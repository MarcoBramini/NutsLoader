package nutsloader

import (
	"encoding/json"
	"fmt"
	"log"
)

/*
	Commands System:
	A command is an action which occurs after a request made by the
	clients.
	The listening workers periodically fetches the commands they have to
	execute.
	Commands are enqueued sorted by their priority. The priority depends on the
	command type and the time they have been requested.

	The lifecycle of a command happens as it follows:
		1. The command is requested by a client and enqueued (status waiting).
		2. The command is fetched by a worker (status dispatched).
		3. The worker executes the command and submits a response:
			a) The command execution succeded and the command is removed
				from the queue.
			b) The command execution failed (status failed). If the error
				is not fatal and retryable, the command is re-scheduled.
				If the error is not retryable, a shutdown command is
				requested immediately. The system has to stop.

	Commands are saved in a Redis Sorted Set with the encoded string
	"{requestID}_{type}" as value and the integer
	"{priority}{requestTime}".

	When the worker is free, it fetches the next command to execute.
	When it's done, it notifies the command completion sending a response
	payload. Only then the command is removed from the queue and a new
	command can be fetched.
*/

// FetchNextCommand ...
// Returned value follows the format: {requestID}_{type}.
// It returns an empty string if the command queue is empty.
func (n *nutsLoader) FetchNextCommand() string {

	// 0. Fetch the next command from the queue.
	nextRedisCommands, err := n.redisClient.ZRange(cmdQueueRedisKey, 1, 1).Result()
	if err != nil {
		log.Printf("unexpected error fetching next command from redis: %s", err)
	}

	if len(nextRedisCommands) == 0 {
		return ""
	}
	return nextRedisCommands[0]
}

func (n *nutsLoader) CompleteCommand(commandResponse CommandResponse) error {
	// 0. Validate parameters.
	if !validateCompleteCommandParameters(commandResponse) {
		return fmt.Errorf("unexpected error: parameters validation failed")
	}

	// 1. Remove the completed command from the queue.
	commandService := commandService{}
	completedCommandKey := commandService.BuildCommandRedisKey(
		commandResponse.ClientID,
		commandResponse.RequestID,
		commandResponse.CommandType,
	)
	_, err := n.redisClient.ZRem(
		cmdQueueRedisKey,
		completedCommandKey,
	).Result()
	if err != nil {
		log.Printf("unexpected error removing completed command (%s) from redis: %s", completedCommandKey, err)
	}

	// 2. Publish event on PubSub.
	jsonCmdResponse, err := json.Marshal(commandResponse)
	if err != nil {
		log.Printf("unexpected error encoding command response to json: %s, payload: %+v", err, commandResponse)
	}
	commandResponseRedisChannel := commandService.BuildCommandResponseRedisChannel(commandResponse.ClientID)
	_, err = n.redisClient.Publish(commandResponseRedisChannel, jsonCmdResponse).Result()
	if err != nil {
		log.Printf("unexpected error publishing command response to Redis (channel: %s): %s", commandResponseRedisChannel, err)
	}

	return nil
}

func validateCompleteCommandParameters(commandResponse CommandResponse) bool {
	if commandResponse.RequestID == "" {
		log.Printf("nutsLoader.CompleteCommand(): empty requestID found [%+v]", commandResponse)
		return false
	}

	if commandResponse.Error == "" && commandResponse.Result == nil {
		log.Printf("nutsLoader.CompleteCommand(): both result and error fields are empty [%+v]", commandResponse)
		return false
	}

	return true
}

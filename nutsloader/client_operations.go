package nutsloader

import (
	"encoding/json"
	"fmt"
	"log"
	"time"

	"github.com/go-redis/redis"
	"github.com/google/uuid"
)

// Clients
func (n *nutsLoader) Login() (string, error) {
	panic("not implemented") // TODO: Implement
}

func (n *nutsLoader) GetFuelLevel(clientID string) (uint, error) {
	// 0. Get subscription for response channel.
	var commandService commandService
	subscription := n.redisClient.Subscribe(commandService.BuildCommandResponseRedisChannel(clientID))
	defer subscription.Close()

	// 1. Add command to command queue.
	requestID := uuid.New().String()
	r := n.redisClient.ZAdd(
		cmdQueueRedisKey,
		redis.Z{
			Member: commandService.BuildCommandRedisKey(clientID, requestID, GetFuelLevelCommandType),
			Score:  commandService.BuildCommandRedisScore(LowCommandPriority),
		},
	)
	if r.Err() != nil {
		return 0, fmt.Errorf("unexpected error adding command (%s-%s) to queue: %s", clientID, GetFuelLevelCommandType, r.Err())
	}

	// 2. Listen for command response.
	cmdResponse, err := receiveCommandResponse(requestID, subscription)
	if err != nil {
		return 0, fmt.Errorf("unexpected error received listening for command response: %s", err)
	}

	// 3. Format command response.
	var commandResponseFormatter commandResponseFormatter
	return commandResponseFormatter.buildGetFuelLevelCommandResponse(cmdResponse)
}

func (n *nutsLoader) SetMode(clientID string, automaticRefill bool) error {
	// 0. Get subscription for response channel.
	var commandService commandService
	subscription := n.redisClient.Subscribe(commandService.BuildCommandResponseRedisChannel(clientID))
	defer subscription.Close()

	// 1. Add command to command queue.
	requestID := uuid.New().String()
	commandType := ManualModeCommandType
	if automaticRefill {
		commandType = AutomaticModeCommandType
	}

	r := n.redisClient.ZAdd(
		cmdQueueRedisKey,
		redis.Z{
			Member: commandService.BuildCommandRedisKey(clientID, requestID, commandType),
			Score:  commandService.BuildCommandRedisScore(MediumCommandPriority),
		},
	)
	if r.Err() != nil {
		return fmt.Errorf("unexpected error adding command (%s-%s) to queue: %s", clientID, commandType, r.Err())
	}

	// 2. Listen for command response.
	cmdResponse, err := receiveCommandResponse(requestID, subscription)
	if err != nil {
		return fmt.Errorf("unexpected error received listening for command response: %s", err)
	}

	// 3. Format command response.
	var commandResponseFormatter commandResponseFormatter
	return commandResponseFormatter.buildSetModeCommandResponse(cmdResponse)
}

func (n *nutsLoader) StartRefill(clientID string) error {
	// 0. Get subscription for response channel.
	var commandService commandService
	subscription := n.redisClient.Subscribe(commandService.BuildCommandResponseRedisChannel(clientID))
	defer subscription.Close()

	// 1. Add command to command queue.
	requestID := uuid.New().String()
	r := n.redisClient.ZAdd(
		cmdQueueRedisKey,
		redis.Z{
			Member: commandService.BuildCommandRedisKey(clientID, requestID, StartRefillCommandType),
			Score:  commandService.BuildCommandRedisScore(MediumCommandPriority),
		},
	)
	if r.Err() != nil {
		return fmt.Errorf("unexpected error adding command (%s-%s) to queue: %s", clientID, StartRefillCommandType, r.Err())
	}

	// 2. Listen for command response.
	cmdResponse, err := receiveCommandResponse(requestID, subscription)
	if err != nil {
		return fmt.Errorf("unexpected error received listening for command response: %s", err)
	}

	// 3. Format command response.
	var commandResponseFormatter commandResponseFormatter
	return commandResponseFormatter.buildStartRefillCommandResponse(cmdResponse)
}

func (n *nutsLoader) Stop(clientID string) error {
	// 0. Get subscription for response channel.
	var commandService commandService
	subscription := n.redisClient.Subscribe(commandService.BuildCommandResponseRedisChannel(clientID))
	defer subscription.Close()

	// 1. Add command to command queue.
	requestID := uuid.New().String()
	r := n.redisClient.ZAdd(
		cmdQueueRedisKey,
		redis.Z{
			Member: commandService.BuildCommandRedisKey(clientID, requestID, StopCommandType),
			Score:  commandService.BuildCommandRedisScore(HighCommandPriority),
		},
	)
	if r.Err() != nil {
		return fmt.Errorf("unexpected error adding command (%s-%s) to queue: %s", clientID, StopCommandType, r.Err())
	}

	// 2. Listen for command response.
	cmdResponse, err := receiveCommandResponse(requestID, subscription)
	if err != nil {
		return fmt.Errorf("unexpected error received listening for command response: %s", err)
	}

	// 3. Format command response.
	var commandResponseFormatter commandResponseFormatter
	return commandResponseFormatter.buildStopCommandResponse(cmdResponse)
}

func (n *nutsLoader) ForceShutdown(clientID string) error {
	// 0. Get subscription for response channel.
	var commandService commandService
	subscription := n.redisClient.Subscribe(commandService.BuildCommandResponseRedisChannel(clientID))
	defer subscription.Close()

	// 1. Add command to command queue.
	requestID := uuid.New().String()
	r := n.redisClient.ZAdd(
		cmdQueueRedisKey,
		redis.Z{
			Member: commandService.BuildCommandRedisKey(clientID, requestID, ForceShutdownCommandType),
			Score:  commandService.BuildCommandRedisScore(HighCommandPriority),
		},
	)
	if r.Err() != nil {
		return fmt.Errorf("unexpected error adding command (%s-%s) to queue: %s", clientID, ForceShutdownCommandType, r.Err())
	}

	// 2. Listen for command response.
	cmdResponse, err := receiveCommandResponse(requestID, subscription)
	if err != nil {
		return fmt.Errorf("unexpected error received listening for command response: %s", err)
	}

	// 3. Format command response.
	var commandResponseFormatter commandResponseFormatter
	return commandResponseFormatter.buildForceShutdownCommandResponse(cmdResponse)
}

// --------------
// Support method
// --------------

func receiveCommandResponse(requestID string, subscription *redis.PubSub) (CommandResponse, error) {
	// Go channel which receives messages.
	channel := subscription.Channel()

	// Save the timeout timestamp. The command response will be awaited
	// until this time.
	timeoutTimestamp := time.Now().UTC().Add(time.Second * 30)

	for {
		select {
		case msg := <-channel:
			// Decode message to a CommandResponse struct.
			var commandResponse CommandResponse
			err := json.Unmarshal([]byte(msg.Payload), &commandResponse)
			if err != nil {
				log.Printf("unexpected error unmarshalling message (%s): %s", msg.Payload, err)
			}

			// Check if the requestID matches, if so, return the response.
			if commandResponse.RequestID == requestID {
				return commandResponse, nil
			}
		}

		// Check if the timeout has been reached, if so, exit from the
		// loop.
		if timeoutTimestamp.Before(time.Now().UTC()) {
			break
		}
		time.Sleep(time.Millisecond * 50)
	}

	return CommandResponse{}, fmt.Errorf("no command response received")
}

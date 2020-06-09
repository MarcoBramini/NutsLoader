package nutsloader

import (
	"fmt"
	"strconv"
	"time"
)

type commandService struct{}

func (c commandService) BuildCommandRedisKey(clientID, requestID string, commandType CommandType) string {
	return fmt.Sprintf("%s_%s_%s", clientID, requestID, commandType)
}

func (c commandService) BuildCommandRedisScore(priority CommandPriority) float64 {
	score, _ := strconv.Atoi(fmt.Sprintf("%d%d", priority, time.Now().UnixNano()/1000))
	return float64(score)
}

func (c commandService) BuildCommandResponseRedisChannel(clientID string) string {
	return fmt.Sprintf("%s_command_responses", clientID)
}

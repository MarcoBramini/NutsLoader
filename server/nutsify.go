package nutsify

import (
	"github.com/go-redis/redis"
)

// Nutsify ...
type Nutsify interface {
	// Clients
	Login() (string, error)
	GetFuelLevel(clientID string) (uint, error)
	SetMode(clientID string, automaticRefill bool) error
	StartRefill(clientID string) error
	Stop(clientID string) error
	ForceShutdown(clientID string) error

	// Worker
	FetchNextCommand() string
	CompleteCommand(commandResponse CommandResponse) error
}

const cmdQueueRedisKey = "command_queue"

type nutsify struct {
	redisClient *redis.Client
}

// New ...
func New() Nutsify {
	redisClient := redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		DB:   1,
	})

	return &nutsify{
		redisClient: redisClient,
	}
}

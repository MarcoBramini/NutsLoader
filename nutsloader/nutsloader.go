package nutsloader

import (
	"github.com/go-redis/redis"
)

// NutsLoader ...
type NutsLoader interface {
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

type nutsLoader struct {
	redisClient *redis.Client
}

// New ...
func New() NutsLoader {
	redisClient := redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		DB:   1,
	})

	return &nutsLoader{
		redisClient: redisClient,
	}
}

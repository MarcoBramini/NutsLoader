package nutsloader

import (
	"time"
)

type CommandType = string

const (
	GetFuelLevelCommandType  CommandType = "LEV"
	ManualModeCommandType    CommandType = "MAN"
	AutomaticModeCommandType CommandType = "AUTO"
	StartRefillCommandType   CommandType = "REF"
	StopCommandType          CommandType = "STOP"
	ForceShutdownCommandType CommandType = "RIP"
)

type CommandPriority uint

const (
	HighCommandPriority   CommandPriority = 0 + iota
	MediumCommandPriority CommandPriority = 1
	LowCommandPriority    CommandPriority = 2
)

type CommandRequest struct {
	ID          string      `json:"ID"`
	CommandType CommandType `json:"commandType"`
	ClientID    string      `json:"clientID"`
	RequestedAt time.Time   `json:"requestedAt"`
}

type CommandResponse struct {
	RequestID   string                 `json:"requestID"`
	ClientID    string                 `json:"clientID"`
	CommandType CommandType            `json:"commandType"`
	Result      map[string]interface{} `json:"result"`
	Error       string                 `json:"error"`
}

package main

import (
	"log"
	"net/http"
	"nutsify"

	"github.com/gorilla/rpc/v2/json2"
)

type NutsifyRPCService struct {
	nutsifyInstance nutsify.Nutsify
}

func NewNutsifyRPCService(n nutsify.Nutsify) NutsifyRPCService {
	return NutsifyRPCService{
		nutsifyInstance: n,
	}
}


func (rpc *NutsifyRPCService) GetFuelLevel(r *http.Request, args *struct{ ClientID string }, reply *uint) error {
	if args.ClientID == "" {
		log.Printf("GetFuelLevel(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	res, err := rpc.nutsifyInstance.GetFuelLevel(args.ClientID)
	if err != nil {
		log.Printf("GetFuelLevel(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	*reply = res
	return nil
}

func (rpc *NutsifyRPCService) StartRefill(r *http.Request, args *struct{ ClientID string }, reply *interface{}) error {
	if args.ClientID == "" {
		log.Printf("StartRefill(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	err := rpc.nutsifyInstance.StartRefill(args.ClientID)
	if err != nil {
		log.Printf("StartRefill(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	return nil
}

func (rpc *NutsifyRPCService) Stop(r *http.Request, args *struct{ ClientID string }, reply *interface{}) error {
	if args.ClientID == "" {
		log.Printf("Stop(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	err := rpc.nutsifyInstance.Stop(args.ClientID)
	if err != nil {
		log.Printf("Stop(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	return nil
}

func (rpc *NutsifyRPCService) ForceShutdown(r *http.Request, args *struct{ ClientID string }, reply *interface{}) error {
	if args.ClientID == "" {
		log.Printf("Stop(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	err := rpc.nutsifyInstance.Stop(args.ClientID)
	if err != nil {
		log.Printf("Stop(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	return nil
}

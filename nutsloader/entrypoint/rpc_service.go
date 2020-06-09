package main

import (
	"fmt"
	"github.com/MarcoBramini/NutsLoader/nutsloader"
	"log"
	"net/http"

	"github.com/gorilla/rpc/v2/json2"
)

type nutsloaderRPCService struct {
	nutsloaderInstance *nutsloader.NutsLoader
}

func newNutsloaderRPCService(n *nutsloader.NutsLoader) (*nutsloaderRPCService,error) {
	if n == nil {
		return nil, fmt.Errorf("null Nutsloader instance received")
	}

	return &nutsloaderRPCService{
		nutsloaderInstance: n,
	},nil
}

func (rpc *nutsloaderRPCService) GetFuelLevel(r *http.Request, args *struct{ ClientID string }, reply *uint) error {
	if args.ClientID == "" {
		log.Printf("GetFuelLevel(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	res, err := (*rpc.nutsloaderInstance).GetFuelLevel(args.ClientID)
	if err != nil {
		log.Printf("GetFuelLevel(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	*reply = res
	return nil
}

func (rpc *nutsloaderRPCService) StartRefill(r *http.Request, args *struct{ ClientID string }, reply *interface{}) error {
	if args.ClientID == "" {
		log.Printf("StartRefill(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	err := (*rpc.nutsloaderInstance).StartRefill(args.ClientID)
	if err != nil {
		log.Printf("StartRefill(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	return nil
}

func (rpc *nutsloaderRPCService) Stop(r *http.Request, args *struct{ ClientID string }, reply *interface{}) error {
	if args.ClientID == "" {
		log.Printf("Stop(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	err := (*rpc.nutsloaderInstance).Stop(args.ClientID)
	if err != nil {
		log.Printf("Stop(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	return nil
}

func (rpc *nutsloaderRPCService) ForceShutdown(r *http.Request, args *struct{ ClientID string }, reply *interface{}) error {
	if args.ClientID == "" {
		log.Printf("Stop(): missing ClientID")
		return &json2.Error{Code: json2.E_BAD_PARAMS, Message: "invalid params"}
	}

	err := (*rpc.nutsloaderInstance).ForceShutdown(args.ClientID)
	if err != nil {
		log.Printf("Stop(%s): %s", args.ClientID, err)
		return &json2.Error{Code: json2.E_SERVER, Message: err.Error()}
	}

	return nil
}

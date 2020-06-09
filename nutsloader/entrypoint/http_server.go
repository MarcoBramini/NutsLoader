package main

import (
	"fmt"
	"github.com/MarcoBramini/NutsLoader/nutsloader"
	"net/http"

	"github.com/gorilla/rpc/v2"
	"github.com/gorilla/rpc/v2/json2"
)

func main() {
	nutsloaderInstance := nutsloader.New()

	// RPC service initialization
	s := rpc.NewServer()
	s.RegisterCodec(json2.NewCodec(), "application/json")

	nutsloaderRPCService,err := newNutsloaderRPCService(&nutsloaderInstance)
	if err != nil {
		panic(fmt.Sprintf("error initializing NutsloaderRPC service: %s", err))
	}

	err = s.RegisterService(nutsloaderRPCService, "NutsLoader")
	if err != nil {
		panic(fmt.Sprintf("error registering service Nutsloader: %s", err))
	}
	http.Handle("/client/rpc", s)

	// REST service initialization
	nutsloaderRESTService := newNutsloaderRESTService(nutsloaderInstance)
	http.HandleFunc("/nutsloader/rest/commands", nutsloaderRESTService.commandAPIHandler)

	err = http.ListenAndServe(":80", nil)
	if err != nil {
		panic(fmt.Sprintf("unable to start serving: %s", err))
	}
}

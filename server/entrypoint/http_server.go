package main

import (
	"fmt"
	"net/http"

	"github.com/gorilla/rpc/v2"
	"github.com/gorilla/rpc/v2/json"
)

func main() {
	//nutsifyInstance := nutsify.New()

	s := rpc.NewServer()
	s.RegisterCodec(json.NewCodec(), "application/json")

	//nutsifyRPCService := newNutsifyRPCService(nutsifyInstance)
	//s.RegisterService(nutsifyRPCService, "Nutsify")

	s.RegisterService(new(HelloService), "Serv")
	fmt.Println(s.HasMethod("Serv.Say"))

	//nutsifyRESTService := newNutsifyRESTService(nutsifyInstance)

	http.Handle("/client/jsonrpc", s)

	//http.HandleFunc("/nutsify/rest/commands", nutsifyRESTService.commandAPIHandler)
	http.ListenAndServe(":80", nil)
}

package main

import (
	"log"
	"net/http"
)

type HelloArgs struct {
	Who string
}

type HelloReply struct {
	Message string
}

type HelloService struct{}

func (h *HelloService) Say(r *http.Request, args *HelloArgs, reply *HelloReply) error {
	reply.Message = "Hello, " + args.Who + "!"
	log.Printf("request: %v\nargs: %v\nreply: %v", r, args, reply)
	return nil
}

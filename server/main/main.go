package main

import (
	"fmt"
	"nutsify"
	"strconv"
	"time"
)

func main() {
	nut := nutsify.New()

	var lvl uint
	var err error

	/*go func() {
		for {
			nextCommand := nut.FetchNextCommand()

			if nextCommand != "" {
				cmdParts := strings.Split(nextCommand, "_")

				err = nut.CompleteCommand(
					nutsify.CommandResponse{
						ClientID:    cmdParts[0],
						RequestID:   cmdParts[1],
						CommandType: cmdParts[2],
						Error:       "",
						Result:      map[string]interface{}{"level": uint(90)},
					},
				)
				if err != nil {
					panic(err)
				}
			}
		}
	}()*/

	fuelLvlFunc := func(clientID string) {
		fmt.Println("start GFL")
		start := time.Now().UnixNano()
		lvl, err = nut.GetFuelLevel(clientID)
		if err != nil {
			panic(err)
		}
		fmt.Println("GetFuelLevel: ", lvl, float64(time.Now().UnixNano()-start)/float64(1000000))
	}
	refFunc := func(clientID string) {
		fmt.Println("start REF")
		start := time.Now().UnixNano()
		err = nut.StartRefill(clientID)
		fmt.Println("StartRefill: ", err, float64(time.Now().UnixNano()-start)/float64(1000000))
	}
	stopFunc := func(clientID string) {
		fmt.Println("start STOP")
		start := time.Now().UnixNano()
		err = nut.Stop(clientID)
		fmt.Println("Stop: ", err, float64(time.Now().UnixNano()-start)/float64(1000000))
	}

	i := 0
	for {
		cmd := ""
		_, err := fmt.Scanf("%s", &cmd)
		if err != nil {
			panic(err)
		}

		switch cmd {
		case "GFL":
			go fuelLvlFunc(strconv.Itoa(i))
		case "REF":
			go refFunc(strconv.Itoa(i))
		case "STOP":
			go stopFunc(strconv.Itoa(i))
		case "TGFL":
			// clients
			for i := 0; i < 200; i++ {
				// req
				for j := 0; j < 2; j++ {
					go fuelLvlFunc(strconv.Itoa(i))
				}
			}
		}
		i++
	}
}

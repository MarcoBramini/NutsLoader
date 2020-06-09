package nutsloader

import "fmt"

type commandResponseFormatter struct{}

func (crf *commandResponseFormatter) buildGetFuelLevelCommandResponse(commandResponse CommandResponse) (uint, error) {
	err := commandResponse.Error
	if err != "" {
		return 0, fmt.Errorf(err)
	}

	result, ok := commandResponse.Result["level"]
	if !ok {
		return 0, fmt.Errorf("invalid response format")
	}

	fuelLevel := result.(float64)

	return uint(fuelLevel), nil
}

func (crf *commandResponseFormatter) buildSetModeCommandResponse(commandResponse CommandResponse) error {
	err := commandResponse.Error
	if err != "" {
		return fmt.Errorf(err)
	}
	return nil
}
func (crf *commandResponseFormatter) buildStartRefillCommandResponse(commandResponse CommandResponse) error {
	err := commandResponse.Error
	if err != "" {
		return fmt.Errorf(err)
	}
	return nil
}
func (crf *commandResponseFormatter) buildStopCommandResponse(commandResponse CommandResponse) error {
	err := commandResponse.Error
	if err != "" {
		return fmt.Errorf(err)
	}
	return nil
}
func (crf *commandResponseFormatter) buildForceShutdownCommandResponse(commandResponse CommandResponse) error {
	err := commandResponse.Error
	if err != "" {
		return fmt.Errorf(err)
	}
	return nil
}

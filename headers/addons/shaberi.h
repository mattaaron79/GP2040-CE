#include "gpaddon.h"
#include "gamepad.h"
#include <vector>

#ifndef _SHABERI_H
#define _SHABERI_H

#define IKARI_MESSAGE_HEADER 0x00
#define SYNC_UART_ID uart0 // Channel for synchronizing buttons states
#define AUX_UART_ID uart1  // Channel for configuration, RGB, and auxilary data
#define RESET_MILLIS 100
#define BAUD_RATE 115200

// Senpai Module Name
#define ShaberiName "Shaberi"

// Physical mode transmits and recieves physical button numbers instead of high level buttons (button 1 - 32 vs B1, R1, S2, etc).
// Allows complete configuration of actions on the Senpai end by treating higher numbered buttons as part of its own configuration
#define PHYSICAL_MODE true

class Shaberi : public GPAddon
{
public:
	virtual bool available();
	virtual void setup();
	virtual void process() {}
	virtual void postprocess(bool sent) {}
	virtual void preprocess();
	virtual void reinit() {}
	virtual std::string name() { return ShaberiName; }

	void preprocessSenpai();
	void preprocessSenpaiPhysical();
	void preprocessKouhai();

	// void updateState(const GamepadState& newState);
	// const GamepadState& getLastState() const;
private:
	// Kouhai
	GamepadState lastState;
	bool areStatesEqual(const GamepadState &state1, const GamepadState &state2);
	void noticeMeSenpai(Gamepad *gamepad);
	uint32_t messageCounter = 0;

	// Senpai
	bool playingMacro = false;
	uint32_t macroStartTime = 0;
	size_t currentMacroIndex = 0;
	Macro currentMacro;

	uint32_t byteCounter = 0;
	uint32_t lastTime = 0;
	uint8_t buffer[3] = {0};
	uint8_t bufferIndex = 0;

	void playMacro(const Macro &macro);
	GamepadState getMacroState();
};

#endif
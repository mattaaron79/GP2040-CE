#include "addons/shaberi.h"
#include "config.pb.h"
#include "hardware/uart.h"
#include "helper.h"
#include "storagemanager.h"
#include <bitset>

bool Shaberi::available()
{
	const ShaberiOptions &options = Storage::getInstance().getAddonOptions().shaberiOptions;
	return options.enabled;
}

void Shaberi::setup()
{
	Storage& storageInstance = Storage::getInstance();
	const ShaberiOptions &options = Storage::getInstance().getAddonOptions().shaberiOptions;
	stdio_init_all();

	// Set up UART
	uart_init(AUX_UART_ID, BAUD_RATE);

	// Set up the UART pins
	if (options.uartEnabled0)
	{
		gpio_set_function(options.pinUartRx0, GPIO_FUNC_UART);
		gpio_set_function(options.pinUartTx0, GPIO_FUNC_UART);
		// storageInstance.shaberiDebug = "uart0";
	}

	else if (options.uartEnabled1)
	{
		gpio_set_function(options.pinUartRx1, GPIO_FUNC_UART);
		gpio_set_function(options.pinUartTx1, GPIO_FUNC_UART);
		// storageInstance.shaberiDebug = "uart1";
	}
}

void Shaberi::preprocess()
{
	const ShaberiOptions &options = Storage::getInstance().getAddonOptions().shaberiOptions;
	if (options.isSenpai)
	{
		preprocessSenpaiPhysical();
	}
	else
	{
		preprocessKouhai();
	}
}

void Shaberi::preprocessSenpai()
{
	Storage& storageInstance = Storage::getInstance();
	Gamepad *gamepad = Storage::getInstance().GetGamepad();
	bool hadMessage = false;
	uint32_t currentTime = getMillis();
	uint32_t timeElapsed = currentTime - lastTime;

	if (timeElapsed > RESET_MILLIS && bufferIndex > 0)
	{
		// Reset the buffer
		bufferIndex = 0;
		// Grab bytes from the buffer until empty
		while (uart_is_readable(AUX_UART_ID))
		{
			uint8_t byte = uart_getc(AUX_UART_ID);
		}

		// debugMessage = "Resetting:" + std::to_string(timeElapsed);
	}

	while (uart_is_readable(AUX_UART_ID))
	{
		uint8_t byte = uart_getc(AUX_UART_ID);

		buffer[bufferIndex] = byte;
		bufferIndex++;

		if (bufferIndex == 3)
		{
			messageCounter++;
			// 3 bytes is a full packet
			uint8_t dpad = buffer[0];
			// uint16_t buttons = (static_cast<uint16_t>(buffer[1]) << 8) | buffer[2];
			uint16_t buttons = (uint16_t)(buffer[2] << 8) | buffer[1];
			lastState = GamepadState();
			lastState.dpad = dpad;
			lastState.buttons = buttons;
			bufferIndex = 0;
			// printf("Received Senpai packet: %d %d %d\n", dpad, buffer[1], buffer[2]);
			// debugMessage = std::to_string(messageCounter) + "  " + std::to_string(dpad) + " " + std::to_string(buffer[1]) + " " + std::to_string(buffer[2]);
			// debugMessage = std::to_string(messageCounter);
			gamepad->state.shaberiCounter++;
		}

		hadMessage = true;
	}

	if (hadMessage)
	{
		lastTime = getMillis();
	}

	gamepad->state.dpad |= lastState.dpad;
	gamepad->state.buttons |= lastState.buttons;
}

void Shaberi::preprocessSenpaiPhysical()
{
	Storage& storageInstance = Storage::getInstance();
	Gamepad *gamepad = Storage::getInstance().GetGamepad();
	bool hadMessage = false;
	uint32_t currentTime = getMillis();
	uint32_t timeElapsed = currentTime - lastTime;

	if (timeElapsed > RESET_MILLIS && bufferIndex > 0)
	{
		// Reset the buffer
		bufferIndex = 0;
		// Grab bytes from the buffer until empty
		while (uart_is_readable(AUX_UART_ID))
		{
			uint8_t byte = uart_getc(AUX_UART_ID);
		}

		// debugMessage = "Resetting:" + std::to_string(timeElapsed);
	}

	while (uart_is_readable(AUX_UART_ID))
	{
		uint8_t byte = uart_getc(AUX_UART_ID);
		byteCounter++;

		buffer[bufferIndex] = byte;
		bufferIndex++;

		if (bufferIndex == 2)
		{
			messageCounter++;
			// Shift the 2-byte button buffer to the high end (bits 16-31)
			uint32_t vpins =
				(static_cast<uint32_t>(buffer[0]) << 16) |
				(static_cast<uint32_t>(buffer[1]) << 24);

			lastState = GamepadState();
			lastState.vpins = vpins;
			bufferIndex = 0;
			gamepad->state.shaberiCounter++;

			gamepad->state.debugString = std::to_string(lastState.vpins);
		}

		hadMessage = true;
	}

	if (hadMessage)
	{
		lastTime = getMillis();
	}

	gamepad->state.vpins |= lastState.vpins;
	// gamepad->state.debugString2 = std::to_string(gamepad->state.physicalButtons);
}

void Shaberi::preprocessKouhai()
{
	Storage& storageInstance = Storage::getInstance();
	Gamepad *gamepad = Storage::getInstance().GetGamepad();
	bool isSameState = areStatesEqual(gamepad->state, lastState);
	// If the state has changed, send an update to Senpai-San! ^^
	if (!isSameState)
	{
		noticeMeSenpai(gamepad);
		gamepad->state.shaberiCounter++;
	}

	lastState = gamepad->state;
}

void Shaberi::noticeMeSenpai(Gamepad *gamepad)
{
	messageCounter++;
	
	#if !PHYSICAL_MODE
		// Send the dpad byte
		uart_putc(AUX_UART_ID, gamepad->state.dpad);

		// Transmit the uint16_t value, one byte at a time
		uart_putc(AUX_UART_ID, gamepad->state.buttons & 0xFF);		   // Send the lower byte
		uart_putc(AUX_UART_ID, (gamepad->state.buttons >> 8) & 0xFF); // Send the upper byte
	#else
		// Transmit the uint32_t value, one byte at a time
		uart_putc(AUX_UART_ID, gamepad->state.vpins & 0xFF);		 // Send the lowest byte
		uart_putc(AUX_UART_ID, (gamepad->state.vpins >> 8) & 0xFF);  // Send the second byte
		// uart_putc(AUX_UART_ID, (gamepad->state.physicalButtons >> 16) & 0xFF); // Send the third byte
		// uart_putc(AUX_UART_ID, (gamepad->state.physicalButtons >> 24) & 0xFF); // Send the highest byte
	#endif
}


bool Shaberi::areStatesEqual(const GamepadState &state1, const GamepadState &state2)
{
	#if !PHYSICAL_MODE
		return state1.dpad == state2.dpad &&
				state1.buttons == state2.buttons;
	#else
		return state1.vpins == state2.vpins;
	#endif

}
#include <cstdint>

struct GamepadAnalogState
{
	// Analog and rapid trigger
    float triggerPoints[32] = {0.0f};			// Next activation/deactivation point
    bool pressed[32] = {false};					// True if button considered pressed
	uint32_t readings[32] = {0};			// For debugging and options setting: the raw voltage reading for each analog trigger
	float readingsNormalized[32] = {0.0f};		// Normalized pressed amount (0.0 - 1.0)
    uint32_t lastPressTime[32] = {0};			// Last press timestamp. Used for minimum latching
	uint32_t lastPressTimeAny = 0;				// Last time any analog button was pressed

	string debugString = ""; 					// For displaying debug info on the screen, if needed
	string debugString2 = "";
};
#include "addons/he_trigger.h"
#include "storagemanager.h"

#include "hardware/adc.h"
#include <cmath>

#define ADC_MAX ((1 << 12) - 1) // 4095
#define LATCH_TIME_MS 0
#define DEADZONE_NORMALIZED 0.01f

bool HETriggerAddon::available() {
    return Storage::getInstance().getAddonOptions().heTriggerOptions.enabled;
}

void HETriggerAddon::setup() {
    HETriggerOptions & options = Storage::getInstance().getAddonOptions().heTriggerOptions;
    this->muxTotal = 32 / options.muxChannels;
    if ( this->muxTotal > 4 )
        this->muxTotal = 4; // Direct = 4, 4-Channel = 4, 8-Channel = 3, 16-Channel = 2

    // Init the ADC options
    muxPinArray[0] = options.muxADCPin0;
    muxPinArray[1] = options.muxADCPin1;
    muxPinArray[2] = options.muxADCPin2;
    muxPinArray[3] = options.muxADCPin3;
    for(int i = 0; i < muxTotal; i++) {
        if ( muxPinArray[i] >= 26 && muxPinArray[i] <= 29 ) {
            adc_gpio_init(muxPinArray[i]);
        }
    }

    // Init our select pins
    switch(options.muxChannels) {
        case 4:
            this->selectPins = 2;
            break;
        case 8:
            this->selectPins = 3;
            break;
        case 16:
            this->selectPins = 4;
            break;
        case 1:
        default:
            this->selectPins = 0;
            break;
    }

    selectPinArray[0] = options.selectPin0;
    selectPinArray[1] = options.selectPin1;
    selectPinArray[2] = options.selectPin2;
    selectPinArray[3] = options.selectPin3;
    for(int i = 0; i < selectPins; i++) {
        if ( selectPinArray[i] != -1 ) {
            gpio_init(selectPinArray[i]);
            gpio_set_dir(selectPinArray[i], GPIO_OUT);
            gpio_put(selectPinArray[i], 0);
        }
    }

    lastADCSelected = -1;

    if ( options.emaSmoothing == 1 ) {
        // Read all ADC values once
        for(int i = 0; i < 32; i++) {
            // Ignore triggers with no actions
            if (options.triggers[i].action == -10 )
                continue;
            mux = (i / options.muxChannels);
            channel = (i % options.muxChannels);
            selectChannel(channel);
            // Only Switch ADC if we are not currently on the mux ADC
            if ( lastADCSelected != muxPinArray[mux]) {
                adc_select_input(muxPinArray[mux]-26);
                lastADCSelected = muxPinArray[mux];
            }
            emaSmoothingReads[i] = adc_read();
        }
        emaSmoothingFactor = (float)options.smoothingFactor / 100.f; // 99 = max smoothing factor
    }

    calibrateAnalogIdle();
}

void HETriggerAddon::selectChannel(uint8_t channel) {
    for(int i = 0; i < selectPins; i++) {
        if ( selectPinArray[i] != -1 ) {
            gpio_put(selectPinArray[i], (channel >> i) & 0x01);
        }   
    }
}

void HETriggerAddon::readVoltages(int numReads, int sleepMicro, bool doDummyRead) {
    Gamepad* gamepad = Storage::getInstance().GetGamepad();
    HETriggerOptions& options = Storage::getInstance().getAddonOptions().heTriggerOptions;
    for (uint8_t he = 0; he < 32; he++) {
        // Ignore triggers with no actions
        if (options.triggers[he].action == -10 )
            continue;
        mux = (he / options.muxChannels);
        channel = (he % options.muxChannels);
        selectChannel(channel);

        if ( lastADCSelected != muxPinArray[mux]) {
            adc_select_input(muxPinArray[mux]-26);
            lastADCSelected = muxPinArray[mux];
        }

        sleep_us(sleepMicro);
        if (doDummyRead) {
            adc_read(); // Dummy read
        }
        // Calculate the average voltage
        value = 0;
        for (int j = 0; j < numReads; j++) {
            value += adc_read();
        }

        value /= numReads;

        gamepad->analogState.readings[he] = value;

        // AnalogTriggerInfo& triggerInfo = options.triggers[he];
        // if (value < triggerInfo.max) {
        //     triggerInfo.max = value;
        // }
        // TODO: Add max value auto calibration
    }
}

uint16_t HETriggerAddon::emaSmoothing(uint16_t value, uint16_t previous) {
    float ema_value = (float)value / ADC_MAX;
    float ema_previous = (float)previous / ADC_MAX;
    return ((emaSmoothingFactor*ema_value) + ((1.0f-emaSmoothingFactor) * ema_previous)) * ADC_MAX;
}

void HETriggerAddon::calibrateAnalogIdle() {
	// sleep_ms(10);
	readVoltages(16, 100, true);

    HETriggerOptions & options = Storage::getInstance().getAddonOptions().heTriggerOptions;
    Gamepad* gamepad = Storage::getInstance().GetGamepad();

    for (uint8_t he = 0; he < 32; he++) {
        HETriggerInfo& triggerInfo = options.triggers[he];
        if (triggerInfo.action == -10 )
            continue;
        triggerInfo.idle = gamepad->analogState.readings[he];
        // buttonInfo.trigger.max = buttonInfo.trigger.idle - 400;
    }
}

void HETriggerAddon::determinePressed() {
    Gamepad* gamepad = Storage::getInstance().GetGamepad();
    HETriggerOptions & options = Storage::getInstance().getAddonOptions().heTriggerOptions;
    GamepadAnalogState& analogState = gamepad->analogState;

    for (uint8_t he = 0; he < 32; he++) {
        HETriggerInfo& triggerInfo = options.triggers[he];
        if (triggerInfo.action == -10 )
            continue;

        uint16_t value = analogState.readings[he];

        if (options.emaSmoothing) {
            value = emaSmoothing(value, emaSmoothingReads[he]);
            emaSmoothingReads[he] = value;
        }

        float idle = triggerInfo.idle;
        float maxVal = triggerInfo.max;

        // Clamp min value at idle. If maxVal is over idle, voltage reading should be at idle or above, otherwise below
        if (maxVal > idle) {
            value = fmaxf(value, idle);
        } else {
            value = fminf(value, idle);
        }

        // Total press span
        float span = fabsf(maxVal - idle);

        // Displacement from idle, normalized to 0 to 1
        float pressedNormalized = fabsf(value - idle);

        // Normalize
        pressedNormalized = fminf(fmaxf(pressedNormalized / span, 0.0f), 1.0f);

        // Round at low and high ends to prevent jitter caused by noise if trigger threshold is very sensitive
        pressedNormalized = (pressedNormalized < DEADZONE_NORMALIZED) ? 0.0f : 
                    (pressedNormalized > 1.0f - DEADZONE_NORMALIZED) ? 1.0f : pressedNormalized;

        // Get current pressed state to determine if we are checking for actuation or release
        bool isPressed = analogState.pressed[he];

        bool rapidTrigger = true;
        float actuate = 0.15f;
        float release = 0.15f;

        // Based on global analog settings
        // rapidTrigger = options.rapidTrigger;
        // actuate = fminf(fmaxf(options.active, 0.01f), 0.99f);
        // release = fminf(fmaxf(options.release, 0.01f), 0.99f);

        // TODO: Overwrite with per-channel settings if implemented
        
        // Determine if pressed and set next trigger point
        if (rapidTrigger) {
            if (!isPressed) {
                // Trigger is actuation point
                analogState.triggerPoints[he] = fmaxf(analogState.triggerPoints[he], actuate); // Actuation 

                if (pressedNormalized >= analogState.triggerPoints[he] || pressedNormalized > 1.0f - release) {
                    isPressed = true;
                    // Set next release trigger point
                    analogState.triggerPoints[he] = fmaxf(pressedNormalized - release, 0.0f);
                } else {
                    // Pull trigger point to follow the current value at a set distance
                    analogState.triggerPoints[he] = fminf(analogState.triggerPoints[he], pressedNormalized + actuate);
                }
            } else {
                // Trigger is release point
                if (pressedNormalized <= analogState.triggerPoints[he]) {
                    isPressed = false;
                    // Set next actuation trigger point
                    analogState.triggerPoints[he] = fminf(pressedNormalized + actuate, 1.0f);
                } else {
                    // Pull trigger point to follow the current value at a set distance
                    analogState.triggerPoints[he] = fmaxf(analogState.triggerPoints[he], pressedNormalized - release);
                }
            }
        } else {
            // Single Actuation/Release Point
            analogState.triggerPoints[he] = actuate;
            isPressed = (pressedNormalized >= actuate);
        }

        // Minimum latching time
        bool physicalPressed = isPressed;
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (physicalPressed) {
            analogState.lastPressTime[he] = now;
            analogState.lastPressTimeAny = now;
        }

        // Is considered effectively pressed if currently physically pressed, or if it was released within the latch time threshold
        #if LATCH_TIME_MS > 0
            bool effectivePressed = physicalPressed || (now - analogState.lastPressTime[he] < LATCH_TIME_MS);
        #else
            bool effectivePressed = physicalPressed;
        #endif
        
        // Update state
        analogState.readingsNormalized[he] = pressedNormalized;
        analogState.pressed[he] = effectivePressed;
    }
}

void HETriggerAddon::updateGamepadState() {
    Gamepad* gamepad = Storage::getInstance().GetGamepad();
    HETriggerOptions & options = Storage::getInstance().getAddonOptions().heTriggerOptions;
    GamepadAnalogState analogState = gamepad->analogState;

    for (uint8_t he = 0; he < 32; he++) {
        if (!analogState.pressed[he])
            continue;
        HETriggerInfo& triggerInfo = options.triggers[he];
        if (triggerInfo.action == -10)
            continue;

        switch (triggerInfo.action) {
            case GpioAction::BUTTON_PRESS_UP: gamepad->state.dpad |= GAMEPAD_MASK_UP; break;
            case GpioAction::BUTTON_PRESS_DOWN: gamepad->state.dpad |= GAMEPAD_MASK_DOWN; break;
            case GpioAction::BUTTON_PRESS_LEFT: gamepad->state.dpad |= GAMEPAD_MASK_LEFT; break;
            case GpioAction::BUTTON_PRESS_RIGHT: gamepad->state.dpad |= GAMEPAD_MASK_RIGHT; break;
            case GpioAction::BUTTON_PRESS_B1: gamepad->state.buttons |= GAMEPAD_MASK_B1; break;
            case GpioAction::BUTTON_PRESS_B2: gamepad->state.buttons |= GAMEPAD_MASK_B2; break;
            case GpioAction::BUTTON_PRESS_B3: gamepad->state.buttons |= GAMEPAD_MASK_B3; break;
            case GpioAction::BUTTON_PRESS_B4: gamepad->state.buttons |= GAMEPAD_MASK_B4; break;
            case GpioAction::BUTTON_PRESS_L1: gamepad->state.buttons |= GAMEPAD_MASK_L1; break;
            case GpioAction::BUTTON_PRESS_R1: gamepad->state.buttons |= GAMEPAD_MASK_R1; break;
            case GpioAction::BUTTON_PRESS_L2: gamepad->state.buttons |= GAMEPAD_MASK_L2; break;
            case GpioAction::BUTTON_PRESS_R2: gamepad->state.buttons |= GAMEPAD_MASK_R2; break;
            case GpioAction::BUTTON_PRESS_S1: gamepad->state.buttons |= GAMEPAD_MASK_S1; break;
            case GpioAction::BUTTON_PRESS_S2: gamepad->state.buttons |= GAMEPAD_MASK_S2; break;
            case GpioAction::BUTTON_PRESS_L3: gamepad->state.buttons |= GAMEPAD_MASK_L3; break;
            case GpioAction::BUTTON_PRESS_R3: gamepad->state.buttons |= GAMEPAD_MASK_R3; break;
            case GpioAction::BUTTON_PRESS_A1: gamepad->state.buttons |= GAMEPAD_MASK_A1; break;
            case GpioAction::BUTTON_PRESS_A2: gamepad->state.buttons |= GAMEPAD_MASK_A2; break;
            case GpioAction::BUTTON_PRESS_A3: gamepad->state.buttons |= GAMEPAD_MASK_A3; break;
            case GpioAction::BUTTON_PRESS_A4: gamepad->state.buttons |= GAMEPAD_MASK_A4; break;
            case GpioAction::BUTTON_PRESS_E1: gamepad->state.buttons |= GAMEPAD_MASK_E1; break;
            case GpioAction::BUTTON_PRESS_E2: gamepad->state.buttons |= GAMEPAD_MASK_E2; break;
            case GpioAction::BUTTON_PRESS_E3: gamepad->state.buttons |= GAMEPAD_MASK_E3; break;
            case GpioAction::BUTTON_PRESS_E4: gamepad->state.buttons |= GAMEPAD_MASK_E4; break;
            case GpioAction::BUTTON_PRESS_E5: gamepad->state.buttons |= GAMEPAD_MASK_E5; break;
            case GpioAction::BUTTON_PRESS_E6: gamepad->state.buttons |= GAMEPAD_MASK_E6; break;
            case GpioAction::BUTTON_PRESS_E7: gamepad->state.buttons |= GAMEPAD_MASK_E7; break;
            case GpioAction::BUTTON_PRESS_E8: gamepad->state.buttons |= GAMEPAD_MASK_E8; break;
            case GpioAction::BUTTON_PRESS_E9: gamepad->state.buttons |= GAMEPAD_MASK_E9; break;
            case GpioAction::BUTTON_PRESS_E10: gamepad->state.buttons |= GAMEPAD_MASK_E10; break;
            case GpioAction::BUTTON_PRESS_E11: gamepad->state.buttons |= GAMEPAD_MASK_E11; break;
            case GpioAction::BUTTON_PRESS_E12: gamepad->state.buttons |= GAMEPAD_MASK_E12; break;                
            case GpioAction::ANALOG_DIRECTION_LS_X_NEG:	gamepad->state.lx = GAMEPAD_JOYSTICK_MIN; break;
            case GpioAction::ANALOG_DIRECTION_LS_X_POS:	gamepad->state.lx = GAMEPAD_JOYSTICK_MAX; break;
            case GpioAction::ANALOG_DIRECTION_LS_Y_NEG:	gamepad->state.ly = GAMEPAD_JOYSTICK_MIN; break;
            case GpioAction::ANALOG_DIRECTION_LS_Y_POS:	gamepad->state.ly = GAMEPAD_JOYSTICK_MAX; break;
            case GpioAction::ANALOG_DIRECTION_RS_X_NEG:	gamepad->state.rx = GAMEPAD_JOYSTICK_MIN; break;
            case GpioAction::ANALOG_DIRECTION_RS_X_POS:	gamepad->state.rx = GAMEPAD_JOYSTICK_MAX; break;
            case GpioAction::ANALOG_DIRECTION_RS_Y_NEG:	gamepad->state.ry = GAMEPAD_JOYSTICK_MIN; break;
            case GpioAction::ANALOG_DIRECTION_RS_Y_POS:	gamepad->state.ry = GAMEPAD_JOYSTICK_MAX; break;
            case GpioAction::BUTTON_PRESS_FN:	gamepad->state.aux |= AUX_MASK_FUNCTION; break;
            case GpioAction::MENU_NAVIGATION_UP: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_UP)); break;
            case GpioAction::MENU_NAVIGATION_DOWN: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_DOWN)); break;
            case GpioAction::MENU_NAVIGATION_LEFT: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_LEFT)); break;
            case GpioAction::MENU_NAVIGATION_RIGHT: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_RIGHT)); break;
            case GpioAction::MENU_NAVIGATION_SELECT: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_SELECT)); break;
            case GpioAction::MENU_NAVIGATION_BACK: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_BACK)); break;
            case GpioAction::MENU_NAVIGATION_TOGGLE: EventManager::getInstance().triggerEvent(new GPMenuNavigateEvent(GpioAction::MENU_NAVIGATION_TOGGLE)); break;
            
            case GpioAction::VPIN_00: gamepad->state.vpins |= VPIN_MASK_0; break;
            case GpioAction::VPIN_01: gamepad->state.vpins |= VPIN_MASK_1; break;
            case GpioAction::VPIN_02: gamepad->state.vpins |= VPIN_MASK_2; break;
            case GpioAction::VPIN_03: gamepad->state.vpins |= VPIN_MASK_3; break;
            case GpioAction::VPIN_04: gamepad->state.vpins |= VPIN_MASK_4; break;
            case GpioAction::VPIN_05: gamepad->state.vpins |= VPIN_MASK_5; break;
            case GpioAction::VPIN_06: gamepad->state.vpins |= VPIN_MASK_6; break;
            case GpioAction::VPIN_07: gamepad->state.vpins |= VPIN_MASK_7; break;
            case GpioAction::VPIN_08: gamepad->state.vpins |= VPIN_MASK_8; break;
            case GpioAction::VPIN_09: gamepad->state.vpins |= VPIN_MASK_9; break;
            case GpioAction::VPIN_10: gamepad->state.vpins |= VPIN_MASK_10; break;
            case GpioAction::VPIN_11: gamepad->state.vpins |= VPIN_MASK_11; break;
            case GpioAction::VPIN_12: gamepad->state.vpins |= VPIN_MASK_12; break;
            case GpioAction::VPIN_13: gamepad->state.vpins |= VPIN_MASK_13; break;
            case GpioAction::VPIN_14: gamepad->state.vpins |= VPIN_MASK_14; break;
            case GpioAction::VPIN_15: gamepad->state.vpins |= VPIN_MASK_15; break;
            case GpioAction::VPIN_16: gamepad->state.vpins |= VPIN_MASK_16; break;
            case GpioAction::VPIN_17: gamepad->state.vpins |= VPIN_MASK_17; break;
            case GpioAction::VPIN_18: gamepad->state.vpins |= VPIN_MASK_18; break;
            case GpioAction::VPIN_19: gamepad->state.vpins |= VPIN_MASK_19; break;
            case GpioAction::VPIN_20: gamepad->state.vpins |= VPIN_MASK_20; break;
            case GpioAction::VPIN_21: gamepad->state.vpins |= VPIN_MASK_21; break;
            case GpioAction::VPIN_22: gamepad->state.vpins |= VPIN_MASK_22; break;
            case GpioAction::VPIN_23: gamepad->state.vpins |= VPIN_MASK_23; break;
            case GpioAction::VPIN_24: gamepad->state.vpins |= VPIN_MASK_24; break;
            case GpioAction::VPIN_25: gamepad->state.vpins |= VPIN_MASK_25; break;
            case GpioAction::VPIN_26: gamepad->state.vpins |= VPIN_MASK_26; break;
            case GpioAction::VPIN_27: gamepad->state.vpins |= VPIN_MASK_27; break;
            case GpioAction::VPIN_28: gamepad->state.vpins |= VPIN_MASK_28; break;
            case GpioAction::VPIN_29: gamepad->state.vpins |= VPIN_MASK_29; break;
            case GpioAction::VPIN_30: gamepad->state.vpins |= VPIN_MASK_30; break;
            case GpioAction::VPIN_31: gamepad->state.vpins |= VPIN_MASK_31; break;
            default: break;
        }
    }
}

void HETriggerAddon::preprocess() {
    // Read voltages
    readVoltages(4, 10, true);

    // Determine pressed state based on voltages and configured thresholds
    determinePressed();

    updateGamepadState();
}
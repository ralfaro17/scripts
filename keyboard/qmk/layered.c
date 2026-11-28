#include "layered.h"

// =============================================================================
// Numpad lock
//
// kanata kept the numpad layer on through a virtual key, separate from the
// Caps hold. QMK layers are a plain on/off bitmask, so TG() would fight with
// the Caps hold. Instead, while locked, layer_state_set_user() forces the
// numpad bit back on whenever anything else clears it.
// =============================================================================

static bool numpad_locked   = false;
static bool numpad_key_down = false;

// =============================================================================
// OverKeys signals
//
// No kanata here, so OverKeys can't get layer changes over TCP. The keyboard
// sends F13-F22 instead, which OverKeys reads as layer triggers and key
// aliases. They're only sent when the host is detected as Windows: on Linux,
// xkb maps these keys to actions like XF86Tools (KDE System Settings).
// =============================================================================

static uint16_t held_layer_signal = KC_NO;

static bool signals_enabled(void) {
    return detected_host_os() == OS_WINDOWS;
}

static uint16_t signal_for_layer(uint8_t layer) {
    switch (layer) {
        case _NAV:
            return SIG_NAV;
        case _MOUSE:
            return SIG_MOUSE;
        case _SYM:
            return SIG_SYM;
        case _NUMPAD:
            return SIG_NUMPAD;
        default:
            return KC_NO;
    }
}

static uint16_t signal_for_mouse_button(uint16_t keycode) {
    switch (keycode) {
        case MS_BTN1:
            return SIG_BTN1;
        case MS_BTN2:
            return SIG_BTN2;
        case MS_BTN3:
            return SIG_BTN3;
        case MS_BTN4:
            return SIG_BTN4;
        case MS_BTN5:
            return SIG_BTN5;
        default:
            return KC_NO;
    }
}

// Momentary layers: keep the active layer's signal held, release the old one.
layer_state_t layer_state_set_user(layer_state_t state) {
    if (numpad_locked) {
        state |= (layer_state_t)1 << _NUMPAD;
    }

    uint16_t signal = signals_enabled() ? signal_for_layer(get_highest_layer(state)) : KC_NO;
    if (signal != held_layer_signal) {
        if (held_layer_signal != KC_NO) {
            unregister_code(held_layer_signal);
        }
        if (signal != KC_NO) {
            register_code(signal);
        }
        held_layer_signal = signal;
    }
    return state;
}

// Base layout: tap the Gallium signal on every Qwerty <-> Gallium change.
// The keyboard always boots in Qwerty (DF isn't saved), matching OverKeys'
// default layout, so the toggle starts in sync.
layer_state_t default_layer_state_set_user(layer_state_t state) {
    static uint8_t base = _QWERTY;

    uint8_t new_base = get_highest_layer(state);
    if (new_base != base) {
        base = new_base;
        if (signals_enabled()) {
            tap_code(SIG_GALLIUM);
        }
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUM_CAP:
            numpad_key_down = record->event.pressed;
            return true;

        case NP_LOCK:
            if (record->event.pressed) {
                numpad_locked = !numpad_locked;
                if (numpad_locked) {
                    layer_on(_NUMPAD);
                } else if (!numpad_key_down) {
                    // If Caps is still held, its release turns the layer off.
                    layer_off(_NUMPAD);
                }
            }
            return false;

        case MS_BTN1:
        case MS_BTN2:
        case MS_BTN3:
        case MS_BTN4:
        case MS_BTN5: {
            uint16_t signal = signal_for_mouse_button(keycode);
            if (record->event.pressed) {
                if (signals_enabled()) {
                    register_code(signal);
                }
            } else {
                // Always release, so a signal can't get stuck.
                unregister_code(signal);
            }
            return true;
        }
    }
    return true;
}

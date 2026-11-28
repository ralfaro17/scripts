// 65% boards using the 65_ansi community layout.
// Layers are defined in users/layered/layered.h; this file only adds the
// keys a 65% board has outside the main block. Adjust the right column to
// match your keycaps.
#include "layered.h"

#define LAYOUT_wrapper(...) LAYOUT_65_ansi(__VA_ARGS__)

// clang-format off

// Base layer: main block plus this board's real extra keys.
#define BASE(L) LAYOUT_wrapper( \
    L##_R0, KC_HOME, \
    L##_R1, KC_DEL, \
    L##_R2, KC_PGUP, \
    L##_R3, KC_UP, KC_PGDN, \
    L##_ML, MO(_FN), L##_MR, KC_LEFT, KC_DOWN, KC_RGHT)

// Every other layer: extra keys are transparent, so they keep working.
#define OVER(L) LAYOUT_wrapper( \
    L##_R0, _______, \
    L##_R1, _______, \
    L##_R2, _______, \
    L##_R3, _______, _______, \
    L##_ML, _______, L##_MR, _______, _______, _______)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]  = BASE(QWERTY),
    [_GALLIUM] = OVER(GALLIUM),
    [_NAV]     = OVER(NAV),
    [_MOUSE]   = OVER(MOUSE),
    [_SYM]     = OVER(SYM),
    [_NUMPAD]  = OVER(NUMPAD),
    [_FN]      = OVER(FN),
};

// clang-format on

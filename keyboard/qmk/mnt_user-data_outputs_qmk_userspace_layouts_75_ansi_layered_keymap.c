// 75% boards using the 75_ansi community layout.
// Layers are defined in users/layered/layered.h; this file only adds the
// keys a 75% board has outside the main block. Adjust the function row and
// right column to match your keycaps.
#include "layered.h"

#define LAYOUT_wrapper(...) LAYOUT_75_ansi(__VA_ARGS__)

// clang-format off

// Base layer: main block plus this board's real extra keys.
// Fn takes the Right GUI position, where most 75% boards put it.
#define BASE(L) LAYOUT_wrapper( \
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_PAUS, KC_DEL, \
    L##_R0, KC_HOME, \
    L##_R1, KC_PGUP, \
    L##_R2, KC_PGDN, \
    L##_R3, KC_UP, KC_END, \
    L##_ML, MO(_FN), L##_MR, KC_LEFT, KC_DOWN, KC_RGHT)

// Every other layer: extra keys are transparent, so they keep working.
#define OVER(L) LAYOUT_wrapper( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
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

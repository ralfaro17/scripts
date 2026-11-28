#pragma once
#include QMK_KEYBOARD_H

/* =============================================================================
 * Shared layers for every keyboard size.
 *
 * Each layer is defined once here as the main key block, split into rows:
 *   _R0  Grave/Esc  1 2 3 4 5 6 7 8 9 0 - =  Bspc       (14 keys)
 *   _R1  Tab  Q W E R T Y U I O P [ ]  \                 (14 keys)
 *   _R2  Caps  A S D F G H J K L ; '  Enter              (13 keys)
 *   _R3  LShift  Z X C V B N M , . /  RShift             (12 keys)
 *   _ML  LCtrl LGui LAlt Space RAlt                      (5 keys)
 *   _MR  RCtrl                                           (1 key)
 *
 * Each layout's keymap.c (layouts/<layout>/layered/keymap.c) wraps these rows
 * with the keys only that size has: function row, nav column, arrows, Fn.
 * A new size (60%, 40%) only needs its own small keymap.c.
 * ========================================================================== */

enum layers {
    _QWERTY,
    _GALLIUM,
    _NAV,
    _MOUSE,
    _SYM,
    _NUMPAD,
    _FN,
};

enum custom_keycodes {
    NP_LOCK = SAFE_RANGE, // numpad lock (kanata: toggle-vkey v-numpad)
};

// ---------- OverKeys signals (sent to Windows only) ----------
// Layer signals are held while the layer is active ("held" triggers in
// OverKeys). Gallium is tapped on every base-layout change ("toggle").
#define SIG_NAV     KC_F13
#define SIG_MOUSE   KC_F14
#define SIG_SYM     KC_F15
#define SIG_NUMPAD  KC_F16
#define SIG_GALLIUM KC_F17
// Mouse button signals, held while the button is held
#define SIG_BTN1    KC_F18 // left
#define SIG_BTN3    KC_F19 // middle
#define SIG_BTN2    KC_F20 // right
#define SIG_BTN4    KC_F21 // back
#define SIG_BTN5    KC_F22 // forward

// ---------- Layer keys (tap: key, hold: layer) ----------
#define NAV_F   LT(_NAV, KC_F)
#define MOU_J   LT(_MOUSE, KC_J)
#define NAV_S   LT(_NAV, KC_S)   // Gallium: same physical key as F
#define MOU_H   LT(_MOUSE, KC_H) // Gallium: same physical key as J
#define SYM_SPC LT(_SYM, KC_SPC)
#define NUM_CAP LT(_NUMPAD, KC_CAPS)

#define TO_QWR  DF(_QWERTY)
#define TO_GAL  DF(_GALLIUM)

// clang-format off

// ---------- Qwerty (base) ----------
#define QWERTY_R0 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC
#define QWERTY_R1 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS
#define QWERTY_R2 NUM_CAP, KC_A,    KC_S,    KC_D,    NAV_F,   KC_G,    KC_H,    MOU_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT
#define QWERTY_R3 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT
#define QWERTY_ML KC_LCTL, KC_LGUI, KC_LALT, SYM_SPC, KC_RALT
#define QWERTY_MR KC_RCTL

// ---------- Gallium (base), rowstag angle mod ----------
// Transparent keys fall back to Qwerty (layer 0).
#define GALLIUM_R0 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
#define GALLIUM_R1 _______, KC_B,    KC_L,    KC_D,    KC_C,    KC_Z,    KC_J,    KC_F,    KC_O,    KC_U,    KC_COMM, _______, _______, _______
#define GALLIUM_R2 _______, KC_N,    KC_R,    KC_T,    NAV_S,   KC_V,    KC_Y,    MOU_H,   KC_A,    KC_E,    KC_I,    KC_SLSH, _______
#define GALLIUM_R3 _______, KC_Q,    KC_M,    KC_W,    KC_G,    KC_X,    KC_K,    KC_P,    KC_QUOT, KC_SCLN, KC_DOT,  _______
#define GALLIUM_ML _______, _______, _______, _______, _______
#define GALLIUM_MR _______

// ---------- Navigation (hold F, or S in Gallium) ----------
#define NAV_R0 KC_ESC,  XXXXXXX, TO_QWR,  TO_GAL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO_QWR,  TO_GAL,  XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC
#define NAV_R1 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define NAV_R2 KC_ESC,  KC_LCTL, KC_LSFT, KC_LALT, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TAB,  XXXXXXX, KC_ENT
#define NAV_R3 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_BSPC, KC_ENT,  KC_DEL,  XXXXXXX, _______
#define NAV_ML _______, _______, _______, KC_SPC,  _______
#define NAV_MR _______

// ---------- Mouse (hold J, or H in Gallium) ----------
#define MOUSE_R0 KC_ESC,  XXXXXXX, TO_QWR,  TO_GAL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO_QWR,  TO_GAL,  XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC
#define MOUSE_R1 _______, MS_BTN4, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define MOUSE_R2 KC_ESC,  MS_BTN5, MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, XXXXXXX, _______, KC_RALT, KC_RSFT, KC_RCTL, KC_ESC,  KC_ENT
#define MOUSE_R3 _______, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define MOUSE_ML _______, _______, _______, KC_SPC,  _______
#define MOUSE_MR _______

// ---------- Symbols (hold Space) ----------
#define SYM_R0 KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______
#define SYM_R1 _______, KC_GRV,  KC_TILD, KC_HASH, KC_AMPR, KC_PIPE, KC_CIRC, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX
#define SYM_R2 KC_ESC,  KC_EXLM, KC_UNDS, KC_COLN, KC_EQL,  KC_DLR,  KC_AT,   KC_LPRN, KC_RPRN, KC_QUOT, KC_SCLN, KC_ESC,  _______
#define SYM_R3 _______, KC_PERC, KC_QUES, KC_ASTR, KC_PLUS, KC_BSLS, KC_SLSH, KC_MINS, KC_LABK, KC_RABK, KC_DQUO, _______
#define SYM_ML _______, _______, _______, _______, _______
#define SYM_MR _______

// ---------- Numpad (hold Caps; NP_LOCK keeps it on) ----------
// Caps stays transparent so it still reaches NUM_CAP while the lock is on.
#define NUMPAD_R0 KC_ESC,  XXXXXXX, TO_QWR,  TO_GAL,  XXXXXXX, XXXXXXX, XXXXXXX, NP_LOCK, KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, XXXXXXX, KC_BSPC
#define NUMPAD_R1 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, XXXXXXX, XXXXXXX, XXXXXXX
#define NUMPAD_R2 _______, KC_LCTL, KC_LSFT, KC_LALT, XXXXXXX, XXXXXXX, KC_NUM,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_ESC,  KC_ENT
#define NUMPAD_R3 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_ENT,  _______
#define NUMPAD_ML _______, _______, _______, KC_SPC,  _______
#define NUMPAD_MR KC_ENT

// ---------- Fn (hold the board's Fn key) ----------
// Replaces the stock firmware's Fn layer. Fn + \ enters the bootloader for
// flashing, in the spot kanata used for live reload.
#define FN_R0 _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL
#define FN_R1 _______, _______, _______, _______, _______, _______, KC_INS,  _______, _______, _______, _______, KC_PSCR, KC_SCRL, QK_BOOT
#define FN_R2 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
#define FN_R3 _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, _______
#define FN_ML _______, _______, _______, _______, _______
#define FN_MR _______

// clang-format on

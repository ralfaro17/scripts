#pragma once

// Settings are #undef'd first so they override any keyboard-level defaults.

// Tap-hold (kanata: tap-hold 200 200)
#undef TAPPING_TERM
#define TAPPING_TERM 200
#undef QUICK_TAP_TERM
#define QUICK_TAP_TERM 200

// Cursor movement: constant 10 px every 20 ms, no acceleration
// (kanata: movemouse 20 10)
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 20
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 20
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 10
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 1
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 0

// Wheel: one notch on tap; held past 300 ms, one notch every 50 ms
// (kanata: tap-hold 300 300 with mwheel 50 120)
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 300
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 50
#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 1
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0

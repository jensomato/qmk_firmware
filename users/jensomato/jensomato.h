#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _KOY 0
#define _GAME 1
#define _NUM 2
#define _NEO3 3
#define _NAV 4
#define _MOUSE 5
#define _FUNC 6
#define _FKEYS 7
#define _ADJUST 8
#define _WM 9
// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single tap
    TRIPLE_TAP,
    TRIPLE_HOLD,
} td_state_t;

enum custom_keycodes {
    CAPSWORD = SAFE_RANGE,
};

// Tap Dance keycodes
enum td_keycodes {
    TD_TAB, // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
    TD_COPY,
    TD_PASTE,
    TD_UNDO,
    TD_SELECT,
    TD_CTL_A,
    TD_APP,
    TD_PASS,
    TD_LEADER,
    TD_SHIFT,
    TD_WM,
    TD_WM1,
    TD_WM2,
    TD_WM3,
    TD_WM4,
    TD_WM5,
    TD_WM6,
    TD_WM7,
    TD_WM8,
    TD_WM9,
    TD_WM_DOWN,
    TD_WM_UP,
    TD_WM_LEFT,
    TD_WM_RIGHT,
};

#define APP     TD(TD_APP)
#define A_COLN  LALT_T(KC_LANG1)
#define A_BSLS  LALT_T(KC_LANG8)
#define BSPC    LT(_NUM, KC_BSPC)
#define C_A     C(DE_A)
#define C_C     C(DE_C)
#define C_COMM  C(DE_COMM)
#define C_F     C(DE_F)
#define C_V     C(DE_V)
#define C_W     C(DE_W)
#define C_X     C(DE_X)
#define C_Y     C(DE_Y)
#define C_Z     C(DE_Z)
#define C_LPRN  RCTL_T(KC_LANG4)
#define C_RCBR  LCTL_T(KC_LANG5)
#define COPY    TD(TD_COPY)
#define ENTER   LT(_NEO3, KC_ENT)
//#define ESC     LT(_NEO3, KC_ESC)
#define ESC     KC_ESC
#define FUNC_01 XXXXXXX
#define FUNC_02 XXXXXXX
#define FUNC_03 XXXXXXX
#define FUNC_04 XXXXXXX
#define FUNC_05 XXXXXXX
#define FUNC_06 XXXXXXX
#define FUNC_07 XXXXXXX
#define FUNC_08 XXXXXXX
#define FUNC_09 S(KC_F6)   // IntelliJ Rename
#define FUNC_10 C(DE_SCLN) // IntelliJ AceJump
#define FUNC_11 XXXXXXX
#define FUNC_12 A(DE_1)    // rofi pass autotype all
#define FUNC_13 XXXXXXX
#define FUNC_14 A(DE_3)    // rofi pass autotype password
#define FUNC_15 XXXXXXX
#define FUNC_16 XXXXXXX
#define FUNC_17 XXXXXXX
#define FUNC_18 XXXXXXX
#define FUNC_19 XXXXXXX
#define FUNC_20 XXXXXXX
#define FUNC_21 XXXXXXX
#define FUNC_22 XXXXXXX
#define FUNC_23 XXXXXXX
#define FUNC_24 XXXXXXX
#define FUNC_25 XXXXXXX
#define FUNC_26 OSL(_WM)
#define FUNC_27 XXXXXXX
#define FUNC_28 XXXXXXX
#define FUNC_29 G(S(DE_Q))  // i3 close window
#define FUNC_30 XXXXXXX
#define FUNC_31 XXXXXXX
#define FUNC_32 XXXXXXX
#define FUNC_33 TD(TD_WM1)
#define FUNC_34 XXXXXXX
#define FUNC_35 OSL(_WM)
#define G_MINS  RGUI_T(KC_LANG2)
#define G_SLSH  LGUI_T(KC_LANG7)
#define HOME_T  RCTL_T(DE_T)
#define HOME_I  LCTL_T(DE_I)
#define HOME_E  LSFT_T(DE_E)
//#define HOME_F  LT(_NEO3, DE_F)
#define HOME_F  DE_F
#define HOME_R  RSFT_T(DE_R)
#define HOME_A  LGUI_T(DE_A)
#define HOME_N  RGUI_T(DE_N)
#define HOME_H  LALT_T(DE_H)
#define HOME_S  LALT_T(DE_S)
#define LEADER  TD(TD_LEADER)
#define MOUSE   LT(_MOUSE, KC_F12)
#define NA_BSPC LSFT_T(KC_BSPC)
#define NA_TMUX TD(TD_CTL_A)
#define NA_SWIT TD(TD_TAB)
#define PASS    TD(TD_PASS)
#define PASTE   TD(TD_PASTE)
#define SELECT  TD(TD_SELECT)
#define S_RPRN  RSFT_T(KC_LANG3)
#define S_LCBR  LSFT_T(KC_LANG6)
#define SHIFT   TD(TD_SHIFT)
#define SPACE   LT(_NAV, KC_SPC)
#define TAB     LT(_WM, KC_TAB)
#define UNDO    TD(TD_UNDO)
#define TDUP      TD(TD_UP)
#define TDDOWN    TD(TD_DOWN)
#define WM_1    TD(TD_WM1)
#define WM_2    TD(TD_WM2)
#define WM_3    TD(TD_WM3)
#define WM_4    TD(TD_WM4)
#define WM_5    TD(TD_WM5)
#define WM_6    TD(TD_WM6)
#define WM_7    TD(TD_WM7)
#define WM_8    TD(TD_WM8)
#define WM_9    TD(TD_WM9)
#define WM_DOWN TD(TD_WM_DOWN)
#define WM_LEFT TD(TD_WM_LEFT)
#define WM_RGHT TD(TD_WM_RIGHT)
#define WM_UP   TD(TD_WM_UP)

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Declare your tapdance functions:
// `finished` and `reset` functions for each tapdance keycode
void cstab_finished(qk_tap_dance_state_t *state, void *user_data);
void cstab_reset(qk_tap_dance_state_t *state, void *user_data);
void select_finished(qk_tap_dance_state_t *state, void *user_data);
void select_reset(qk_tap_dance_state_t *state, void *user_data);
void send_with_gui(uint16_t keycode);
void send_with_shift_gui(uint16_t keycode);

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
#define _SHIFT 2
#define _NUM 3
#define _NEO3 4
#define _NAV 5
#define _MOUSE 6
#define _NUM2 7
#define _FKEYS 8
#define _ADJUST 9
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

// Tap Dance keycodes
enum td_keycodes {
    TD_TAB, // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
    TD_COPY,
    TD_PASTE,
    TD_UNDO,
    TD_SELECT,
    TD_MOUSE,
    TD_CTL_A,
    TD_SENTER,
    TD_APP,
    TD_PASS,
    TD_LEADER,
    TD_SHIFT,
};

#define APP     TD(TD_APP)
#define A_COLN  LALT_T(KC_LANG1)
#define A_BSLS  LALT_T(KC_LANG8)
#define BSPC    LT(_NEO3, KC_BSPC)
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
#define DEL     LT(_NEO3, KC_DEL)
#define ENTER   LT(_NUM, KC_ENT)
#define ESC     LT(_NEO3, KC_ESC)
#define ESCAPE  LT(_MOUSE, KC_ESC)
#define G_MINS  RGUI_T(KC_LANG2)
#define G_SLSH  LGUI_T(KC_LANG7)
#define HOME_T  RCTL_T(DE_T)
#define HOME_I  LCTL_T(DE_I)
#define HOME_E  LSFT_T(DE_E)
#define HOME_F  LT(_NEO3, DE_F)
#define HOME_R  RSFT_T(DE_R)
#define HOME_A  LGUI_T(DE_A)
#define HOME_N  RGUI_T(DE_N)
#define HOME_H  LALT_T(DE_H)
#define HOME_S  LALT_T(DE_S)
#define LEADER  TD(TD_LEADER)
#define MOUSE   TG(_MOUSE)
#define CAPS    TD(TD_MOUSE)
#define NA_BSPC LSFT_T(KC_BSPC)
#define NA_TMUX TD(TD_CTL_A)
#define NA_SWIT TD(TD_TAB)
#define PASS    TD(TD_PASS)
#define PASTE   TD(TD_PASTE)
#define SELECT  TD(TD_SELECT)
#define S_ENTER TD(TD_SENTER)
#define S_RPRN  RSFT_T(KC_LANG3)
#define S_LCBR  LSFT_T(KC_LANG6)
#define SHIFT   TD(TD_SHIFT)
#define SPACE   LT(_NAV, KC_SPC)
#define TAB     LT(_MOUSE, KC_TAB)
#define UNDO    TD(TD_UNDO)
#define LEFT    TD(TD_LEFT)
#define RIGHT   TD(TD_RIGHT)
#define TDUP      TD(TD_UP)
#define TDDOWN    TD(TD_DOWN)

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Declare your tapdance functions:
// `finished` and `reset` functions for each tapdance keycode
void cstab_finished(qk_tap_dance_state_t *state, void *user_data);
void cstab_reset(qk_tap_dance_state_t *state, void *user_data);
void select_finished(qk_tap_dance_state_t *state, void *user_data);
void select_reset(qk_tap_dance_state_t *state, void *user_data);

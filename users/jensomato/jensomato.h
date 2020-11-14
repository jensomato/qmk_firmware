#include "keymap_german.h"
#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _KOY 0
#define _SHIFT 1
#define _NUM 2
#define _NEO3 3
#define _NAV 4
#define _MOUSE 5
#define _NUM2 6
#define _FKEYS 7
#define _ADJUST 8
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
};

#define APP     TD(TD_APP)
#define BSPC    LT(_SHIFT, KC_BSPC)
#define C_A     C(DE_A)
#define C_C     C(DE_C)
#define C_COMM  C(DE_COMM)
#define C_F     C(DE_F)
#define C_V     C(DE_V)
#define C_W     C(DE_W)
#define C_X     C(DE_X)
#define C_Y     C(DE_Y)
#define C_Z     C(DE_Z)
#define COPY    TD(TD_COPY)
#define DEL     LT(_NAV, KC_DEL)
#define ENTER   LT(_NUM, KC_ENT)
#define ESC     LT(_NEO3, KC_ESC)
#define ESCAPE  LT(_MOUSE, KC_ESC)
#define HOME_T  RCTL_T(DE_T)
#define HOME_I  LCTL_T(DE_I)
#define HOME_E  LSFT_T(DE_E)
#define HOME_F  LT(_NEO3, DE_F)
#define HOME_R  RSFT_T(DE_R)
#define HOME_A  LGUI_T(DE_A)
#define HOME_N  RGUI_T(DE_N)
#define HOME_H  LALT_T(DE_H)
#define HOME_S  LALT_T(DE_S)
#define MOUSE   TG(_MOUSE)
#define CAPS    TD(TD_MOUSE)
#define NA_TMUX TD(TD_CTL_A)
#define NA_SWIT TD(TD_TAB)
#define PASS    TD(TD_PASS)
#define PASTE   TD(TD_PASTE)
#define SELECT  TD(TD_SELECT)
#define S_ENTER TD(TD_SENTER)
#define SPACE   LT(_NAV, KC_SPC)
#define TAB     LT(_FKEYS, KC_TAB)
#define UNDO    TD(TD_UNDO)

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Declare your tapdance functions:
// `finished` and `reset` functions for each tapdance keycode
void cstab_finished(qk_tap_dance_state_t *state, void *user_data);
void cstab_reset(qk_tap_dance_state_t *state, void *user_data);
void select_finished(qk_tap_dance_state_t *state, void *user_data);
void select_reset(qk_tap_dance_state_t *state, void *user_data);

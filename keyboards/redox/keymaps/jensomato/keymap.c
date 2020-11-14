#include QMK_KEYBOARD_H

#include "keymap_german.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

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

enum custom_keycodes {
  KOY = SAFE_RANGE,
  NEO3,
  NEO4,
  NAV,
  MOUSE,
  NUM,
  FKEYS,
  ADJUST,
  GTAB,
  KI_P,
  KI_F,
  ENT_D,
  CAP_SPC,
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

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void cstab_finished(qk_tap_dance_state_t *state, void *user_data);
void cstab_reset(qk_tap_dance_state_t *state, void *user_data);
void select_finished(qk_tap_dance_state_t *state, void *user_data);
void select_reset(qk_tap_dance_state_t *state, void *user_data);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GTAB:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_NAV)) {
                    SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
                    return false;
                }
            }
            break;
        case ENT_D:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_UP) SS_TAP(X_END) SS_TAP(X_ENT));
                return false;
            }
            break;
        case ENTER:
            if (record->event.pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
                    SEND_STRING(SS_TAP(X_UP) SS_TAP(X_END) SS_TAP(X_ENT));
                    return false;
                }
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_KOY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,DE_K    ,DE_DOT  ,DE_O    ,DE_COMM ,DE_Y    ,XXXXXXX ,                          XXXXXXX ,DE_V    ,DE_G    ,DE_C    ,DE_L    ,DE_Z    ,DE_SS   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ESC     ,HOME_H  ,HOME_A  ,HOME_E  ,HOME_I  ,DE_U    ,XXXXXXX ,                          XXXXXXX ,DE_D    ,HOME_T  ,HOME_R  ,HOME_N  ,HOME_S  ,HOME_F  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LEAD ,DE_X    ,DE_Q    ,DE_AE   ,DE_UE   ,DE_OE   ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,DE_B    ,DE_P    ,DE_W    ,DE_M    ,DE_J    ,KC_LALT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_LGUI ,     BSPC    ,    DEL     ,ESCAPE  ,        TAB     ,SPACE   ,    ENTER   ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SHIFT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,S(DE_K) ,DE_DOT  ,S(DE_O) ,DE_COMM ,S(DE_Y) ,_______ ,                          _______ ,S(DE_V) ,S(DE_G) ,S(DE_C) ,S(DE_L) ,S(DE_Z) ,S(DE_SS),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,S(DE_H) ,S(DE_A) ,S(DE_E) ,S(DE_I) ,S(DE_U) ,_______ ,                          _______ ,S(DE_D) ,S(DE_T) ,S(DE_R) ,S(DE_N) ,S(DE_S) ,S(DE_F) ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,S(DE_X) ,S(DE_Q) ,S(DE_AE),S(DE_UE),S(DE_OE),_______ ,_______ ,        _______ ,_______ ,S(DE_B) ,S(DE_P) ,S(DE_W) ,S(DE_M) ,S(DE_J) ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,DE_0    ,DE_7    ,DE_8    ,DE_9    ,DE_PLUS ,DE_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LALT ,KC_LGUI ,KC_LSFT ,KC_LCTL ,XXXXXXX ,_______ ,                          _______ ,DE_COMM ,DE_4    ,DE_5    ,DE_6    ,DE_COLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,DE_0    ,DE_1    ,DE_2    ,DE_3    ,DE_ASTR ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,DE_0    ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘

  ),
  [_NEO3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,DE_AT   ,DE_UNDS ,DE_LBRC ,DE_RBRC ,DE_CIRC ,_______ ,                          _______ ,DE_EXLM ,DE_LABK ,DE_RABK ,DE_EQL  ,DE_AMPR ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_BSLS ,DE_SLSH ,DE_LCBR ,DE_RCBR ,DE_ASTR ,_______ ,                          _______ ,DE_QUES ,DE_LPRN ,DE_RPRN ,DE_MINS ,DE_COLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_HASH ,DE_DLR  ,DE_PIPE ,DE_TILD ,DE_GRV  ,_______ ,_______ ,        _______ ,_______ ,DE_PLUS ,DE_PERC ,DE_DQUO ,DE_QUOT ,DE_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,C_W     ,XXXXXXX ,XXXXXXX ,_______ ,C_Y     ,XXXXXXX ,                          _______ ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_INS  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MOUSE   ,KC_LALT ,NA_TMUX ,KC_LSFT ,KC_LCTL ,C_Z     ,XXXXXXX ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_DEL  ,KC_TAB  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,C_A     ,C_X     ,C_C     ,C_V     ,C_F     ,_______ ,_______ ,        _______ ,_______ ,SELECT  ,COPY    ,PASTE   ,UNDO    ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    APP     ,PASS    ,        _______ ,_______ ,NA_SWIT ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,DE_0    ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,DE_1    ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_6    ,DE_7    ,DE_8    ,DE_9    ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,DE_2    ,DE_3    ,DE_4    ,DE_5    ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,_______ ,     _______ ,    KC_SPC  ,_______ ,        _______ ,DE_0    ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_FKEYS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LALT ,KC_LGUI ,KC_LSFT ,KC_LCTL ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F12  ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    XXXXXXX ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_WH_U ,KC_WH_L ,KC_MS_U ,KC_WH_R ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MOUSE   ,KC_LALT ,KC_LGUI ,KC_LCTL ,KC_LSFT ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_WH_D ,KC_MS_L ,KC_MS_D ,KC_MS_R ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_LGUI      ,_______ ,    _______ ,KC_LCTL ,        KC_BTN1 ,KC_BTN3 ,    KC_BTN2 ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};

// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void cstab_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LGUI));
            tap_code16(KC_TAB);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSHIFT));
            register_mods(MOD_BIT(KC_LCTRL));
            break;
        default:
            break;
    }
}

void cstab_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSHIFT));
            unregister_mods(MOD_BIT(KC_LCTRL));
            break;
        default:
            break;
    }
}

void senter_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSHIFT));
            tap_code16(KC_ENT);
            break;
        case SINGLE_HOLD:
            layer_on(_FKEYS);
            break;
        default:
            break;
    }
}

void senter_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LSHIFT));
            break;
        case SINGLE_HOLD:
            layer_off(_FKEYS);
            break;
        default:
            break;
    }
}

void select_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL));
            break;
        case DOUBLE_TAP:
            SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
            break;
        case TRIPLE_TAP:
            SEND_STRING(SS_LCTL("a"));
            break;
        default:
            break;
    }
}

void select_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void nav_app_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LGUI));
            tap_code16(DE_D);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
}

void nav_app_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
}

void nav_pass_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LGUI));
            tap_code16(DE_P);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_LSFT | MOD_LCTL);
            break;
        default:
            break;
    }
}

void nav_pass_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_LSFT | MOD_LCTL);
            break;
        default:
            break;
    }
}

void nav_ctla_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LCTRL));
            tap_code16(DE_A);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
}

void nav_ctla_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LCTRL));
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    //[CS_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cstab_finished, cstab_reset),
    [TD_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_F12, G(KC_TAB)),
    [TD_SENTER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, senter_layer_finished, senter_layer_reset),
    [TD_COPY] = ACTION_TAP_DANCE_DOUBLE(C(DE_C), C(DE_X)),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(C(DE_V), C(S(DE_V))),
    [TD_UNDO] = ACTION_TAP_DANCE_DOUBLE(C(DE_Z), C(S(DE_Z))),
    [TD_SELECT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, select_finished, select_reset),
    [TD_MOUSE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_CAPS, _MOUSE),
    [TD_CTL_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_ctla_finished, nav_ctla_reset),
    [TD_APP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_app_finished, nav_app_reset),
    [TD_PASS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_pass_finished, nav_pass_reset),
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        SEQ_ONE_KEY(KC_ENT) {
            SEND_STRING(SS_TAP(X_END) SS_TAP(X_ENT));
        }
        SEQ_TWO_KEYS(KC_ENT, KC_ENT) {
            SEND_STRING(SS_TAP(X_UP) SS_TAP(X_END) SS_TAP(X_ENT));
        }
        SEQ_TWO_KEYS(DE_D, DE_D) {
            SEND_STRING(SS_TAP(X_END) SS_DOWN(X_LSFT) SS_TAP(X_HOME) SS_UP(X_LSFT) SS_TAP(X_BSPC));
        }
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_I:
        case HOME_E:
            return TAPPING_TERM + 100;
        case NA_SWIT:
            return 100;
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _SHIFT, _FKEYS);
}

#include QMK_KEYBOARD_H

#include "keymap_german.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _KOY 0
#define _NUM 1
#define _NEO3 2
#define _CAP 3
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


#define C_A     C(DE_A)
#define C_C     C(DE_C)
#define C_COMM  C(DE_COMM)
#define C_F     C(DE_F)
#define C_V     C(DE_V)
#define C_W     C(DE_W)
#define C_X     C(DE_X)
#define C_Y     C(DE_Y)
#define C_Z     C(DE_Z)
#define DEL     LT(_NEO3, KC_DEL)
#define DOT     LT(_CAP, DE_DOT)
#define BSPC    SFT_T(KC_BSPC)
#define ENTER   TD(TD_ENT)
#define ESC     LT(_NEO3, KC_ESC)
#define ESCAPE  LT(_FKEYS, KC_ESC)
#define HOME_T  RSFT_T(DE_T)
#define HOME_I  LSFT_T(DE_I)
#define HOME_E  LCTL_T(DE_E)
#define HOME_F  LT(_NEO3, DE_F)
#define HOME_R  RCTL_T(DE_R)
#define HOME_A  LGUI_T(DE_A)
#define HOME_N  RGUI_T(DE_N)
#define HOME_H  LALT_T(DE_H)
#define HOME_S  RALT_T(DE_S)
#define MOUSE   TG(_MOUSE)
#define NU_BSPC LT(_NEO3,KC_BSPC)
#define NU_DEL  LGUI_T(KC_DEL)
#define NU_ESC  SGUI_T(KC_ESC)
#define SPACE   LT(_NAV, KC_SPC)
#define TAB     LT(_FKEYS, KC_TAB)

// Tap Dance keycodes
enum td_keycodes {
    CS_TAB, // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
    TD_ENT,
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single tap
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void cstab_finished(qk_tap_dance_state_t *state, void *user_data);
void cstab_reset(qk_tap_dance_state_t *state, void *user_data);
void enter_layer_finished(qk_tap_dance_state_t *state, void *user_data);
void enter_layer_reset(qk_tap_dance_state_t *state, void *user_data);

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
        case CAP_SPC:
            if (record->event.pressed) {
                SEND_STRING(". ");
                set_oneshot_mods(MOD_LSFT);
            } else {
                //clear_oneshot_mods();
                //layer_off(_CAP);
            }
            return false;
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_KOY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,DE_K    ,DOT     ,DE_O    ,DE_COMM ,DE_Y    ,XXXXXXX ,                          XXXXXXX ,DE_V    ,DE_G    ,DE_C    ,DE_L    ,DE_Z    ,DE_SS   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ESC     ,HOME_H  ,HOME_A  ,HOME_E  ,HOME_I  ,DE_U    ,XXXXXXX ,                          XXXXXXX ,DE_D    ,HOME_T  ,HOME_R  ,HOME_N  ,HOME_S  ,HOME_F  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LEAD ,DE_X    ,DE_Q    ,DE_AE   ,DE_UE   ,DE_OE   ,C_C     ,C_V     ,        XXXXXXX ,KC_LEAD ,DE_B    ,DE_P    ,DE_W    ,DE_M    ,DE_J    ,KC_LALT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_LGUI ,     BSPC    ,    DEL     ,ESCAPE  ,        TAB     ,SPACE   ,    ENTER   ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,DE_0    ,DE_1    ,DE_2    ,DE_3    ,DE_PLUS ,DE_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LALT ,KC_LGUI ,KC_LCTL ,KC_LSFT ,XXXXXXX ,_______ ,                          _______ ,DE_COMM ,DE_4    ,DE_5    ,DE_6    ,DE_COLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,DE_DOT  ,DE_7    ,DE_8    ,DE_9    ,DE_ASTR ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,_______ ,     NU_BSPC ,    NU_DEL  ,NU_ESC  ,        _______ ,_______ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘

  ),
  [_NEO3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,DE_AT   ,DE_UNDS ,DE_LBRC ,DE_RBRC ,DE_CIRC ,_______ ,                          _______ ,DE_EXLM ,DE_LABK ,DE_RABK ,DE_EQL  ,DE_AMPR ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_BSLS ,KC_PSLS ,DE_LCBR ,DE_RCBR ,DE_ASTR ,_______ ,                          _______ ,DE_QUES ,DE_LPRN ,DE_RPRN ,DE_MINS ,DE_COLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_HASH ,DE_DLR  ,DE_PIPE ,DE_TILD ,DE_GRV  ,_______ ,_______ ,        _______ ,_______ ,DE_PLUS ,DE_PERC ,DE_DQUO ,DE_QUOT ,DE_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_CAP] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,KC_LALT ,KC_LGUI ,KC_LCTL ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F12  ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,CAP_SPC ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,C_W     ,XXXXXXX ,XXXXXXX ,C_COMM  ,C_Y     ,XXXXXXX ,                          _______ ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_INS  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MOUSE   ,KC_LALT ,KC_LGUI ,KC_LCTL ,KC_LSFT ,C_Z     ,XXXXXXX ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_DEL  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,C_A     ,C_X     ,C_C     ,C_V     ,C_F     ,_______ ,_______ ,        _______ ,_______ ,_______ ,XXXXXXX ,KC_LEAD ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    LGUI_T(KC_F12) ,C_S_T(KC_ESC) ,        _______ ,_______ ,TD(CS_TAB) ,     _______ ,_______ ,_______ ,_______
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
     _______ ,KC_LALT ,KC_LGUI ,KC_LCTL ,KC_LSFT ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F12  ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_WH_U ,KC_WH_L ,KC_MS_U ,KC_WH_R ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MOUSE   ,XXXXXXX ,KC_BTN2 ,KC_BTN3 ,KC_BTN1 ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_WH_D ,KC_MS_L ,KC_MS_D ,KC_MS_R ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_LGUI      ,_______ ,    _______ ,KC_LCTL ,        KC_LALT ,KC_ENT  ,    KC_SPC  ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
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

void enter_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            tap_code16(KC_ENT);
            break;
        case SINGLE_HOLD:
            layer_on(_NUM);
            break;
        case DOUBLE_HOLD:
            layer_on(_FKEYS);
            break;
        default:
            break;
    }
}

void enter_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(_NUM);
            break;
        case DOUBLE_HOLD:
            layer_off(_FKEYS);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [CS_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cstab_finished, cstab_reset),
    [TD_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter_layer_finished, enter_layer_reset),
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

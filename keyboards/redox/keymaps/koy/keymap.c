#include QMK_KEYBOARD_H

#include "keymap_german.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _KOY 0
#define _NEO3 1
#define _NEO4 2
#define _NAV 3
#define _MOUSE 4
#define _NUM 5
#define _FKEYS 6
#define _ADJUST 7
#define _NAV1 8

enum custom_keycodes {
  KOY = SAFE_RANGE,
  NEO3,
  NEO4,
  NAV,
  MOUSE,
  NUM,
  FKEYS,
  ADJUST,
  NAV1,
};

// Shortcut to make keymap more readable
#define KC_BKSL KC_BSLASH
#define SYM_L   MO(_NEO3)
#define KC_NEO3 LT(_NEO3, KC_ESC)
#define F_NEO3  LT(_NEO3, DE_F)
#define L_NEO4  LT(_NUM, KC_TAB)
#define R_NEO4  LT(_NEO4, KC_ENT)
#define R_SHFT  RSFT_T(KC_SPC)
#define L_SHFT  LSFT_T(KC_BSPC)
#define BKSP    LT(_NAV1, KC_BSPC)
//
#define H_SHFT  LSFT_T(DE_H)
#define A_CTL   LCTL_T(DE_A)
#define E_ALT   LALT_T(DE_E)
#define I_GUI   LGUI_T(DE_I)
#define S_SHFT  RSFT_T(DE_S)
#define N_CTL   RCTL_T(DE_N)
#define R_ALT   RALT_T(DE_R)
#define T_GUI   RGUI_T(DE_T)
#define L_NEO3  LT(_NEO3, KC_DEL)
#define R_NEO3  LT(_NEO3, KC_ENT)
#define KC_NAV  LT(_NAV, KC_ESC)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_PSLS)
#define L_CTL   LCTL_T(KC_TAB)
// keys for nav layer
#define S_LEFT  S(KC_LEFT)
#define S_RGHT  S(KC_RGHT)
#define S_UP    S(KC_UP)
#define S_DOWN  S(KC_DOWN)
#define S_END   S(KC_END)
#define S_HOME  S(KC_HOME)
#define C_LEFT  C(KC_LEFT)
#define C_RGHT  C(KC_RGHT)
#define C_TAB   C(KC_TAB)
#define CS_RGHT C(S(KC_RGHT))
#define CS_LEFT C(S(KC_LEFT))
#define CS_TAB  C(S(KC_TAB))
#define C_C     C(DE_C)
#define C_V     C(DE_V)
#define C_X     C(DE_X)
#define C_A     C(DE_A)
#define C_Y     C(DE_Y)
#define C_Z     C(DE_Z)
#define C_W     C(DE_W)
#define C_F     C(DE_F)

#define KC_NAGR LT(_NEO4, DE_CIRC)
#define KC_NAMI LT(_NEO4, DE_SS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)
#define GUI OSM(MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_KOY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,DE_K    ,DE_DOT  ,DE_O    ,DE_COMM ,DE_Y    ,SYM_L   ,                          SYM_L   ,DE_V    ,DE_G    ,DE_C    ,DE_L    ,DE_Z    ,DE_SS   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NEO3 ,DE_H    ,DE_A    ,DE_E    ,DE_I    ,DE_U    ,KC_DEL  ,                          DE_PLUS ,DE_D    ,DE_T    ,DE_R    ,DE_N    ,DE_S    ,F_NEO3  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,DE_X    ,DE_Q    ,DE_AE   ,DE_UE   ,DE_OE   ,KC_NAV  ,KC_PGDN ,        KC_HOME ,KC_ADEN ,DE_B    ,DE_P    ,DE_W    ,DE_M    ,DE_J    ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,GUI     ,     BKSP    ,    L_NEO4  ,L_CTL   ,        KC_LALT ,R_NEO4  ,    R_SHFT  ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  [_NEO3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_EXLM ,DE_UNDS ,DE_LBRC ,DE_RBRC ,DE_CIRC ,_______ ,                          _______ ,DE_EXLM ,DE_LABK ,DE_RABK ,DE_EQL  ,DE_AMPR ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_BSLS ,KC_PSLS ,DE_LCBR ,DE_RCBR ,DE_ASTR ,_______ ,                          _______ ,DE_QUES ,DE_LPRN ,DE_RPRN ,DE_MINS ,DE_COLN ,DE_AT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,DE_HASH ,DE_DLR  ,DE_PIPE ,DE_TILD ,DE_GRV  ,_______ ,_______ ,        _______ ,_______ ,DE_PLUS ,DE_PERC ,DE_DQUO ,DE_QUOT ,DE_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,KC_LALT ,     KC_LCTL ,    _______ ,_______ ,        _______ ,_______ ,    KC_LALT ,     KC_KP_0 ,KC_PDOT ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NEO4] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_PGUP ,KC_BSPC ,KC_UP   ,KC_DEL  ,KC_PGDN ,_______ ,                          _______ ,XXXXXXX ,DE_7    ,DE_8    ,DE_9    ,DE_PLUS ,DE_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_HOME ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_END  ,_______ ,                          _______ ,XXXXXXX ,DE_4    ,DE_5    ,DE_6    ,DE_COMM ,DE_DOT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,DE_COLN ,DE_1    ,DE_2    ,DE_3    ,DE_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,_______ ,    DE_0    ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F1   ,KC_F4   ,KC_F7   ,KC_F10  ,KC_PGDN ,_______ ,                          _______ ,XXXXXXX ,DE_7    ,DE_8    ,DE_9    ,DE_PLUS ,DE_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,DE_4    ,DE_5    ,DE_6    ,DE_COMM ,DE_DOT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F3   ,KC_F6   ,KC_F9   ,KC_F12  ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,DE_COLN ,DE_1    ,DE_2    ,DE_3    ,DE_SCLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,MO(_FKEYS) ,    DE_0    ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_FKEYS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F1   ,KC_F4   ,KC_F7   ,KC_F10  ,KC_PGDN ,_______ ,                          _______ ,XXXXXXX ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,DE_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,DE_DOT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F3   ,KC_F6   ,KC_F9   ,KC_F12  ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F12  ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,_______ ,    DE_0    ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,C_W     ,CS_LEFT ,S_UP    ,CS_RGHT ,C_Y     ,SYM_L   ,                          SYM_L   ,KC_PGUP ,C_LEFT  ,KC_UP   ,C_RGHT  ,DE_SS   ,DE_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,C_A     ,S_LEFT  ,S_DOWN  ,S_RGHT  ,C_Z     ,KC_ESC  ,                          DE_PLUS ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_END  ,C_F     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,S_HOME  ,C_X     ,C_C     ,C_V     ,S_END   ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_HOME ,CS_TAB  ,KC_TAB  ,C_TAB   ,KC_END  ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,GUI     ,     L_NEO4  ,    L_NEO3  ,KC_LCTL ,        KC_LALT ,KC_ENT  ,    KC_SPC  ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,C_W     ,CS_LEFT ,S_UP    ,CS_RGHT ,C_Y     ,SYM_L   ,                          SYM_L   ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,DE_SS   ,DE_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,C_Z     ,KC_ESC  ,                          DE_PLUS ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_TAB  ,C_F     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,C_A     ,C_X     ,C_C     ,C_V     ,S_END   ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,DE_COMM ,CS_TAB  ,KC_TAB  ,C_TAB   ,KC_END  ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,GUI     ,     L_NEO4  ,    L_NEO3  ,KC_LCTL ,        KC_LALT ,KC_ENT  ,    KC_SPC  ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                                            KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,C_W     ,CS_LEFT ,S_UP    ,CS_RGHT ,C_Y     ,SYM_L   ,                          SYM_L   ,XXXXXXX ,XXXXXXX ,KC_MS_U ,XXXXXXX ,XXXXXXX ,DE_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,C_A     ,S_LEFT  ,S_DOWN  ,S_RGHT  ,C_Z     ,KC_ESC  ,                          DE_PLUS ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,XXXXXXX ,DE_F    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,S_HOME  ,C_X     ,C_C     ,C_V     ,S_END   ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,DE_B    ,KC_HOME ,KC_TAB  ,KC_END  ,DE_J    ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,GUI     ,     L_NEO4  ,    L_NEO3  ,KC_LCTL ,        KC_LALT ,KC_ENT  ,    KC_SPC  ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
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

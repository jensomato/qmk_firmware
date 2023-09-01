#include "action.h"
#include "quantum.h"
#include "jensomato.h"
#include "casemodes.h"

void send_with_gui(uint16_t keycode) {
    register_code(KC_LGUI);
    tap_code16(keycode);
    unregister_code(KC_LGUI);
}

void send_with_shift_gui(uint16_t keycode) {
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    tap_code16(keycode);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
}

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Determine the tapdance state to return
uint8_t cur_dance(tap_dance_state_t *state) {
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

void select_finished(tap_dance_state_t *state, void *user_data) {
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

void select_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void nav_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            register_mods(MOD_LSFT);
            break;
        default:
            break;
    }
}

void nav_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_LSFT);
            break;
        default:
            break;
    }
}

void double_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case DQUO:
                    tap_code16(DE_DQUO);
                    break;
                case QUOT:
                    tap_code16(DE_QUOT);
                    break;
            }
            break;
        case DOUBLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case DQUO:
                    tap_code16(DE_DQUO);
                    tap_code16(DE_DQUO);
                    tap_code16(KC_LEFT);
                    break;
                case QUOT:
                    tap_code16(DE_QUOT);
                    tap_code16(DE_QUOT);
                    tap_code16(KC_LEFT);
                    break;
            }
            break;
        default:
            break;
    }
}

void double_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void cursor_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case LEFT:
                    register_mods(MOD_LCTL);
                    register_code(KC_LEFT);
                    break;
                case RIGHT:
                    register_mods(MOD_LCTL);
                    register_code(KC_RIGHT);
                    break;
            }
            break;
        case SINGLE_HOLD:
        case DOUBLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case LEFT:
                    register_mods(MOD_LCTL|MOD_LSFT);
                    register_code(KC_LEFT);
                    break;
                case RIGHT:
                    register_mods(MOD_LCTL|MOD_LSFT);
                    register_code(KC_RIGHT);
                    break;
            }
            break;
        default:
            break;
    }
}

void cursor_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case LEFT:
                    unregister_code(KC_LEFT);
                    unregister_mods(MOD_LCTL);
                    break;
                case RIGHT:
                    unregister_code(KC_RIGHT);
                    unregister_mods(MOD_LCTL);
                    break;
            }
            break;
        case SINGLE_HOLD:
        case DOUBLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case LEFT:
                    unregister_code(KC_LEFT);
                    unregister_mods(MOD_LCTL|MOD_LSFT);
                    break;
                case RIGHT:
                    unregister_code(KC_RIGHT);
                    unregister_mods(MOD_LCTL|MOD_LSFT);
                    break;
            }
            break;
        default:
            break;
    }
}

void wm_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case TD(TD_WM1):
                    send_with_gui(DE_1);
                    break;
                case TD(TD_WM2):
                    send_with_gui(DE_2);
                    break;
                case TD(TD_WM3):
                    send_with_gui(DE_3);
                    break;
                case TD(TD_WM4):
                    send_with_gui(DE_4);
                    break;
                case TD(TD_WM5):
                    send_with_gui(DE_5);
                    break;
                case TD(TD_WM6):
                    send_with_gui(DE_6);
                    break;
                case TD(TD_WM7):
                    send_with_gui(DE_7);
                    break;
                case TD(TD_WM8):
                    send_with_gui(DE_8);
                    break;
                case TD(TD_WM9):
                    send_with_gui(DE_9);
                    break;
                case TD(TD_WM_DOWN):
                    send_with_gui(KC_DOWN);
                    break;
                case TD(TD_WM_UP):
                    send_with_gui(KC_UP);
                    break;
                case TD(TD_WM_LEFT):
                    send_with_gui(KC_LEFT);
                    break;
                case TD(TD_WM_RIGHT):
                    send_with_gui(KC_RIGHT);
                    break;
            }
            break;
        case DOUBLE_TAP:
            switch (TAP_DANCE_KEYCODE(state)) {
                case TD(TD_WM4):
                    send_with_gui(KC_LEFT);
                    break;
                case TD(TD_WM5):
                    send_with_gui(KC_DOWN);
                    break;
                case TD(TD_WM6):
                    send_with_gui(KC_RIGHT);
                    break;
                case TD(TD_WM8):
                    send_with_gui(KC_UP);
                    break;
            }
            break;
        case SINGLE_HOLD:
            switch (TAP_DANCE_KEYCODE(state)) {
                case TD(TD_WM1):
                    send_with_shift_gui(DE_1);
                    break;
                case TD(TD_WM2):
                    send_with_shift_gui(DE_2);
                    break;
                case TD(TD_WM3):
                    send_with_shift_gui(DE_3);
                    break;
                case TD(TD_WM4):
                    send_with_shift_gui(DE_4);
                    break;
                case TD(TD_WM5):
                    send_with_shift_gui(DE_5);
                    break;
                case TD(TD_WM6):
                    send_with_shift_gui(DE_6);
                    break;
                case TD(TD_WM7):
                    send_with_shift_gui(DE_7);
                    break;
                case TD(TD_WM8):
                    send_with_shift_gui(DE_8);
                    break;
                case TD(TD_WM9):
                    send_with_shift_gui(DE_9);
                    break;
                case TD(TD_WM_DOWN):
                    send_with_shift_gui(KC_DOWN);
                    break;
                case TD(TD_WM_UP):
                    send_with_shift_gui(KC_UP);
                    break;
                case TD(TD_WM_LEFT):
                    send_with_shift_gui(KC_LEFT);
                    break;
                case TD(TD_WM_RIGHT):
                    send_with_shift_gui(KC_RIGHT);
                    break;
            }
            break;
        default:
            break;
    }
}

void wm_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [TD_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_F12, G(KC_TAB)),
    [TD_COPY] = ACTION_TAP_DANCE_DOUBLE(C(DE_C), C(DE_X)),
    [TD_CURR] = ACTION_TAP_DANCE_DOUBLE(DE_DLR, DE_EURO),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(C(DE_V), C(S(DE_V))),
    [TD_UNDO] = ACTION_TAP_DANCE_DOUBLE(C(DE_Z), C(S(DE_Z))),
    [TD_SELECT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, select_finished, select_reset),
    [TD_WM1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM8] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM9] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM_UP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_WM_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wm_finished, wm_reset),
    [TD_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cursor_finished, cursor_reset),
    [TD_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cursor_finished, cursor_reset),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_finished, double_reset),
    [TD_DQUO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_finished, double_reset),
    [TD_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_finished, nav_reset),
};

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case DE_MINS:
            case DE_UNDS:
            case KC_LNG2: // minus key with homerow mods
            case KC_BSPC:
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() != 0)) {
                    return true;
                }
                break;
            default:
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
        return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool isOneShotShift = get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    //bool isOneShotCtrl = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    //bool isOneShotAlt = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
    //bool isOneShotGui = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
    //bool isAnyOneShot = isOneShotShift || isOneShotCtrl || isOneShotAlt || isOneShotGui;
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case SHIFT:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    if (caps_word_enabled()) {
                        disable_caps_word();
                    } else {
                        if (!isOneShotShift) {
                            add_oneshot_mods(MOD_BIT(KC_LSFT));
                        } else {
                            del_oneshot_mods(MOD_BIT(KC_LSFT));
                            unregister_mods(MOD_BIT(KC_LSFT));
                            enable_caps_word();
                        }
                    }
                }
                return false;
            }
            break;
        case CAPSWORD:
            if (record->event.pressed) {
                enable_caps_word();
            }
            return false;
        case A_BSLS:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_BSLS);
                }
                return false;
            }
            break;

        case G_SLSH:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_SLSH);
                }
                return false;
            }
            break;
        case S_LCBR:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_LCBR);
                }
                return false;
            }
            break;
        case C_RCBR:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_RCBR);
                }
                return false;
            }
            break;
        case A_COLN:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_COLN);
                }
                return false;
            }
            break;
        case G_MINS:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_MINS);
                }
                return false;
            }
            break;
        case S_RPRN:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_RPRN);
                }
                return false;
            }
            break;
        case C_LPRN:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    tap_code16(DE_LPRN);
                }
                return false;
            }
            break;
    }
    return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHIFT:
        case ESC:
        case HOME_F:
        case A_BSLS:
        case G_SLSH:
        case ENTER:
            return TAPPING_TERM - 35;
        case HOME_I:
        case HOME_E:
        case HOME_S:
        case UNDO:
        case SPACE:
        case S_LCBR:
        case C_RCBR:
        case C_LPRN:
        case S_RPRN:
        case G_MINS:
        case A_COLN:
        case WM_1:
        case WM_2:
        case WM_3:
        case WM_4:
        case WM_5:
        case WM_6:
        case WM_7:
        case WM_8:
        case WM_9:
            return TAPPING_TERM + 25;
        case SELECT:
        case COPY:
        case PASTE:
        case NA_SWIT:
            return TAPPING_TERM + 75;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHIFT:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

//layer_state_t layer_state_set_user(layer_state_t state) {
//  return update_tri_layer_state(state, _NUM, _NEO3, _FKEYS);
//}

enum combo_events {
    COPY_COMBO,
    PASTE_COMBO,
    CLOSE_WINDOW_COMBO,
    AE_COMBO,
    UE_COMBO,
    OE_COMBO,
    COMBO_LENGTH
};

const uint16_t PROGMEM copy_combo[] = {DE_Q, DE_ADIA, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {DE_UDIA, DE_ADIA, COMBO_END};
const uint16_t PROGMEM close_window[] = {DE_Q, DE_X, COMBO_END};
const uint16_t PROGMEM ae_combo[] = {HOME_A, SPACE, COMBO_END};
//const uint16_t PROGMEM ae_combo[] = {DE_COLN, SPACE, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {DE_U, SPACE, COMBO_END};
//const uint16_t PROGMEM ue_combo[] = {DE_QUOT, SPACE, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {DE_O, SPACE, COMBO_END};
//const uint16_t PROGMEM oe_combo[] = {DE_SLSH, SPACE, COMBO_END};

combo_t key_combos[] = {
    [COPY_COMBO] = COMBO(copy_combo, LCTL(KC_C)),
    [PASTE_COMBO] = COMBO(paste_combo, LCTL(KC_V)),
    [CLOSE_WINDOW_COMBO] = COMBO(close_window, LSFT(LGUI(DE_Q))),
    [AE_COMBO] = COMBO(ae_combo, DE_ADIA),
    [UE_COMBO] = COMBO(ue_combo, DE_UDIA),
    [OE_COMBO] = COMBO(oe_combo, DE_ODIA),
};

const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_DOT, DE_EXLM);
const key_override_t comma_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_COMM, DE_QUES);
const key_override_t dquot_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_DQUO, DE_QUOT);
const key_override_t colon_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_COLN, DE_SCLN);
const key_override_t slash_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_SLSH, DE_BSLS);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &dot_key_override,
    &comma_key_override,
    &dquot_key_override,
    &colon_key_override,
    &slash_key_override,
    NULL // Null terminate the array of overrides!
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _NAV, _FKEYS);
}

#include "action.h"
#include "quantum.h"
#include "jensomato.h"

// Create a global instance of the tapdance state type
static td_state_t td_state;

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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

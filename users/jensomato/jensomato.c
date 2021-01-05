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

void leader_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            qk_leader_start();
            break;
        case SINGLE_HOLD:
            layer_on(_MOUSE);
            break;
        default:
            break;
    }
}

void leader_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(_MOUSE);
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
    [TD_LEADER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, leader_finished, leader_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t bsls_timer;
    static uint16_t slsh_timer;
    static uint16_t lcbr_timer;
    static uint16_t rcbr_timer;
    static uint16_t coln_timer;
    static uint16_t mins_timer;
    static uint16_t lprn_timer;
    static uint16_t rprn_timer;

    switch (keycode) {
        case A_BSLS:
            if (record->event.pressed) {
                bsls_timer = timer_read();
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (timer_elapsed(bsls_timer) < TAPPING_TERM) {
                    tap_code16(DE_BSLS);
                }
            }
            return false;
        case G_SLSH:
            if (record->event.pressed) {
                slsh_timer = timer_read();
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
                if (timer_elapsed(slsh_timer) < TAPPING_TERM) {
                    tap_code16(DE_SLSH);
                }
            }
            return false;
        case S_LCBR:
            if (record->event.pressed) {
                lcbr_timer = timer_read();
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
                if (timer_elapsed(lcbr_timer) < TAPPING_TERM) {
                    tap_code16(DE_LCBR);
                }
            }
            return false;
        case C_RCBR:
            if (record->event.pressed) {
                rcbr_timer = timer_read();
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
                if (timer_elapsed(rcbr_timer) < TAPPING_TERM) {
                    tap_code16(DE_RCBR);
                }
            }
            return false;
        case A_COLN:
            if (record->event.pressed) {
                coln_timer = timer_read();
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (timer_elapsed(coln_timer) < TAPPING_TERM) {
                    tap_code16(DE_COLN);
                }
            }
            return false;
        case G_MINS:
            if (record->event.pressed) {
                mins_timer = timer_read();
                register_code(KC_RGUI);
            } else {
                unregister_code(KC_RGUI);
                if (timer_elapsed(mins_timer) < TAPPING_TERM) {
                    tap_code16(DE_MINS);
                }
            }
            return false;
        case S_RPRN:
            if (record->event.pressed) {
                rprn_timer = timer_read();
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
                if (timer_elapsed(rprn_timer) < TAPPING_TERM) {
                    tap_code16(DE_RPRN);
                }
            }
            return false;
        case C_LPRN:
            if (record->event.pressed) {
                lprn_timer = timer_read();
                register_code(KC_RCTL);
            } else {
                unregister_code(KC_RCTL);
                if (timer_elapsed(lprn_timer) < TAPPING_TERM) {
                    tap_code16(DE_LPRN);
                }
            }
            return false;
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
        SEQ_ONE_KEY(DE_DOT) {
            SEND_STRING(". ");
            set_oneshot_mods(MOD_LSFT);
        }
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
            return 200;
        case A_BSLS:
        case G_SLSH:
        case S_LCBR:
        case C_RCBR:
        case C_LPRN:
        case S_RPRN:
        case G_MINS:
        case A_COLN:
            return TAPPING_TERM - 100;
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _SHIFT, _FKEYS);
}

enum combo_events {
    DOT_OSM,
    LEADER_COMBO,
};

const uint16_t PROGMEM dot_osm_combo[] = {DE_DOT, DE_O, COMBO_END};
const uint16_t PROGMEM leader_combo[] = {DE_P, DE_UE, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [DOT_OSM] = COMBO_ACTION(dot_osm_combo),
    [LEADER_COMBO] = COMBO_ACTION(leader_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case DOT_OSM:
      if (pressed) {
        SEND_STRING(". ");
        set_oneshot_mods(MOD_LSFT);
      }
      break;
    case LEADER_COMBO:
      if (pressed) {
        qk_leader_start();
      }
      break;
  }
}

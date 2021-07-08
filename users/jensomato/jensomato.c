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
            layer_on(_FKEYS);
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
            layer_off(_FKEYS);
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

void shift_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            if ((get_oneshot_mods () & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out ()) {
                enable_caps_word();
                //tap_code16(KC_CAPS);
            } else {
                set_oneshot_mods(MOD_LSFT);
            }
            break;
        case SINGLE_HOLD:
            layer_on(_NUM);
            break;
        default:
            break;
    }
}

void shift_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_mods(MOD_LSFT);
            break;
        case SINGLE_HOLD:
            layer_off(_NUM);
            break;
        default:
            layer_off(_NUM);
            break;
    }
}

void dot_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            if ((get_oneshot_mods () & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out ()) {
                clear_oneshot_mods();
                set_oneshot_layer(_NEO3, ONESHOT_START);
            } else {
                register_code(DE_DOT);
            }
            break;
        default:
            break;
    }
}

void dot_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            unregister_code(DE_DOT);
            //clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            break;
        default:
            break;
    }
}

void wm_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            switch (state->keycode) {
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
            switch (state->keycode) {
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

void wm_reset(qk_tap_dance_state_t *state, void *user_data) {
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
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_F12, G(KC_TAB)),
    [TD_COPY] = ACTION_TAP_DANCE_DOUBLE(C(DE_C), C(DE_X)),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(C(DE_V), C(S(DE_V))),
    [TD_UNDO] = ACTION_TAP_DANCE_DOUBLE(C(DE_Z), C(S(DE_Z))),
    [TD_SELECT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, select_finished, select_reset),
    [TD_CTL_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_ctla_finished, nav_ctla_reset),
    [TD_APP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_app_finished, nav_app_reset),
    [TD_PASS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_pass_finished, nav_pass_reset),
    [TD_LEADER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, leader_finished, leader_reset),
    [TD_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished, shift_reset),
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
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dot_finished, dot_reset),
};

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case DE_MINS:
            case DE_UNDS:
            case KC_LANG2: // minus key with homerow mods
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
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case DE_DOT:
            if (record->event.pressed) {
                if ((get_oneshot_mods () & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out ()) {
                    tap_code16(DE_I);
                            qk_leader_start();

                    set_oneshot_layer(_NEO3, ONESHOT_START);
                    return false;
                }
            } else {
                if ((get_oneshot_mods () & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out ()) {
                    clear_oneshot_layer_state(ONESHOT_PRESSED);
                    return false;
                }
                    clear_oneshot_layer_state(ONESHOT_PRESSED);
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

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        SEQ_ONE_KEY(DE_DOT) {
            SEND_STRING(". ");
            set_oneshot_mods(MOD_LSFT);
        }
        SEQ_ONE_KEY(DE_Q) {
            SEND_STRING(SS_LGUI(SS_LSFT("q")));
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
        case SHIFT:
        case ESC:
        case HOME_F:
        case PASS:
        case APP:
        case A_BSLS:
        case G_SLSH:
        case ENTER:
            return TAPPING_TERM - 25;
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

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _NEO3, _FKEYS);
}

enum combo_events {
    DOT_OSM,
    LEADER_COMBO,
    COPY_COMBO,
    PASTE_COMBO,
    CTL_LEFT_COMBO,
    CTL_RIGHT_COMBO,
    CLOSE_WINDOW_COMBO,
};

const uint16_t PROGMEM dot_osm_combo[] = {DE_DOT, DE_O, COMBO_END};
const uint16_t PROGMEM leader_combo[] = {DE_P, DE_UE, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {DE_Q, DE_AE, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {DE_UE, DE_AE, COMBO_END};
const uint16_t PROGMEM ctl_left_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM ctl_right_combo[] = {KC_RIGHT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM close_window[] = {DE_Q, DE_X, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [DOT_OSM] = COMBO_ACTION(dot_osm_combo),
    [LEADER_COMBO] = COMBO_ACTION(leader_combo),
    [COPY_COMBO] = COMBO_ACTION(copy_combo),
    [PASTE_COMBO] = COMBO_ACTION(paste_combo),
    [CTL_LEFT_COMBO] = COMBO_ACTION(ctl_left_combo),
    [CTL_RIGHT_COMBO] = COMBO_ACTION(ctl_right_combo),
    [CLOSE_WINDOW_COMBO] = COMBO_ACTION(close_window),
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
    case COPY_COMBO:
      if (pressed) {
          tap_code16(LCTL(KC_C));
      }
      break;
    case PASTE_COMBO:
      if (pressed) {
          tap_code16(LCTL(KC_V));
      }
      break;
    case CTL_LEFT_COMBO:
      if (pressed) {
          tap_code16(LCTL(KC_LEFT));
      }
      break;
    case CTL_RIGHT_COMBO:
      if (pressed) {
          tap_code16(LCTL(KC_RIGHT));
      }
      break;
    case CLOSE_WINDOW_COMBO:
      if (pressed) {
          tap_code16(LSFT(LGUI(DE_Q)));
      }
      break;
  }
}

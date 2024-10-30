#include QMK_KEYBOARD_H

enum custom_keycodes {
    DBLZERO = 0,
    XCOPY,
    XPASTE,
    XCUT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DBLZERO:
        if (record->event.pressed) {
            tap_code(KC_P0);
            tap_code(KC_P0);
        }
        break;
    case XCOPY:
        if (record->event.pressed) {
            tap_code16(C(KC_C));
        }
        break;
    case XPASTE:
        if (record->event.pressed) {
            tap_code16(C(KC_V));
        }
        break;
    case XCUT:
        if (record->event.pressed) {
            tap_code16(C(KC_X));
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,   KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,  KC_F,   KC_G,   KC_H,  KC_J,   KC_K,    KC_L,    KC_QUOT, KC_MINS,
    KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,   KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_P1, KC_DEL, KC_SPC, KC_P2, KC_ENT, KC_RALT, KC_APP,  KC_RGUI, KC_RCTL)
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

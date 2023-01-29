/* Copyright 2023 Kemal Emre Arpacı -- (github.com/arpacique)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include QMK_KEYBOARD_H
#include "keymap_turkish_q.h"

enum cockpit_layer {
     _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ARROW,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ARROW  MO(_ARROW)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_cockpit(
  KC_TAB,     KC_Q,        KC_W,        KC_E,       KC_R,         KC_T,                    KC_Y,  KC_U,        KC_I,        KC_O,        KC_P,           KC_BSPC,
  KC_ESC,     GUI_T(KC_A), ALT_T(KC_S), SFT_T(KC_D), CTL_T(KC_F), KC_G,                    KC_H,  CTL_T(KC_J), SFT_T(KC_K), ALT_T(KC_L), GUI_T(KC_SCLN), KC_QUOT,
  KC_LSFT,    KC_Z,        KC_X,        KC_C,       KC_V,         KC_B,                    KC_N,  KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,        KC_SFTENT,  
                                                                          KC_MPLY,   KC_MUTE,
                                          KC_LCTL,   LOWER,    LT(ARROW, KC_SPC),  LT(ARROW, KC_SPC),   RAISE,    KC_RGUI,
                                                                                 KC_UP,
                                                                    KC_LEFT,    KC_DOWN,  KC_RGHT

  ),
  
  [_LOWER] = LAYOUT_split_3x6_3(
    KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,           KC_F12,  _______, _______, KC_HOME, KC_END , _______,
                                                     KC_MPLY,   KC_MUTE,
                             _______,   _______, _______,         _______,   _______,  _______,
                                                           KC_UP,
                                              KC_LEFT,    KC_DOWN,  KC_RGHT

  ),
  
  [_RAISE] = LAYOUT_split_3x6_3(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,               KC_F12,  KC_LABK, KC_RABK, KC_PGUP, KC_PGDN, _______,
                                                     KC_MPLY,   KC_MUTE,
                           _______,  _______,   _______,           _______,  _______,  _______,
                                                           KC_UP,
                                              KC_LEFT,    KC_DOWN,  KC_RGHT
  ),
  
  [_ADJUST] = LAYOUT_split_3x6_3(
    XXXXXXX, RESET  , XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   CG_NORM,            CG_SWAP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                     KC_MPLY,   KC_MUTE,            
                                     _______,   _______, XXXXXXX,        XXXXXXX,  _______,  _______,
                                                                  KC_UP,
                                                    KC_LEFT,    KC_DOWN,  KC_RGHT
  ),
  
  [_ARROW] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_UP  , C(KC_HOME), KC_PGUP,          _______, KC_7, KC_8, KC_9,  KC_SLASH,    KC_BSPC,
    _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,    KC_END,           _______, KC_4, KC_5, KC_6,  KC_ASTERISK, KC_EQUAL,
    _______, _______, _______, _______, C(KC_END),  KC_PGDN,          KC_0   , KC_1, KC_2, KC_3,  KC_MINUS,    KC_PLUS,
                                                         KC_MPLY,   KC_MUTE,                         
                               _______, _______,   _______,           _______,  KC_0,  KC_DOT,
                                                            KC_UP,
                                                KC_LEFT,    KC_DOWN,  KC_RGHT
  )
};




layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder: Right encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder: Left encoder */
        if (IS_LAYER_ON(_LOWER)) { 
              if (clockwise) {
                  tap_code(KC_BRIU);
              } else {
                  tap_code(KC_BRID);
              }
        } else {
              if (clockwise) {
                  tap_code(KC_PGUP);
              } else {
                  tap_code(KC_PGDN);
              }
        }
    }
    return false;
}

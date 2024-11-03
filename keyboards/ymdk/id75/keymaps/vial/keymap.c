/* Copyright 2020 IFo Hancroft
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----ESC-----|-----1------|-----2------|-----3------|-----4------|-----5------|-----6------|-----7------|-----8------|-----9------|-----0------|---( -_ )---|---( =+ )---|---( |\ )---|----BSPC----|
       KC_ESC,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_MINS,     KC_EQL,      KC_BSLS,     KC_BSPC,     //1
//  | |----TAB-----|-----Q------|-----W------|-----E------|-----R------|-----T------|---( [{ )---|---( `~ )---|---( ]} )---|-----Y------|-----U------|-----I------|-----O------|-----P------|----DEL-----|
       KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_LBRC,     KC_GRV,      KC_RBRC,     KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_DEL,      //2
//  | |----ALT-----|-----A------|-----S------|-----D------|-----F------|-----G------|----HOME----|---INSERT---|----PGUP----|-----H------|-----J------|-----K------|-----L------|---( ;: )---|---( '" )---|
       KC_LALT,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_HOME,     KC_INS,      KC_PGUP,     KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,     //3
//  | |---LCTRL----|-----Z------|-----X------|-----C------|-----V------|-----B------|----END-----|-----UP-----|---PGDWN----|-----N------|-----M------|---( ,< )---|---( .> )---|---( /? )---|---RCTRL----|
       KC_LCTL,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_END,      KC_UP,       KC_PGDN,     KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,     KC_RCTL,     //4
//  | |----LAYR----|----WIN-----|---MEDIA----|----NPAD----|----SPC-----|----SPC-----|----ENTER---|---SHIFT----|---RIGHT----|---ENTER----|----SHIFT---|---SHIFT----|---NUMPAD---|---MOUSE----|----LAYR----|
       OSL(LAYR),   KC_LGUI,     OSL(MEDI),   OSL(NPAD),   KC_SPC,      LSFT_T(KC_SPC), KC_LEFT,  KC_DOWN,     KC_RGHT,     KC_ENT,      OSM(MOD_RSFT), KC_RSFT,   OSL(NPAD),   OSL(MOUS),   OSL(LAYR)    //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [NPAD] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----PAUS----|-----F1-----|-----F2-----|-----F3-----|-----F4-----|-----F5-----|-----F6-----|-----F7-----|-----F8-----|-----F9-----|----F10-----|----F11-----|----F12-----|-----▽------|---PRTSCR---|
       KC_PAUS,     KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_TRNS,     KC_PSCR,     //1
//  | |---SCRLCK---|-----▽------|-----UP-----|-----▽------|-----▽------|-----▽------|----HOME----|----INS-----|----PGUP----|----NUM7----|----NUM8----|----NUM9----|---(NUM/)---|-----▽------|-----▽------|
       KC_SCRL,     KC_TRNS,     KC_UP,       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_HOME,     KC_INS,      KC_PGUP,     KC_P7,       KC_P8,       KC_P9,       KC_PSLS,     KC_TRNS,     KC_TRNS,     //2
//  | |-----▽------|----LEFT----|----DOWN----|----RGHT----|-----▽------|-----▽------|----END-----|----DEL-----|----PGDN----|----NUM4----|----NUM5----|----NUM6----|---(NUM*)---|-----▽------|-----▽------|
       KC_TRNS,     KC_LEFT,     KC_DOWN,     KC_RGHT,     KC_TRNS,     KC_TRNS,     KC_END,      KC_DEL,      KC_PGDN,     KC_P4,       KC_P5,       KC_P6,       KC_PAST,     KC_TRNS,     KC_TRNS,     //3
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|----NUM1----|----NUM2----|----NUM3----|---(NUM-)---|-----▽------|-----NO-----|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_P1,       KC_P2,       KC_P3,       KC_PMNS,     KC_TRNS,     KC_NO,       //4
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|--CAPSLCK---|-----▽------|---NUMLCK---|----NUM0----|---( . )----|---NENTER---|---(NUM+)---|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_CAPS,     KC_TRNS,     KC_NUM,      KC_P0,       KC_PDOT,     KC_PENT,     KC_PPLS,     KC_NO,       KC_TRNS      //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [MOUS] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     //1
//  | |---BKSPC----|--MOUSBCK---|---MOUSUP---|--MOUSFRD---|-----▽------|-----▽------|---VOLUP----|-----▽------|--MSWHLUP---|---MOUSBCK--|---MOUSUP---|--MOUSFRD---|---BKSPC----|-----▽------|-----▽------|
       KC_BSPC,     KC_BTN4,     KC_MS_U,     KC_BTN5,     KC_TRNS,     KC_TRNS,     KC_VOLU,     KC_TRNS,     KC_WH_U,     KC_BTN4,     KC_MS_U,     KC_BTN5,     KC_BSPC,     KC_TRNS,     KC_TRNS,     //2
//  | |---ENTER----|--MOUSLFT---|--MOUSDWN---|--MOUSRGT---|-----▽------|-----▽------|---VOLDWN---|-----▽------|--MSWHLDWN--|--MOUSLFT---|--MDLMBTN---|--MOUSRGT---|---ENTER----|-----▽------|-----▽------|
       KC_ENT,      KC_MS_L,     KC_MS_D,     KC_MS_R,     KC_TRNS,     KC_TRNS,     KC_VOLD,     KC_TRNS,     KC_WH_D,     KC_MS_L,     KC_BTN3,     KC_MS_R,     KC_ENT,      KC_TRNS,     KC_TRNS,     //3
//  | |----DEL-----|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|----MUTE----|--MSWHLUP---|--MDLMBTN---|-----▽------|--MOUSDWN---|-----▽------|----DEL-----|-----▽------|-----NO-----|
       KC_DEL,      KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_MUTE,     KC_WH_U,     KC_BTN3,     KC_TRNS,     KC_MS_D,     KC_TRNS,     KC_DEL,      KC_TRNS,     KC_NO,       //4
//  | |-----▽------|-----▽------|-----▽------|-----▽------|--LFTMBTN---|--RGTMBTN---|--MSWHLLFT--|--MSWHLDWN--|--MSWHLRGT--|--LFTMBTN---|--RGTMBTN---|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_BTN1,     KC_BTN2,     KC_WH_L,     KC_WH_D,     KC_WH_R,     KC_BTN1,     KC_BTN2,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS      //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [CTRL] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|----CTL1----|----CTL2----|----CTL3----|----CTL4----|----CTL5----|----CTL6----|----CTL7----|----CTL8----|----CTL9----|----CTL0----|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     LCTL(KC_1),  LCTL(KC_2),  LCTL(KC_3),  LCTL(KC_4),  LCTL(KC_5),  LCTL(KC_6),  LCTL(KC_7),  LCTL(KC_8),  LCTL(KC_9),  LCTL(KC_0),  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     //1
//  | |--CTL_TAB---|----CTLQ----|----CTLW----|----CTLE----|----CTLR----|----CTLT----|-----▽------|-----▽------|-----▽------|----CTLY----|----CTLU----|----CTLI----|----CTLO----|----CTLP----|-----▽------|
       LCTL(KC_TAB),LCTL(KC_Q),  LCTL(KC_W),  LCTL(KC_E),  LCTL(KC_R),  LCTL(KC_T),  KC_TRNS,     KC_TRNS,     KC_TRNS,     LCTL(KC_Y),  LCTL(KC_U),  LCTL(KC_I),  LCTL(KC_O),  LCTL(KC_P),  KC_TRNS,     //2
//  | |-----▽------|----CTLA----|----CTLS----|----CTLD----|----CTLF----|----CTLG----|---CTL_HM---|-----▽------|---CTL_PU---|----CTLH----|----CTLJ----|----CTLK----|----CTLL----|-----▽------|-----▽------|
       KC_TRNS,     LCTL(KC_A),  LCTL(KC_S),  LCTL(KC_D),  LCTL(KC_F),  LCTL(KC_G),  LCTL(KC_HOME), KC_TRNS,   LCTL(KC_PGUP), LCTL(KC_H), LCTL(KC_J), LCTL(KC_K),  LCTL(KC_L),  KC_TRNS,     KC_TRNS,     //3
//  | |-----▽------|----CTLZ----|----CTLX----|----CTLC----|----CTLV----|----CTLB----|--CTL_END---|-----▽------|---CTL_PD---|----CTLN----|----CTLM----|-----▽------|-----▽------|-----▽------|-----NO-----|
       KC_TRNS,     LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_V),  LCTL(KC_B),  LCTL(KC_END), KC_TRNS,    LCTL(KC_PGDN), LCTL(KC_N), LCTL(KC_M), KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       //4
//  | |-----▽------|-----▽------|-----▽------|-----▽------|---ENTER----|---ENTER----|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_ENT,      KC_ENT,      KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS      //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [MEDI] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_MRWD,     KC_MFFD,     KC_MPRV,     KC_MNXT,     KC_MSTP,     KC_MPLY,     //1
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_EJCT,     KC_SLCT,     KC_MAIL,     KC_CALC,     KC_MYCM,     KC_WSCH,     //2
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_WHOM,     KC_WBAK,     KC_WFWD,     KC_WSTP,     KC_WREF,     KC_WFAV,     //3
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       //4
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS      //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [SYSC] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     QK_AREP,     QK_REP,      EE_CLR,      DB_TOGG,     QK_BOOT,     //1
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     NK_TOGG,     //2
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     RGB_VAI,     RGB_HUI,     RGB_SAI,     RGB_SPI,     RGB_MOD,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     //3
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       RGB_TOG,     RGB_VAD,     RGB_HUD,     RGB_SAD,     RGB_SPD,     RGB_RMOD,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       //4
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS      //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [LAYR] = LAYOUT_ortho_5x15(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12____________13___________14__________15______
    | \            \            \            \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----BASE----|----NPAD----|----MOUS----|----CTRL----|----MEDI----|----SYSC----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|
       TO(BASE),    TO(NPAD),    TO(MOUS),    TO(CTRL),    TO(MEDI),    TO(SYSC),    KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       //1
//  | |-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|
       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       //2
//  | |-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|
       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       //3
//  | |-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|
       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       //4
//  | |-----▽------|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----▽------|
       KC_TRNS,     KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_TRNS      //5
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    )
};

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----TAB-----|-----Q------|-----W------|-----E------|-----R------|-----T------|-----Y------|-----U------|-----I------|-----O------|-----P------|----BSPC----|
       KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_BSPC,
//  | |----ALT-----|-----A------|-----S------|-----D------|-----F------|-----G------|-----H------|-----J------|-----K------|-----L------|---( ;: )---|---( '" )---|
       KC_LALT,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,
//  | |---LCTRL----|-----Z------|-----X------|-----C------|-----V------|-----B------|-----N------|-----M------|---( ,< )---|---( .> )---|---( /? )---|---RCTRL----|
       KC_LCTL,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,     KC_RCTL,
//  | |----LAYR----|----WIN-----|---NUMPAD---|----FUNC----|----SPC-----|----SPC-----|----ENTER---|----SHIFT---|---NUMBER---|---NUMPAD---|---MOUSE----|----LAYR----|
       OSL(LAYR),   KC_LGUI,     OSL(NPAD),   OSL(FUNC),   KC_SPC,      LSFT_T(KC_SPC), KC_ENT,   OSM(MOD_RSFT), OSL(NUMB), OSL(NPAD),   OSL(MOUS),   OSL(LAYR)
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [NUMB] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----ESC-----|-----1------|-----2------|-----3------|-----4------|----5-------|-----6------|-----7------|-----8------|-----9------|-----0------|---BSPC-----|
       KC_ESC,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_BSPC,
//  | |---( `~ )---|-----▽------|-----▽------|-----▽------|-----▽------|---( [{ )---|---( ]} )---|-----▽------|---( -_ )---|---( =+ )---|---( |\ )---|----DEL-----|
       KC_GRV ,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_LBRC,     KC_RBRC,     KC_TRNS,     KC_MINS,     KC_EQL,      KC_BSLS,     KC_DEL,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [FUNC] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----F1-----|-----F2-----|-----F3-----|-----F4-----|-----F5-----|-----F6-----|-----F7-----|-----F8-----|-----F9-----|----F10-----|----F11-----|----F12-----|
       KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [NPAD] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----PAUS----|-----▽------|-----UP-----|-----▽------|----INS-----|----HOME----|----PGUP----|----NUM7----|----NUM8----|----NUM9----|---(NUM/)---|---PRTSCR---|
       KC_PAUS,     KC_TRNS,     KC_UP,       KC_TRNS,     KC_INS,      KC_HOME,     KC_PGUP,     KC_P7,       KC_P8,       KC_P9,       KC_PSLS,     KC_PSCR,
//  | |---SCRLCK---|----LEFT----|----DOWN----|----RGHT----|----DEL-----|----END-----|----PGDN----|----NUM4----|----NUM5----|----NUM6----|---(NUM*)---|-----▽------|
       KC_SCRL,     KC_LEFT,     KC_DOWN,     KC_RGHT,     KC_DEL,      KC_END,      KC_PGDN,     KC_P4,       KC_P5,       KC_P6,       KC_PAST,     KC_TRNS,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|----NUM1----|----NUM2----|----NUM3----|---(NUM-)---|-----NO-----|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_P1,       KC_P2,       KC_P3,       KC_PMNS,     KC_NO,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|--CAPSLCK---|---NUMLCK---|----NUM0----|---( . )----|---NENTER---|---(NUM+)---|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_CAPS,     KC_NUM,      KC_P0,       KC_PDOT,     KC_PENT,     KC_PPLS,     KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [MOUS] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |---BKSPC----|--MOUSBCK---|---MOUSUP---|--MOUSFRD---|-----▽------|---VOLUP----|--MSWHLUP---|---MOUSBCK--|---MOUSUP---|--MOUSFRD---|---BKSPC----|-----▽------|
       KC_BSPC,     KC_BTN4,     KC_MS_U,     KC_BTN5,     KC_TRNS,     KC_VOLU,     KC_WH_U,     KC_BTN4,     KC_MS_U,     KC_BTN5,     KC_BSPC,     KC_TRNS,
//  | |---ENTER----|--MOUSLFT---|--MOUSDWN---|--MOUSRGT---|-----▽------|---VOLDWN---|--MSWHLDWN--|--MOUSLFT---|--MDLMBTN---|--MOUSRGT---|---ENTER----|-----▽------|
       KC_ENT,      KC_MS_L,     KC_MS_D,     KC_MS_R,     KC_TRNS,     KC_VOLD,     KC_WH_D,     KC_MS_L,     KC_BTN3,     KC_MS_R,     KC_ENT,      KC_TRNS,
//  | |----DEL-----|-----▽------|-----▽------|-----▽------|-----▽------|----MUTE----|--MDLMBTN---|-----▽------|--MOUSDWN---|-----▽------|----DEL-----|-----NO-----|
       KC_DEL,      KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_MUTE,     KC_BTN3,     KC_TRNS,     KC_MS_D,     KC_TRNS,     KC_DEL,      KC_NO,
//  | |-----▽------|-----▽------|-----▽------|--LFTMBTN---|--RGTMBTN---|--MSWHLLFT--|--MSWHLRGT--|--LFTMBTN---|--RGTMBTN---|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_BTN1,     KC_BTN2,     KC_WH_L,     KC_WH_R,     KC_BTN1,     KC_BTN2,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [CTRL] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       LCTL(KC_TAB),LCTL(KC_Q),  LCTL(KC_W),  LCTL(KC_E),  LCTL(KC_R),  LCTL(KC_T),  LCTL(KC_Y),  LCTL(KC_U),  LCTL(KC_I),  LCTL(KC_O),  LCTL(KC_P),  LCTL(KC_PGUP),
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       LCTL(KC_HOME),LCTL(KC_A), LCTL(KC_S),  LCTL(KC_D),  LCTL(KC_F),  LCTL(KC_G),  LCTL(KC_H),  LCTL(KC_J),  LCTL(KC_K),  LCTL(KC_L),  KC_TRNS,     LCTL(KC_PGDN),
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       LCTL(KC_END),LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_V),  LCTL(KC_B),  LCTL(KC_N),  LCTL(KC_M),  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|---ENTER----|---ENTER----|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_ENT,      KC_ENT,      KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [NCTL] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     LCTL(KC_1),  LCTL(KC_2),  LCTL(KC_3),  LCTL(KC_4),  LCTL(KC_5),  LCTL(KC_6),  LCTL(KC_7),  LCTL(KC_8),  LCTL(KC_9),  LCTL(KC_0),  KC_TRNS,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|---ENTER----|---ENTER----|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_ENT,      KC_ENT,      KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [MEDI] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_MRWD,     KC_MFFD,     KC_MPRV,     KC_MNXT,     KC_MSTP,     KC_MPLY,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_EJCT,     KC_SLCT,     KC_MAIL,     KC_CALC,     KC_MYCM,     KC_WSCH,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_WHOM,     KC_WBAK,     KC_WFWD,     KC_WSTP,     KC_WREF,     KC_WFAV,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [MCRO] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|----MM0-----|----MM1-----|----MM2-----|----MM3-----|----MM4-----|----MM0-----|----MM1-----|----MM2-----|----MM3-----|----MM4-----|-----▽------|
       KC_TRNS,     M_M0,        M_M1,        M_M2,        M_M3,        M_M4,        M_M5,        M_M6,        M_M7,        M_M8,        M_M9,        KC_TRNS,    
//  | |-----▽------|----MM5-----|----MM6-----|----MM7-----|----MM8-----|----MM9-----|----MM5-----|----MM6-----|----MM7-----|----MM8-----|----MM9-----|-----▽------|
       KC_TRNS,     M_M10,       M_M11,       M_M12,       M_M13,       M_M14,       M_M15,       M_M16,       M_M17,       M_M18,       M_M19,       KC_TRNS,    
//  | |-----▽------|----MM10----|----MM11----|----MM12----|----MM13----|----MM14----|----MM10----|----MM11----|----MM12----|----MM13----|----MM14----|-----▽------|
       KC_TRNS,     M_M20,       M_M21,       M_M22,       M_M23,       M_M24,       M_M25,       M_M26,       M_M27,       M_M28,       M_M29,       KC_TRNS,    
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [SYSC] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     QK_AREP,     QK_REP,      EE_CLR,      DB_TOGG,     QK_BOOT,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|
       KC_TRNS,     RGB_VAI,     RGB_HUI,     RGB_SAI,     RGB_SPI,     RGB_MOD,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     NK_TOGG,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|
       RGB_TOG,     RGB_VAD,     RGB_HUD,     RGB_SAD,     RGB_SPD,     RGB_RMOD,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,
//  | |-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----▽------|-----NO-----|-----▽------|
       KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    ),
  [LAYR] = LAYOUT(
/*   _______1____________2____________3____________4____________5____________6____________7____________8____________9___________10___________11___________12______
    | \            \            \            \            \            \            \            \            \            \            \            \            \ */
//  | |----BASE----|----NUMB----|----FUNC----|----NPAD----|----MOUS----|----CTRL----|----NCTL----|----MEDI----|----MCRO----|----SYSC----|-----NO-----|-----NO-----|
       TO(BASE),    TO(NUMB),    TO(FUNC),    TO(NPAD),    TO(MOUS),    TO(CTRL),    TO(NCTL),    TO(MEDI),    TO(MCRO),    TO(SYSC),    KC_NO,       KC_NO,
//  | |-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|
       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
//  | |-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|
       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,
//  | |-----▽------|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----NO-----|-----▽------|
       KC_TRNS,     KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_TRNS
//   \|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|____________|
    )
};

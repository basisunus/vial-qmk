#include "p48.h"
#include <lib/lib8tion/lib8tion.h>

#ifdef RGB_MATRIX_ENABLE

/* RGB Positioning */
led_config_t g_led_config =
{
    {
        // Key Matrix to LED Index
        {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11},
        {  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
        {  24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
        {  36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47}
    },
    {
        // LED Index to Physical Position
        {0, 0}, {21, 0}, {41, 0}, {62, 0}, {82, 0}, {102, 0}, {123, 0}, {143, 0}, {163, 0}, {184, 0}, {204, 0}, {224, 0},
        {0,22}, {21,22}, {41,22}, {62,22}, {82,22}, {102,22}, {123,22}, {143,22}, {163,22}, {184,22}, {204,22}, {224,22},
        {0,42}, {21,42}, {41,42}, {62,42}, {82,42}, {102,42}, {123,42}, {143,42}, {163,42}, {184,42}, {204,42}, {224,42},
        {0,64}, {21,64}, {41,64}, {62,64}, {82,64}, {102,64}, {123,64}, {143,64}, {163,64}, {184,64}, {204,64}, {224,64}
    },
    {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

uint16_t my_speed = 0;
bool sft_down = false;
bool caps_lck = false;
bool nums_lck = false;

const uint8_t PROGMEM alphabet[] = {
	16, 17, 18, 19, 20, 21, 22, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46
};
const uint8_t PROGMEM numeral[]  = {
	4, 5, 15, 16, 17, 27, 28, 29, 39, 40, 41
};

const uint8_t PROGMEM spc_sft[] = {
	6
};

#define C_CMD	HSV_CORAL
#define C_NUM	HSV_PINK
#define C_ABC	HSV_YELLOW
#define C_VIU	HSV_MAGENTA
#define C_SYM	HSV_ORANGE
#define C_ACS	HSV_CYAN
#define C_ENT	HSV_GREEN
#define C_FUN	HSV_SPRINGGREEN
#define C_LCK	HSV_PURPLE
#define C_UPP	HSV_AZURE
#define C_DWN	HSV_GOLD
#define C_LFT	HSV_BLUE
#define C_RGT	HSV_RED
#define C_BLN	HSV_WHITE
#define C_BLK	HSV_BLACK
#define C_RB1	0x00, 0xFF, 0xFF
#define C_RB2	0x24, 0xFF, 0xFF
#define C_RB3	0x48, 0xFF, 0xFF
#define C_RB4	0x6C, 0xFF, 0xFF
#define C_RB5	0x90, 0xFF, 0xFF
#define C_RB6	0xB4, 0xFF, 0xFF
#define C_RB7	0xD8, 0xFF, 0xFF

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    caps_lck = host_keyboard_led_state().caps_lock;
    nums_lck = host_keyboard_led_state().num_lock;

    return true;
}

const uint8_t PROGMEM layercolors[10][48*3] =
{
	{ C_ACS, C_SYM, C_SYM, C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ACS,
	  C_SYM, C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ACS,
	  C_CMD, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM,
	  C_SYM, C_SYM, C_SYM, C_SYM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_CMD },
	{ C_BLK, C_BLK, C_SYM, C_VIU, C_DWN, C_VIU, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_SYM, C_RGT, C_BLK, C_LFT, C_BLK, C_BLK, C_RGT, C_DWN, C_LFT, C_BLK,
	  C_BLK, C_BLK, C_SYM, C_VIU, C_UPP, C_VIU, C_BLK, C_BLK, C_BLK, C_UPP, C_BLK, C_BLK,
	  C_CMD, C_LCK, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_CMD },
	{ C_BLK, C_RB3, C_CMD, C_BLK, C_DWN, C_BLK, C_RB3, C_BLK, C_BLK, C_BLK, C_BLK, C_CMD,
	  C_BLK, C_RB2, C_ENT, C_RGT, C_CMD, C_LFT, C_RB2, C_BLK, C_RGT, C_DWN, C_LFT, C_ENT,
	  C_BLK, C_RB1, C_SYM, C_RGT, C_UPP, C_LFT, C_RB1, C_BLK, C_RGT, C_UPP, C_LFT, C_SYM,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_RB1, C_RB5, C_RB7, C_RB4, C_RB2, C_RB6, C_RB3, C_BLK,
	  C_BLK, C_BLK, C_RB5, C_RB2, C_RB7, C_RB3, C_RB2, C_RB1, C_RB5, C_RB4, C_RB7, C_BLK,
	  C_BLK, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_RB5, C_RB3, C_RB7, C_RB2, C_RB1, C_RB6,
	  C_BLK, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_ENT, C_LCK, C_RGT, C_LFT, C_RGT, C_LFT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_ENT, C_LCK, C_RGT, C_LFT, C_RGT, C_LFT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_ENT, C_LCK, C_RGT, C_LFT, C_RGT, C_LFT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_ENT, C_LCK, C_RGT, C_LFT, C_RGT, C_LFT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB4, C_RB4, C_RB4, C_RB4, C_RB4, C_LCK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB5, C_RB5, C_RB5, C_RB5, C_RB5, C_BLK,
	  C_RB4, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_CMD, C_CMD, C_RB4, C_LCK,
	  C_RB1, C_CMD, C_RB1, C_CMD, C_CMD, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB5, C_BLK },
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB7, C_RB6, C_RB5, C_RB4, C_RB3, C_RB2 }
};

const uint8_t PROGMEM layercolor_sft[48*3] = 
	{ C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_ACS,
	  C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_ACS,
	  C_CMD, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM,
	  C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_CMD };

const uint8_t PROGMEM layercolor_caps_lck[48*3] = 
	{ C_ACS, C_SYM, C_SYM, C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_ACS,
	  C_SYM, C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_ACS,
	  C_CMD, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM,
	  C_SYM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_CMD };

const uint8_t PROGMEM layercolor_nums_lck[48*3] = 
    { C_BLK, C_BLK, C_SYM, C_LCK, C_LCK, C_LCK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_SYM, C_LCK, C_LCK, C_LCK, C_BLK, C_BLK, C_RGT, C_DWN, C_LFT, C_BLK,
	  C_BLK, C_BLK, C_SYM, C_LCK, C_LCK, C_LCK, C_BLK, C_BLK, C_BLK, C_UPP, C_BLK, C_BLK,
	  C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN };

void set_layer_color( uint8_t layer ) {
  uint8_t val = rgb_matrix_config.hsv.v;
  uint8_t hue = (uint16_t)(rgb_matrix_config.hsv.h);
  uint8_t sat = rgb_matrix_config.hsv.s;
  uint8_t time = scale16by8(g_rgb_timer, my_speed);
  float offset = time < 128 ? time : 255 - time;;
  offset *= 0.25f;
  time = (uint8_t)(offset);
  //val = val > time ? val - time : 0;
  
  bool locks = ((layer == 0) && (sft_down || caps_lck)) || (layer == 1 && nums_lck);
  for (int i = 0; i < 48; i++) {
  	HSV color_hsv;
  	if (layer == 0)
  	{
  		if (sft_down)
	  	{
	  		color_hsv.h = layercolor_sft[i*3];
	  		color_hsv.s = layercolor_sft[i*3+1];
	  		color_hsv.v = layercolor_sft[i*3+2];
	  	}
	  	else if (caps_lck)
	  	{
	  		color_hsv.h = layercolor_caps_lck[i*3];
	  		color_hsv.s = layercolor_caps_lck[i*3+1];
	  		color_hsv.v = layercolor_caps_lck[i*3+2];
	  	}
	}
	else if (layer == 1)
	{
		if (nums_lck)
	  	{
	  		color_hsv.h = layercolor_nums_lck[i*3];
	  		color_hsv.s = layercolor_nums_lck[i*3+1];
	  		color_hsv.v = layercolor_nums_lck[i*3+2];
	  	}
	}
  	if (!locks)
  	{
  		color_hsv.h = layercolors[layer][i*3];
  		color_hsv.s = layercolors[layer][i*3+1];
  		color_hsv.v = layercolors[layer][i*3+2];
  	}
  	
  	uint16_t hue2 = hue + color_hsv.h;
  	hue2 = hue2 > 255 ? hue2 - 256 : hue2;
  	color_hsv.h = (uint8_t)(hue2);
  	color_hsv.s = sat;
  	uint8_t time2 = hue2 < 64 || hue2 > 190 ? time / 2 : time;
  	uint8_t val2 = val > time2 ? val - time2 : 0;
  	color_hsv.v = color_hsv.v == 0 ? 0 : val2;
  	RGB color = hsv_to_rgb(color_hsv);
    rgb_matrix_set_color( i, color.r, color.g, color.b );
  }
}

bool rgb_matrix_indicators_user(void) {
  my_speed = rgb_matrix_config.speed;
  if (my_speed > 0) my_speed += my_speed * g_last_hit_tracker.count;
  if (my_speed > 255) my_speed = 255;
  uint32_t mode = rgblight_get_mode();
  // assign colors if the matrix is on and the current mode
  // is SOLID COLORS => No animations running
  if(rgb_matrix_config.enable == 1 && mode == 1) {
    uint8_t layer = biton32(layer_state);
    set_layer_color(layer);
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  	case KC_RSFT:
  	case LSFT_T(KC_SPC):
  	case OSM(MOD_RSFT):
  	case MOD_RSFT:
  		if (record->event.pressed)
  			sft_down = true;
  		else
  			sft_down = false;
  		break;
  }
  return true;
}
#endif

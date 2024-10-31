/* Copyright 2021 MT
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

#include "quantum.h"
#include "id75.h"
#include <lib/lib8tion/lib8tion.h>

//#ifdef RGB_MATRIX_ENABLE
uint16_t my_speed = 0;
bool sft_down = false;
bool caps_lck = false;
bool nums_lck = false;

#define C_LYR	0xF7, 0x50, 0x50
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

//led index mapping
const uint8_t PROGMEM li[75*3] =
{
    74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60,
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45,
    44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30,
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,
    14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
};

const uint8_t PROGMEM layercolors[7][75*3] =
{
    //BASE
	{ C_CMD, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_SYM, C_SYM, C_SYM, C_SYM,
	  C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM, C_SYM, C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_CMD,
	  C_ACS, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_VIU, C_CMD, C_VIU, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM, C_SYM,
	  C_ACS, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_VIU, C_UPP, C_VIU, C_ABC, C_ABC, C_SYM, C_SYM, C_SYM, C_ACS,
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_LFT, C_DWN, C_RGT, C_ENT, C_ACS, C_ACS, C_LYR, C_LYR, C_LYR },
    //NUMPAD
	{ C_CMD, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_BLK, C_CMD,
	  C_LCK, C_BLK, C_UPP, C_BLK, C_BLK, C_BLK, C_VIU, C_CMD, C_VIU, C_VIU, C_UPP, C_VIU, C_SYM, C_CMD, C_BLK,
	  C_BLK, C_LFT, C_DWN, C_RGT, C_BLK, C_BLK, C_VIU, C_CMD, C_VIU, C_LFT, C_BLK, C_RGT, C_SYM, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_VIU, C_DWN, C_VIU, C_SYM, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_BLK, C_LCK, C_CMD, C_CMD, C_ENT, C_SYM, C_BLK, C_BLK },
    //MOUSE
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_RB1, C_RB5, C_RB2, C_BLK, C_RB1, C_RB7, C_RB4, C_RB2, C_RB6, C_RB3, C_BLK,
	  C_BLK, C_BLK, C_RB5, C_RB2, C_RB7, C_RB3, C_RB6, C_BLK, C_RB4, C_RB2, C_RB1, C_RB5, C_RB4, C_RB7, C_BLK,
	  C_BLK, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_BLK, C_BLK, C_BLK, C_RB5, C_RB3, C_RB7, C_RB2, C_RB1, C_RB6,
	  C_BLK, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_BLK, C_BLK, C_BLK, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_BLK },
    //CONTROL
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_RB1, C_RB5, C_RB2, C_BLK, C_RB1, C_RB7, C_RB4, C_RB2, C_RB6, C_RB3, C_BLK,
	  C_BLK, C_BLK, C_RB5, C_RB2, C_RB7, C_RB3, C_RB6, C_BLK, C_RB4, C_RB2, C_RB1, C_RB5, C_RB4, C_RB7, C_BLK,
	  C_BLK, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_BLK, C_BLK, C_BLK, C_RB5, C_RB3, C_RB7, C_RB2, C_RB1, C_RB6,
	  C_BLK, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_BLK, C_BLK, C_BLK, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_BLK },
    //MEDIA
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_RB1, C_RB5, C_RB2, C_BLK, C_RB1, C_RB7, C_RB4, C_RB2, C_RB6, C_RB3, C_BLK,
	  C_BLK, C_BLK, C_RB5, C_RB2, C_RB7, C_RB3, C_RB6, C_BLK, C_RB4, C_RB2, C_RB1, C_RB5, C_RB4, C_RB7, C_BLK,
	  C_BLK, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_BLK, C_BLK, C_BLK, C_RB5, C_RB3, C_RB7, C_RB2, C_RB1, C_RB6,
	  C_BLK, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_BLK, C_BLK, C_BLK, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_BLK },
    //SYSTEM
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_RB1, C_RB5, C_RB2, C_BLK, C_RB1, C_RB7, C_RB4, C_RB2, C_RB6, C_RB3, C_BLK,
	  C_BLK, C_BLK, C_RB5, C_RB2, C_RB7, C_RB3, C_RB6, C_BLK, C_RB4, C_RB2, C_RB1, C_RB5, C_RB4, C_RB7, C_BLK,
	  C_BLK, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_BLK, C_BLK, C_BLK, C_RB5, C_RB3, C_RB7, C_RB2, C_RB1, C_RB6,
	  C_BLK, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_BLK, C_BLK, C_BLK, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_BLK },
    //LAYERS
	{ C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK }
};

const uint8_t PROGMEM lc_base_shft[75*3] = 
	{ C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK };

const uint8_t PROGMEM lc_base_caps[75*3] = 
	{ C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK };

const uint8_t PROGMEM lc_npad_lock[75*3] = 
	{ C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK };

void set_layer_color( uint8_t layer ) {
  uint8_t val = rgb_matrix_config.hsv.v;
  uint8_t hue = (uint16_t)(rgb_matrix_config.hsv.h);
  uint8_t sat = rgb_matrix_config.hsv.s;
  uint8_t time = scale16by8(g_rgb_timer, my_speed);
  float offset = time < 128 ? time : 255 - time;;
  offset *= 0.25f;
  time = (uint8_t)(offset);
  //val = val > time ? val - time : 0;
  
  bool shifted =
      ((layer == BASE) && (sft_down || caps_lck)) ||
      (layer == NPAD && nums_lck);

  for (int i = 0; i < 75; i++)
  {
  	HSV color_hsv = { C_BLK };

    if (shifted)
    {
        if (layer == BASE)
        {
            if (sft_down)
            {
                color_hsv.h = lc_base_shft[li[i] * 3];
                color_hsv.s = lc_base_shft[li[i] * 3 + 1];
                color_hsv.v = lc_base_shft[li[i] * 3 + 2];
            }
            else if (caps_lck)
            {
                color_hsv.h = lc_base_caps[li[i] * 3];
                color_hsv.s = lc_base_caps[li[i] * 3 + 1];
                color_hsv.v = lc_base_caps[li[i] * 3 + 2];
            }
        }
        else if (layer == NPAD)
        {
            if (nums_lck)
            {
                color_hsv.h = lc_npad_lock[li[i] * 3];
                color_hsv.s = lc_npad_lock[li[i] * 3 + 1];
                color_hsv.v = lc_npad_lock[li[i] * 3 + 2];
            }
        }
    }
    else
  	{
  		color_hsv.h = layercolors[layer][li[i]*3];
  		color_hsv.s = layercolors[layer][li[i]*3+1];
  		color_hsv.v = layercolors[layer][li[i]*3+2];
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
//#endif

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

#include "raw_hid.h"
#include "quantum.h"
#include "id75.h"
#include "types.h"
#include <lib/lib8tion/lib8tion.h>

//#ifdef RGB_MATRIX_ENABLE
uint8_t  disp_mode = DM_LAYER;
uint16_t my_speed = 0;
bool sft_down = false;
bool caps_lck = false;
bool nums_lck = false;
bool scrl_lck = false;
bool nk_rover = false;
uint16_t idx_caps = 8;
uint16_t idx_nums = 6;
uint16_t idx_scrl = 59;
uint16_t idx_nkro = 45;

#define C_LYR	0xF0, 0xFF, 0xFF
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
    scrl_lck = host_keyboard_led_state().scroll_lock;

    return true;
}

//key state press
bool PROGMEM ksp[GRID_COUNT] =
{
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};

//led index mapping
const uint8_t PROGMEM li[GRID_COUNT] =
{
//--1---2---3---4---5---6---7---8---9---10--11--12--13--14--15
    74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60,
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45,
    44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30,
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,
    14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
};

const uint8_t PROGMEM time_x_pos[4] = {0, 4, 8, 12};

char time_buffer[5] = {'0', '1', '2', '3'};

uint8_t PROGMEM time_disp[GRID_COUNT] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const uint8_t PROGMEM layercolors[LAYER_NUM][GRID_COUNT*3] =
{
    //BASE
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_CMD, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_SYM, C_SYM, C_SYM, C_SYM,  //1
	  C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM, C_SYM, C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_CMD,  //2
	  C_ACS, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_VIU, C_CMD, C_VIU, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM, C_SYM,  //3
	  C_ACS, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_VIU, C_UPP, C_VIU, C_ABC, C_ABC, C_SYM, C_SYM, C_SYM, C_ACS,  //4
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_LFT, C_DWN, C_RGT, C_ENT, C_ACS, C_ACS, C_LYR, C_LYR, C_LYR },//5
    //NUMPAD
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_CMD, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_BLK, C_CMD,  //1
	  C_LCK, C_BLK, C_UPP, C_BLK, C_BLK, C_BLK, C_VIU, C_CMD, C_VIU, C_VIU, C_UPP, C_VIU, C_SYM, C_BLK, C_BLK,  //2
	  C_BLK, C_LFT, C_DWN, C_RGT, C_BLK, C_BLK, C_VIU, C_CMD, C_VIU, C_LFT, C_BLK, C_RGT, C_SYM, C_BLK, C_BLK,  //3
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_VIU, C_DWN, C_VIU, C_SYM, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_BLK, C_LCK, C_CMD, C_CMD, C_ENT, C_SYM, C_BLK, C_BLK },//5
    //MOUSE
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //1
	  C_SYM, C_LFT, C_UPP, C_RGT, C_BLK, C_BLK, C_RB1, C_BLK, C_UPP, C_LFT, C_UPP, C_RGT, C_SYM, C_BLK, C_BLK,  //2
	  C_ENT, C_LFT, C_DWN, C_RGT, C_BLK, C_BLK, C_RB2, C_BLK, C_DWN, C_LFT, C_CMD, C_RGT, C_ENT, C_BLK, C_BLK,  //3
	  C_CMD, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB3, C_UPP, C_CMD, C_BLK, C_DWN, C_BLK, C_CMD, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_LFT, C_RGT, C_LFT, C_DWN, C_RGT, C_LFT, C_RGT, C_BLK, C_BLK, C_BLK, C_BLK },//5
    //CONTROL
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_BLK, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK,  //1
	  C_RB6, C_RB7, C_RB2, C_RB1, C_RB1, C_RB5, C_BLK, C_BLK, C_BLK, C_RB7, C_RB4, C_RB2, C_RB6, C_RB3, C_BLK,  //2
	  C_BLK, C_RB4, C_RB5, C_RB2, C_RB7, C_RB3, C_RB6, C_BLK, C_RB4, C_RB2, C_RB1, C_RB5, C_RB4, C_BLK, C_BLK,  //3
	  C_BLK, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_RB2, C_BLK, C_RB1, C_RB5, C_RB3, C_BLK, C_BLK, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },//5
    //MEDIA
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LFT, C_RGT, C_LFT, C_RGT, C_LCK, C_ENT,  //1
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB6, C_RB5, C_RB4, C_RB3, C_RB2, C_RB1,  //2
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB6, C_RB5, C_RB4, C_RB3, C_RB2, C_RB1,  //3
	  C_RB1, C_RB2, C_RB3, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },//5
    //MACROS
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_BLK, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_BLK, C_BLK, C_BLK, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_BLK,  //1
	  C_BLK, C_RB6, C_RB1, C_RB2, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB6, C_RB1, C_RB2, C_RB3, C_RB4, C_BLK,  //2
	  C_BLK, C_RB5, C_RB6, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB5, C_RB6, C_RB1, C_RB2, C_RB3, C_BLK,  //3
	  C_BLK, C_RB4, C_RB5, C_RB6, C_RB1, C_RB2, C_BLK, C_BLK, C_BLK, C_RB4, C_RB5, C_RB6, C_RB1, C_RB2, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },//5
    //SYSTEM
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_RB1, C_RB2, C_RB3, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_CMD, C_CMD, C_RB1, C_CMD, C_RB1,  //1
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB4,  //2
	  C_BLK, C_RB5, C_RB5, C_RB5, C_RB5, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //3
	  C_LCK, C_RB4, C_RB4, C_RB4, C_RB4, C_RB4, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },//5
    //LAYERS
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_RB7, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //1
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //2
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //3
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK } //5
};

const uint8_t PROGMEM lc_base_shft[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_CMD, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_SYM, C_LCK, C_LCK, C_LCK, C_SYM,  //1
	  C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_CMD,  //2
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_VIU, C_CMD, C_VIU, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK,  //3
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_VIU, C_UPP, C_VIU, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_ACS,  //4
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_LFT, C_DWN, C_RGT, C_ENT, C_ACS, C_ACS, C_LYR, C_LYR, C_LYR };//5

const uint8_t PROGMEM lc_base_caps[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_CMD, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_SYM, C_SYM, C_SYM, C_SYM,  //1
	  C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM, C_SYM, C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_CMD,  //2
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_VIU, C_CMD, C_VIU, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM, C_SYM,  //3
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_VIU, C_UPP, C_VIU, C_LCK, C_LCK, C_SYM, C_SYM, C_SYM, C_ACS,  //4
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_LFT, C_DWN, C_RGT, C_ENT, C_ACS, C_ACS, C_LYR, C_LYR, C_LYR };//5

const uint8_t PROGMEM lc_npad_lock[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12-----13-----14-----15
	{ C_CMD, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_BLK, C_CMD,  //1
	  C_LCK, C_BLK, C_UPP, C_BLK, C_BLK, C_BLK, C_VIU, C_CMD, C_VIU, C_NUM, C_NUM, C_NUM, C_SYM, C_CMD, C_BLK,  //2
	  C_BLK, C_LFT, C_DWN, C_RGT, C_BLK, C_BLK, C_VIU, C_CMD, C_VIU, C_NUM, C_NUM, C_NUM, C_SYM, C_BLK, C_BLK,  //3
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_NUM, C_NUM, C_NUM, C_SYM, C_BLK, C_BLK,  //4
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_BLK, C_LCK, C_NUM, C_NUM, C_ENT, C_SYM, C_BLK, C_BLK };//5

HSV get_key_press_color(uint8_t i, HSV color_hsv) {
    if (ksp[i])
    {
        //flash randomly for the pressed key
        color_hsv.h = rand() % 256;
        color_hsv.s = 0xFF;
        color_hsv.v = 0xFF;
    }
    return color_hsv;
}

HSV get_layer_color(uint8_t layer, uint8_t i) {
  	HSV color_hsv = { C_BLK };

    bool shifted =
        ((layer == BASE) && (sft_down || caps_lck)) ||
        (layer == NPAD && nums_lck);

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

    if (layer == NPAD &&
        (i == idx_caps ||
         i == idx_nums ||
         i == idx_scrl))
    {
        //lock status
        uint16_t temp = layercolors[layer][li[i]*3];
        temp = (temp + 0x7F) % 256;
        if (caps_lck && i == idx_caps)
            color_hsv.h = temp;
        if (nums_lck && i == idx_nums)
            color_hsv.h = temp;
        if (scrl_lck && i == idx_scrl)
            color_hsv.h = temp;
    }

    if (layer == SYSC &&
        i == idx_nkro)
    {
        if (nk_rover)
        {
            uint16_t temp = layercolors[layer][li[i]*3];
            temp = (temp + 0x7F) % 256;
            color_hsv.h = temp;
        }
    }

    return color_hsv;
}

HSV  get_time_color(uint8_t i) {
  	HSV color_hsv;
    uint16_t ci = time_disp[li[i]];
    if (ci == 0)
    {
        color_hsv.h = 0;
        color_hsv.s = 0;
        color_hsv.v = 0;
    }
    else if (ci == 1)
    {
        color_hsv.h = 0;
        color_hsv.s = 0;
        color_hsv.v = 0xFF;
    }
    else
    {
        ci -= '0';
        color_hsv.h = ci * 0xFF / 11;
        color_hsv.s = 0xFF;
        color_hsv.v = 0xFF;
    }

    return color_hsv;
}

void set_my_color(void) {
    uint8_t layer = biton32(layer_state);
    uint8_t val = rgb_matrix_config.hsv.v;
    uint8_t hue = (uint16_t)(rgb_matrix_config.hsv.h);
    uint8_t sat = rgb_matrix_config.hsv.s;
    uint8_t time = scale16by8(g_rgb_timer, my_speed);
    float offset = time < 128 ? time : 255 - time;;
    offset *= 0.25f;
    time = (uint8_t)(offset);
    HSV color_hsv;

    for (int i = 0; i < GRID_COUNT; i++)
    {
        switch (disp_mode)
        {
        case DM_LAYER:
            color_hsv = get_layer_color(layer, i);
            break;
        case DM_TIME:
        case DM_TSEC:
        case DM_STOPW:
            color_hsv = get_time_color(i);
            break;
        }

        color_hsv = get_key_press_color(i, color_hsv);

        uint16_t hue2 = hue + color_hsv.h;
        hue2 = hue2 > 255 ? hue2 - 256 : hue2;
        color_hsv.h = (uint8_t)(hue2);
        color_hsv.s = (uint8_t)((float)(color_hsv.s) * sat / 255.0f);
        uint8_t time2 = hue2 < 64 || hue2 > 190 ? time / 2 : time;
        uint8_t val2 = val > time2 ? val - time2 : 0;
        color_hsv.v = color_hsv.v == 0 ? 0 : val2;
        RGB color = hsv_to_rgb(color_hsv);
        rgb_matrix_set_color( i, color.r, color.g, color.b );
    }
}

void set_disp_time_char(char c, uint8_t x0)
{
    if (c < '0' || c > '9') return;

    uint8_t digit = c - '0';
    for (uint8_t y = 0; y < TYPE_ROW; ++y)
    {
        for (uint8_t x = 0; x < TYPE_COL; ++x)
        {
            bool led_on = type_num[digit][y] & (1 << (2 - x));
            if (led_on)
                time_disp[y * DISP_COL + x + x0] = c;
        }
    }
}

void set_disp_time(void)
{
    for (uint8_t i = 0; i < GRID_COUNT; ++i)
        time_disp[i] = 0;
    time_disp[22] = 1;
    time_disp[52] = 1;
    for (uint8_t i = 0; i < 4; ++i)
        set_disp_time_char(time_buffer[i], time_x_pos[i]);
}

bool rgb_matrix_indicators_user(void) {
  my_speed = rgb_matrix_config.speed;
  if (my_speed > 0) my_speed += my_speed * g_last_hit_tracker.count;
  if (my_speed > 255) my_speed = 255;
  uint32_t mode = rgblight_get_mode();
  // assign colors if the matrix is on and the current mode
  // is SOLID COLORS => No animations running
  if(rgb_matrix_config.enable == 1 && mode == 1) {
    set_my_color();
  }
  return true;
}

void matrix_scan_user(void) {
    //get nk rollover status
    nk_rover = keymap_config.nkro;

    //get shift status
    if (get_mods() & MOD_MASK_SHIFT)
        sft_down = true;
    else
        sft_down = false;

    //get key press
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t i = row * MATRIX_COLS + col;
            if (matrix_is_on(row, col)) {
                ksp[li[i]] = true;
            } else {
                ksp[li[i]] = false;
            }
        }
    }

    // get time from usb
    switch (disp_mode) {
        case DM_TIME:
        case DM_TSEC:
        case DM_STOPW:
            set_disp_time();
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            //macros
            case MM0://build
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_B))));
                break;
            case MM1://run
                SEND_STRING(SS_LCTL(SS_TAP(X_F5)));
                break;
            case MM2://debug
                SEND_STRING(SS_TAP(X_F5));
                break;
            case MM3://stop debug
                SEND_STRING(SS_LSFT(SS_TAP(X_F5)));
                break;
            case MM4://close
                SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(100) SS_LALT(SS_TAP(X_F4)));
                break;
            case MM5://step over
                SEND_STRING(SS_TAP(X_F10));
                break;
            case MM6://step in
                SEND_STRING(SS_TAP(X_F11));
                break;
            case MM7://step out
                SEND_STRING(SS_LSFT(SS_TAP(X_F11)));
                break;
            case MM10://close tab
                SEND_STRING(SS_LCTL(SS_TAP(X_W)));
                break;
            case MM11://empty emails in outlook
                SEND_STRING(SS_TAP(X_BTN2) SS_DELAY(100) SS_TAP(X_Y));
                break;
            case MM15://select and look up
                SEND_STRING(SS_TAP(X_BTN1) SS_TAP(X_BTN1) SS_TAP(X_BTN1) SS_DELAY(100) SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_T)) SS_DELAY(200) SS_LCTL(SS_TAP(X_V)) SS_DELAY(100) SS_TAP(X_ENTER));
                break;
            case MM16://select and copy
                SEND_STRING(SS_TAP(X_BTN1) SS_TAP(X_BTN1) SS_DELAY(200) SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_TAB)));
                break;
            case MM17://copy and switch tab
                SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_TAB)));
                break;
            case MM18://focus and enter
                SEND_STRING(SS_TAP(X_BTN1) SS_LCTL(SS_TAP(X_V)) SS_DELAY(100) SS_TAP(X_ENTER) SS_DELAY(100) SS_TAP(X_ENTER));
                break;
            case MM19://open link in new tab
                SEND_STRING(SS_DOWN(X_LCTL) SS_DELAY(100) SS_TAP(X_BTN1) SS_DELAY(100) SS_UP(X_LCTL));
                break;

            //display modes
            case DK_LAYER://set mode to layer
                disp_mode = DM_LAYER;
                break;
            case DK_TIME://toggle time
                disp_mode = disp_mode == DM_TIME ? DM_LAYER : DM_TIME;
                break;
            case DK_TSEC://toggle time with sec
                disp_mode = disp_mode == DM_TSEC ? DM_LAYER : DM_TSEC;
                break;
            case DK_STOPW: // toggle stopwatch
                disp_mode = disp_mode == DM_STOPW ? DM_LAYER : DM_STOPW;
                break;
        }
    }
    return true;
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *cid        = &(data[0]);
    uint8_t *cdata      = &(data[1]);
    uint8_t  buffer[32] = {0};

    switch (*cid) {
        case ID_QUERY_MODE:
            buffer[0] = 0xFF;
            buffer[1] = ID_REPORT_MODE;
            buffer[2] = disp_mode;
            raw_hid_send(buffer, sizeof(buffer));
            break;
        case ID_UPDATE_TIME: {
            uint8_t ls = sizeof(time_buffer);
            ls         = length < ls ? length : ls;
            for (uint8_t i = 0; i < ls; i++) {
                time_buffer[i] = cdata[i];
            }
        } break;
        default: // debug
            //memset(buffer, 255, sizeof(buffer));
            //raw_hid_send(buffer, sizeof(buffer));
            break;
    }
}

// #endif

#include "p48.h"
#include <lib/lib8tion/lib8tion.h>

//#ifdef RGB_MATRIX_ENABLE

/* RGB Positioning */
led_config_t g_led_config = { {
    {   0,  1,  2,  3,  4,  5,  6},
    {  23, 22, 21, 20, 19, 18, 17},
    {  24, 25, 26, 27, 28, 29, 30},
    {  47, 46, 45, 44, 43, 42, 41},
    {   7,  8,  9, 10, 11, 13, 12},
    {  16, 15, 14, 31, 32, 33, 34},
    {  40, 39, 38, 37, 36, 35    }
}, {
    {0,0},    {21,0},   {41,0},   {62,0},   {82,0},   {102,0},  {123,0},  {143,0},  {163,0},  {184,0},  {204,0},  {224,0},
    {224,22}, {204,22}, {184,22}, {163,22}, {143,22}, {123,22}, {102,22}, {82,22},  {62,22},  {41,22},  {21,22},  {0,22},
    {0,42},   {21,42},  {41,42},  {62,42},  {82,42},  {102,42}, {123,42}, {143,42}, {163,42}, {184,42}, {204,42}, {224,42},
    {224,64}, {204,64}, {184,64}, {163,64}, {143,64}, {123,64}, {102,64}, {82,64},  {62,64},  {41,64},  {21,64},  {0,64}
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };

uint16_t my_speed = 0;
bool sft_down = false;
bool caps_lck = false;
bool nums_lck = false;
bool scrl_lck = false;
bool nk_rover = false;
uint16_t idx_caps = 42;
uint16_t idx_nums = 41;
uint16_t idx_scrl = 23;
uint16_t idx_nkro = 12;

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
    scrl_lck = host_keyboard_led_state().scroll_lock;

    return true;
}

//key state press
bool PROGMEM ksp[GRID_COUNT] =
{
    false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false, false
};

//key layout
const uint8_t PROGMEM ki[GRID_COUNT] =
{
//--1---2---3---4---5---6---7
    0,  1,  2,  3,  4,  5,  6,
   23, 22, 21, 20, 19, 18, 17,
   24, 25, 26, 27, 28, 29, 30,
   47, 46, 45, 44, 43, 42, 41,
    7,  8,  9, 10, 11, 13, 12,
   16, 15, 14, 31, 32, 33, 34,
   40, 39, 38, 37, 36, 35    
};

//led index mapping
const uint8_t PROGMEM li[GRID_COUNT] =
{
//--1---2---3---4---5---6---7---8---9---10--11--12
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
    23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36
};

const uint8_t PROGMEM layercolors[LAYER_NUM][GRID_COUNT*3] =
{
    //BASE
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_SYM, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM,
	  C_ACS, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM, C_SYM,
	  C_ACS, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_ABC, C_SYM, C_SYM, C_SYM, C_ACS,
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_ENT, C_ACS, C_LYR, C_LYR, C_LYR, C_LYR },
    //NUMB
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_CMD, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_NUM, C_SYM,
	  C_SYM, C_BLK, C_BLK, C_BLK, C_BLK, C_SYM, C_SYM, C_BLK, C_SYM, C_SYM, C_SYM, C_CMD,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //FUNC
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN, C_FUN,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //NUMPAD
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_CMD, C_BLK, C_UPP, C_BLK, C_CMD, C_VIU, C_VIU, C_VIU, C_UPP, C_VIU, C_SYM, C_CMD,
	  C_LCK, C_LFT, C_DWN, C_RGT, C_CMD, C_VIU, C_VIU, C_LFT, C_BLK, C_RGT, C_SYM, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_VIU, C_DWN, C_VIU, C_SYM, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_LCK, C_CMD, C_CMD, C_ENT, C_SYM, C_BLK },
    //MOUSE
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_SYM, C_LFT, C_UPP, C_RGT, C_BLK, C_RB1, C_RB1, C_LFT, C_UPP, C_RGT, C_SYM, C_BLK,
	  C_ENT, C_LFT, C_DWN, C_RGT, C_BLK, C_RB2, C_RB2, C_LFT, C_CMD, C_RGT, C_ENT, C_BLK,
	  C_CMD, C_BLK, C_BLK, C_BLK, C_BLK, C_RB3, C_CMD, C_BLK, C_DWN, C_BLK, C_CMD, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_LFT, C_RGT, C_LFT, C_RGT, C_LFT, C_RGT, C_BLK, C_BLK, C_BLK },
    //CONTROL
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_SYM, C_RB7, C_RB2, C_RB6, C_RB3, C_RB4, C_RB1, C_RB6, C_RB1, C_RB3, C_RB5, C_VIU,
	  C_VIU, C_RB4, C_RB5, C_RB2, C_RB7, C_RB3, C_RB2, C_RB1, C_RB5, C_RB4, C_BLK, C_VIU,
	  C_VIU, C_RB1, C_RB3, C_RB4, C_RB5, C_RB1, C_RB5, C_RB3, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //NUM_CONTROL
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_BLK, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_ENT, C_ENT, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //MEDIA
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LFT, C_RGT, C_LFT, C_RGT, C_LCK, C_ENT,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB6, C_RB5, C_RB4, C_RB3, C_RB2, C_RB1,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB6, C_RB5, C_RB4, C_RB3, C_RB2, C_RB1,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //MACROS
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_BLK, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_BLK,
	  C_BLK, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_BLK,
	  C_BLK, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //SYSTEM
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_CMD, C_CMD, C_RB1, C_CMD, C_RB1,
	  C_BLK, C_RB5, C_RB5, C_RB5, C_RB5, C_RB5, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_RB4,
	  C_LCK, C_RB4, C_RB4, C_RB4, C_RB4, C_RB4, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK },
    //LAYERS
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_RB4, C_RB5, C_RB6, C_RB7, C_RB1, C_RB2, C_RB3, C_RB4, C_RB5, C_RB6, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK }
};

const uint8_t PROGMEM lc_base_shft[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM,
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK,
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_ACS,
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_ENT, C_ACS, C_LYR, C_LYR, C_LYR, C_LYR };

const uint8_t PROGMEM lc_base_caps[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_SYM, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM,
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM, C_SYM,
	  C_ACS, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM, C_SYM, C_SYM, C_ACS,
	  C_LYR, C_CMD, C_LYR, C_LYR, C_SYM, C_SYM, C_ENT, C_ACS, C_LYR, C_LYR, C_LYR, C_LYR };

const uint8_t PROGMEM lc_numb_shft[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
	{ C_CMD, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_LCK, C_SYM,
	  C_LCK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_LCK, C_BLK, C_LCK, C_LCK, C_LCK, C_CMD,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK };

const uint8_t PROGMEM lc_npad_lock[GRID_COUNT*3] = 
    //--1------2------3------4------5------6------7------8------9-----10-----11-----12
    { C_CMD, C_BLK, C_UPP, C_BLK, C_CMD, C_VIU, C_VIU, C_LCK, C_LCK, C_LCK, C_SYM, C_CMD,
	  C_LCK, C_LFT, C_DWN, C_RGT, C_CMD, C_VIU, C_VIU, C_LCK, C_LCK, C_LCK, C_SYM, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_LCK, C_LCK, C_SYM, C_BLK,
	  C_BLK, C_BLK, C_BLK, C_BLK, C_BLK, C_LCK, C_LCK, C_LCK, C_LCK, C_ENT, C_SYM, C_BLK };

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
      (layer == NUMB && sft_down) ||
      (layer == NPAD && nums_lck);

  for (int i = 0; i < GRID_COUNT; i++)
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
        else if (layer == NUMB)
        {
            if (sft_down)
            {
                color_hsv.h = lc_numb_shft[li[i] * 3];
                color_hsv.s = lc_numb_shft[li[i] * 3 + 1];
                color_hsv.v = lc_numb_shft[li[i] * 3 + 2];
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

    if (ksp[i])
    {
        //flash randomly for the pressed key
        color_hsv.h = rand() % 256;
        color_hsv.s = 0xFF;
        color_hsv.v = 0xFF;
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
            if (i == GRID_COUNT) break;
            if (matrix_is_on(row, col)) {
                ksp[ki[i]] = true;
            } else {
                ksp[ki[i]] = false;
            }
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
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
                SEND_STRING(SS_LALT(SS_TAP(X_F4)));
                break;
            case MM10://step over
                SEND_STRING(SS_TAP(X_F10));
                break;
            case MM11://step in
                SEND_STRING(SS_TAP(X_F11));
                break;
            case MM12://step out
                SEND_STRING(SS_LSFT(SS_TAP(X_F11)));
                break;
            case MM20://select and look up
                SEND_STRING(SS_TAP(X_BTN1) SS_TAP(X_BTN1) SS_TAP(X_BTN1) SS_DELAY(100) SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_T)) SS_DELAY(200) SS_LCTL(SS_TAP(X_V)) SS_DELAY(100) SS_TAP(X_ENTER));
                break;
            case MM21://select and copy
                SEND_STRING(SS_TAP(X_BTN1) SS_TAP(X_BTN1) SS_DELAY(200) SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_TAB)));
                break;
            case MM22://copy and switch tab
                SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_TAB)));
                break;
            case MM23://focus and enter
                SEND_STRING(SS_TAP(X_BTN1) SS_LCTL(SS_TAP(X_V)) SS_DELAY(100) SS_TAP(X_ENTER) SS_DELAY(100) SS_TAP(X_ENTER));
                break;
        }
    }
    return true;
}

// #endif

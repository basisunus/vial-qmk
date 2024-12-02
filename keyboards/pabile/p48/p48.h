#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00,k01,k02,k03,k04,k05,k06,k40,k41,k42,k43,k44, \
    k10,k11,k12,k13,k14,k15,k16,k50,k51,k52,k45,k46, \
    k20,k21,k22,k23,k24,k25,k26,k53,k54,k55,k56,k65, \
    k30,k31,k32,k33,k34,k35,k36,k60,k61,k62,k63,k64 \
) \
{ \
    {k00,k01,k02,k03,k04,k05,k06}, \
    {k10,k11,k12,k13,k14,k15,k16}, \
    {k20,k21,k22,k23,k24,k25,k26}, \
    {k30,k31,k32,k33,k34,k35,k36}, \
    {k40,k41,k42,k43,k44,k45,k46}, \
    {k50,k51,k52,k53,k54,k55,k56}, \
    {k60,k61,k62,k63,k64,k65    } \
}

#define LAYER_NUM 11
// Defines names for use in layer keycodes and the keymap
enum layer_names
{
    BASE = 0,
    NUMB,
    FUNC,
    NPAD,
    MOUS,
    CTRL,
    NCTL,
    MEDI,
    MCRO,
    SYSC,
    LAYR
};

//keycodes for macros
enum custom_keycodes {
    MM0 = QK_KB_0,
    MM1,
    MM2,
    MM3,
    MM4,
    MM5,
    MM6,
    MM7,
    MM8,
    MM9,
    MM10,
    MM11,
    MM12,
    MM13,
    MM14,
    MM15,
    MM16,
    MM17,
    MM18,
    MM19,
    MM20,
    MM21,
    MM22,
    MM23,
    MM24,
    MM25,
    MM26,
    MM27,
    MM28,
    MM29
};

// display modes
enum disp_modes {
    DM_NONE  = 0,
    DM_LAYER,       // display color depending on key function
    DM_TIME,         // display current time from host
    DM_STOPW        // display time in mmss for a stopwatch
};

// keycodes for display modes
enum disp_keycodes {
    DK_LAYER = SAFE_RANGE,
    DK_TIME,
    DK_STOPW
};

// command id for hid
enum commands {
    ID_QUERY_MODE = 0xF0, // receive
    ID_REPORT_MODE,       // send
    ID_UPDATE_TIME        // receive
};

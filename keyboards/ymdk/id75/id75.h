#pragma once

#define LAYER_NUM 8
// Defines names for use in layer keycodes and the keymap
enum layer_names
{
    BASE = 0,
    NPAD,
    MOUS,
    CTRL,
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
    DM_NONE = 0,
    DM_LAYER, // display color depending on key function
    DM_TIME,  // display current time from host
    DM_TSEC,  // display time in mmss
    DM_STOPW  // display time in mmss for a stopwatch
};

// keycodes for display modes
enum disp_keycodes {
    DK_LAYER = SAFE_RANGE,
    DK_TIME,
    DK_TSEC,
    DK_STOPW };

// command id for hid
enum commands {
    ID_QUERY_MODE = 0xF0, // receive
    ID_REPORT_MODE,       // send
    ID_UPDATE_TIME        // receive
};

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
    M0 = QK_KB_0,
    M1,
    M2,
    M3,
    M4,
    M5,
    M6,
    M7,
    M8,
    M9,
    M10,
    M11,
    M12,
    M13,
    M14,
    M15,
    M16,
    M17,
    M18,
    M19,
    M20,
    M21,
    M22,
    M23,
    M24,
    M25,
    M26,
    M27,
    M28,
    M29
};

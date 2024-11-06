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
    M_M0 = SAFE_RANGE,
    M_M1,
    M_M2,
    M_M3,
    M_M4,
    M_M5,
    M_M6,
    M_M7,
    M_M8,
    M_M9,
    M_M10,
    M_M11,
    M_M12,
    M_M13,
    M_M14,
    M_M15,
    M_M16,
    M_M17,
    M_M18,
    M_M19,
    M_M20,
    M_M21,
    M_M22,
    M_M23,
    M_M24,
    M_M25,
    M_M26,
    M_M27,
    M_M28,
    M_M29
};

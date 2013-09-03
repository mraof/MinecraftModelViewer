#ifndef OSLINUX_H_INCLUDED
#define OSLINUX_H_INCLUDED
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/keysym.h>
#include "globals.h"

#define SLEEP(x) usleep((x) * 1000)

#define OS_KEY_LEFT     XK_Left
#define OS_KEY_RIGHT    XK_Right
#define OS_KEY_UP       XK_Up
#define OS_KEY_DOWN     XK_Down
#define OS_KEY_A        XK_a
#define OS_KEY_B        XK_b
#define OS_KEY_C        XK_c
#define OS_KEY_D        XK_d
#define OS_KEY_E        XK_e
#define OS_KEY_F        XK_f
#define OS_KEY_G        XK_g
#define OS_KEY_H        XK_h
#define OS_KEY_I        XK_i
#define OS_KEY_J        XK_j
#define OS_KEY_K        XK_k
#define OS_KEY_L        XK_l
#define OS_KEY_M        XK_m
#define OS_KEY_N        XK_n
#define OS_KEY_O        XK_o
#define OS_KEY_P        XK_p
#define OS_KEY_Q        XK_q
#define OS_KEY_R        XK_r
#define OS_KEY_S        XK_s
#define OS_KEY_T        XK_t
#define OS_KEY_U        XK_u
#define OS_KEY_V        XK_v
#define OS_KEY_W        XK_w
#define OS_KEY_X        XK_x
#define OS_KEY_Y        XK_y
#define OS_KEY_Z        XK_z
#define OS_KEY_COMMA    XK_comma
#define OS_KEY_RETURN   XK_Return
#define OS_KEY_CTRL     XK_Control_L
#define OS_KEY_SHIFT    XK_Shift_L
#define OS_KEY_ADD      XK_KP_Add
#define OS_KEY_SUBTRACT XK_KP_Subtract
#define OS_KEY_MULTIPLY XK_KP_Multiply
#define OS_KEY_DIVIDE   XK_KP_Divide
#define OS_KEY_SLASH    XK_slash

#endif // OSLINUX_H_INCLUDED

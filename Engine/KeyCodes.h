#pragma once
#include <math.h>
#include <bitset>

// A keycode is just an integer
typedef int KeyCode;

// Define virtual codes for each key.
#define KEYCODE_ARROWLEFT 0
#define KEYCODE_ARROWUP 1
#define KEYCODE_ARROWRIGHT 2
#define KEYCODE_ARROWDOWN 3
#define KEYCODE_Q 4
#define KEYCODE_W 5
#define KEYCODE_E 6
#define KEYCODE_R 7
#define KEYCODE_T 8
#define KEYCODE_Y 9
#define KEYCODE_U 10
#define KEYCODE_I 11
#define KEYCODE_O 12
#define KEYCODE_P 13
#define KEYCODE_A 14
#define KEYCODE_S 15
#define KEYCODE_D 16
#define KEYCODE_F 17
#define KEYCODE_G 18
#define KEYCODE_H 19
#define KEYCODE_J 20
#define KEYCODE_K 21
#define KEYCODE_L 22
#define KEYCODE_Z 23
#define KEYCODE_X 24
#define KEYCODE_C 25
#define KEYCODE_V 26
#define KEYCODE_B 27
#define KEYCODE_N 28
#define KEYCODE_M 29
#define KEYCODE_LEFTSHIFT 30
#define KEYCODE_LEFTCONTROL 31
#define KEYCODE_LEFTALT 32
#define KEYCODE_SPACEBAR 33
#define KEYCODE_RIGHTALT 34
#define KEYCODE_RIGHTCONTROL 35
#define KEYCODE_RIGHTSHIFT 36
#define KEYCODE_ENTER 37
#define KEYCODE_RETURN 37
#define KEYCODE_BACKSPACE 38
#define KEYCODE_HASHTAG 39
#define KEYCODE_1 40
#define KEYCODE_2 41
#define KEYCODE_3 42
#define KEYCODE_4 43
#define KEYCODE_5 44
#define KEYCODE_6 45
#define KEYCODE_7 46
#define KEYCODE_8 47
#define KEYCODE_9 48
#define KEYCODE_0 49
#define KEYCODE_MINUS 50
#define KEYCODE_PLUS 51
#define KEYCODE_FULLSTOP 52
#define KEYCODE_PERIOD 52
#define KEYCODE_COMMA 53
#define KEYCODE_FORWARDSLASH 54
#define KEYCODE_BACKSLASH 55
#define KEYCODE_HASHTAG 56
#define KEYCODE_SEMICOLON 57
#define KEYCODE_APOSTROPHE 58
#define KEYCODE_INSERT 59
#define KEYCODE_HOME 60
#define KEYCODE_PAGEUP 61
#define KEYCODE_DELETE 62
#define KEYCODE_END 63
#define KEYCODE_PAGEDOWN 64
#define KEYCODE_NUMPADFORWARDSLASH 65
#define KEYCODE_NUMPADASTERISK 66
#define KEYCODE_NUMPADMINUS 67
#define KEYCODE_NUMPADPLUS 68
#define KEYCODE_NUMPADENTER 69
#define KEYCODE_NUMPADRETURN 69
#define KEYCODE_NUMPADPERIOD 70
#define KEYCODE_NUMPAD0 71
#define KEYCODE_NUMPAD1 72
#define KEYCODE_NUMPAD2 73
#define KEYCODE_NUMPAD3 74
#define KEYCODE_NUMPAD4 75
#define KEYCODE_NUMPAD5 76
#define KEYCODE_NUMPAD6 77
#define KEYCODE_NUMPAD7 78
#define KEYCODE_NUMPAD8 79
#define KEYCODE_NUMPAD9 80
#define KEYCODE_F1 81
#define KEYCODE_F2 82
#define KEYCODE_F3 83
#define KEYCODE_F4 84
#define KEYCODE_F5 85
#define KEYCODE_F6 86
#define KEYCODE_F7 87
#define KEYCODE_F8 88
#define KEYCODE_F9 89
#define KEYCODE_F10 90
#define KEYCODE_F11 91
#define KEYCODE_F12 92
#define KEYCODE_BACKTICK 93
#define KEYCODE_TAB 94
#define KEYCODE_LEFTMOUSE 95
#define KEYCODE_MIDDLEMOUSE 96
#define KEYCODE_RIGHTMOUSE 97
#define KEYCODE_ESCAPE 98

// The amount of virtual codes
#define COUNT_KEYCODES 99

// Returns a bitset that represents a certain keycode.
// Multple keys can be checked at once as follows: GetKeyCodeBits(KEYCODE1) | GetKeycodeBits(KEYCODE2)
// This will check for both keys as it merges the two bitsets.
std::bitset<COUNT_KEYCODES> GetKeyCodeBits(KeyCode code);

// Keycodes are represented by a single bit within the bitset. The bits index is equal to the value of the keycode.
// For example, Getting the bits for the keycode: "KEYCODE_TAB" will return a bitset in which only the 95th bit is set.
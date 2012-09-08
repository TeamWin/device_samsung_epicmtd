// hardwarekeyboard.cpp - HardwareKeyboard object
// Custom hardware keyboard support for epicmtd aka Sprint Epic 4G

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/reboot.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include <string>

extern "C" {
#include "../common.h"
#include "../minuitwrp/minui.h"
#include "../recovery_ui.h"
}

#include "rapidxml.hpp"
#include "objects.hpp"
#include "../data.hpp"
#include <linux/input.h>

HardwareKeyboard::HardwareKeyboard(void) {
	// Do Nothing
	DataManager::SetValue("shift_down", 0);
	DataManager::SetValue("shift_up", 1);
	DataManager::SetValue("fn_down", 0);
	DataManager::SetValue("fn_up", 1);
	DataManager::SetValue("key_pressed", 0);
	DataManager::SetValue("last_key", 0);
}

HardwareKeyboard::~HardwareKeyboard() {
	// Do Nothing
}

int HardwareKeyboard::KeyDown(int key_code) {

	int keyboard = -1;
	int key_pressed, shift_down, shift_up, fn_down, fn_up;

	DataManager::GetValue("key_pressed", key_pressed);
	DataManager::GetValue("shift_down", shift_down);
	DataManager::GetValue("shift_up", shift_up);
	DataManager::GetValue("fn_down", fn_down);
	DataManager::GetValue("fn_up", fn_up);

#ifdef _EVENT_LOGGING
	LOGE("HardwareKeyboard::KeyDown %i\n", key_code);
#endif
	switch (key_code) {
		case 41: // Shift
			DataManager::SetValue("key_pressed", 0);
			DataManager::SetValue("shift_down", 1);
			DataManager::SetValue("shift_up", 0);
			DataManager::SetValue("fn_down", 0);
			DataManager::SetValue("fn_up", 1);
			return 0;
			break;
		case 31: // Fn
			DataManager::SetValue("key_pressed", 0);
			DataManager::SetValue("shift_down", 0);
			DataManager::SetValue("shift_up", 1);
			DataManager::SetValue("fn_down", 1);
			DataManager::SetValue("fn_up", 0);
			return 0;
			break;
		case 1: // 1
			keyboard = '1';
			break;
		case 2: // 2
			keyboard = '2';
			break;
		case 3: // 3
			if (fn_down || !fn_up)
				keyboard = '#';
			else
				keyboard = '3';
			break;
		case 4: // 4
			if (fn_down || !fn_up)
				keyboard = '$';
			else
				keyboard = '4';
			break;
		case 5: // 5
			if (fn_down || !fn_up)
				keyboard = '%';
			else
				keyboard = '5';
			break;
		case 6: // 6
			if (fn_down || !fn_up)
				keyboard = '^';
			else
				keyboard = '6';
			break;
		case 7: // 7
			if (fn_down || !fn_up)
				keyboard = '&';
			else
				keyboard = '7';
			break;
		case 8: // 8
			if (fn_down || !fn_up)
				keyboard = '*';
			else
				keyboard = '8';
			break;
		case 9: // 9
			if (fn_down || !fn_up)
				keyboard = '(';
			else
				keyboard = '9';
			break;
		case 10: // 0
			if (fn_down || !fn_up)
				keyboard = ')';
			else
				keyboard = '0';
			break;
		case 11: // q
			if (fn_down || !fn_up)
				keyboard = '~';
			else if (shift_down || !shift_up)
				keyboard = 'Q';
			else
				keyboard = 'q';
			break;
		case 12: // w
			if (fn_down || !fn_up)
				keyboard = '-';
			else if (shift_down || !shift_up)
				keyboard = 'W';
			else
				keyboard = 'w';
			break;
		case 13: // e
			if (fn_down || !fn_up)
				keyboard = '_';
			else if (shift_down || !shift_up)
				keyboard = 'E';
			else
				keyboard = 'e';
			break;
		case 14: // r
			if (fn_down || !fn_up)
				keyboard = '+';
			else if (shift_down || !shift_up)
				keyboard = 'R';
			else
				keyboard = 'r';
			break;
		case 15: // t
			if (fn_down || !fn_up)
				keyboard = '=';
			else if (shift_down || !shift_up)
				keyboard = 'T';
			else
				keyboard = 't';
			break;
		case 16: // y
			if (fn_down || !fn_up)
				keyboard = '[';
			else if (shift_down || !shift_up)
				keyboard = 'Y';
			else
				keyboard = 'y';
			break;
		case 17: // u
			if (fn_down || !fn_up)
				keyboard = ']';
			else if (shift_down || !shift_up)
				keyboard = 'U';
			else
				keyboard = 'u';
			break;
		case 18: // i
			if (fn_down || !fn_up)
				keyboard = ';';
			else if (shift_down || !shift_up)
				keyboard = 'I';
			else
				keyboard = 'i';
			break;
		case 19: // o
			if (fn_down || !fn_up)
				keyboard = ':';
			else if (shift_down || !shift_up)
				keyboard = 'O';
			else
				keyboard = 'o';
			break;
		case 20: // p
			if (fn_down || !fn_up)
				keyboard = '\\';
			else if (shift_down || !shift_up)
				keyboard = 'P';
			else
				keyboard = 'p';
			break;
		case 21: // a
			if (shift_down || !shift_up)
				keyboard = 'A';
			else
				keyboard = 'a';
			break;
		case 22: // s
			if (shift_down || !shift_up)
				keyboard = 'S';
			else
				keyboard = 's';
			break;
		case 23: // d
			if (fn_down || !fn_up)
				keyboard = '|';
			else if (shift_down || !shift_up)
				keyboard = 'D';
			else
				keyboard = 'd';
			break;
		case 24: // f
			if (fn_down || !fn_up)
				keyboard = '{';
			else if (shift_down || !shift_up)
				keyboard = 'F';
			else
				keyboard = 'f';
			break;
		case 25: // g
			if (fn_down || !fn_up)
				keyboard = '}';
			else if (shift_down || !shift_up)
				keyboard = 'G';
			else
				keyboard = 'g';
			break;
		case 26: // h
			if (fn_down || !fn_up)
				keyboard = '<';
			else if (shift_down || !shift_up)
				keyboard = 'H';
			else
				keyboard = 'h';
			break;
		case 27: // j
			if (fn_down || !fn_up)
				keyboard = '>';
			else if (shift_down || !shift_up)
				keyboard = 'J';
			else
				keyboard = 'j';
			break;
		case 28: // k
			if (fn_down || !fn_up)
				keyboard = '\'';
			else if (shift_down || !shift_up)
				keyboard = 'K';
			else
				keyboard = 'k';
			break;
		case 29: // l
			if (fn_down || !fn_up)
				keyboard = '\"';
			else if (shift_down || !shift_up)
				keyboard = 'L';
			else
				keyboard = 'l';
			break;
		case 30: // backspace
			keyboard = KEYBOARD_BACKSPACE;
			break;
		case 32: // z
			if (shift_down || !shift_up)
				keyboard = 'Z';
			else
				keyboard = 'z';
			break;
		case 33: // x
			if (shift_down || !shift_up)
				keyboard = 'X';
			else
				keyboard = 'x';
			break;
		case 34: // c
			if (shift_down || !shift_up)
				keyboard = 'C';
			else
				keyboard = 'c';
			break;
		case 35: // v
			if (shift_down || !shift_up)
				keyboard = 'V';
			else
				keyboard = 'v';
			break;
		case 36: // b
			if (fn_down || !fn_up)
				keyboard = '/';
			else if (shift_down || !shift_up)
				keyboard = 'B';
			else
				keyboard = 'b';
			break;
		case 37: // n
			if (fn_down || !fn_up)
				keyboard = '@';
			else if (shift_down || !shift_up)
				keyboard = 'N';
			else
				keyboard = 'n';
			break;
		case 38: // m
			if (fn_down || !fn_up)
				keyboard = '?';
			else if (shift_down || !shift_up)
				keyboard = 'M';
			else
				keyboard = 'm';
			break;
		case 40: // Enter key
			keyboard = KEYBOARD_ACTION;
			break;
		case 44: // ,
			keyboard = ',';
			break;
		case 45: // Space
			keyboard = ' ';
			break;
		case 47: // .
			if (fn_down || !fn_up)
				keyboard = '!';
			else
				keyboard = '.';
			break;
		case 39: // Up arrow
			keyboard = KEYBOARD_ARROW_UP;
			break;
		case 49: // Down arrow
			keyboard = KEYBOARD_ARROW_DOWN;
			break;
		case 48: // Left arrow
			keyboard = KEYBOARD_ARROW_LEFT;
			break;
		case 50: // Right arrow
			keyboard = KEYBOARD_ARROW_RIGHT;
			break;
		case 57: // keyboard back button
		case 158: // back button below screen
			PageManager::NotifyKey(KEY_BACK);
			DataManager::SetValue("key_pressed", 1);
			DataManager::SetValue("shift_up", 1);
			DataManager::SetValue("fn_up", 1);
			return 0;
			break;
		case 53: // keyboard home button
		case 102: // home button below screen
			PageManager::NotifyKey(KEY_HOME);
			DataManager::SetValue("key_pressed", 1);
			DataManager::SetValue("shift_up", 1);
			DataManager::SetValue("fn_up", 1);
			return 0;
			break;
		case 116: // power button
			PageManager::NotifyKey(KEY_POWER);
			DataManager::SetValue("key_pressed", 1);
			DataManager::SetValue("shift_up", 1);
			DataManager::SetValue("fn_up", 1);
			return 0;
			break;
#ifdef _EVENT_LOGGING
		default:
			LOGE("Unmapped keycode: %i\n", key_code);
			break;
#endif
	}
	DataManager::SetValue("key_pressed", 1);
	if (!shift_down && !shift_up)
		DataManager::SetValue("shift_up", 1);
	if (!fn_down && !fn_up)
		DataManager::SetValue("fn_up", 1);
	if (keyboard != -1) {
		DataManager::SetValue("last_key", keyboard);
		if (!PageManager::NotifyKeyboard(keyboard))
			return 1;  // Return 1 to enable key repeat
	} else {
		DataManager::SetValue("last_key", 0);
		PageManager::NotifyKey(keyboard);
	}
	return 0;
}

int HardwareKeyboard::KeyUp(int key_code) {
	int key_pressed;

	DataManager::GetValue("key_pressed", key_pressed);

#ifdef _EVENT_LOGGING
	LOGE("HardwareKeyboard::KeyUp %i\n", key_code);
#endif
	if (key_code == 41) { // Shift
		int key_pressed;

		DataManager::GetValue("key_pressed", key_pressed);
		DataManager::SetValue("shift_down", 0);
		if (key_pressed)
			DataManager::SetValue("shift_up", 1);
	} else if (key_code == 31) { // Fn
		int key_pressed;

		DataManager::GetValue("key_pressed", key_pressed);
		DataManager::SetValue("fn_down", 0);
		if (key_pressed)
			DataManager::SetValue("fn_up", 1);
	}
	return 0;
}

int HardwareKeyboard::KeyRepeat(void) {
	int last_key;

	DataManager::GetValue("last_key", last_key);
#ifdef _EVENT_LOGGING
	LOGE("HardwareKeyboard::KeyRepeat: %i\n", last_key);
#endif
	if (last_key)
		PageManager::NotifyKeyboard(last_key);
	return 0;
}

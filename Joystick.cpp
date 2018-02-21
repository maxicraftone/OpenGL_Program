#include <GLFW\glfw3.h>
#include "Joystick.h"

Joystick::Joystick(int id) {
	joystick_id = id;
}

int Joystick::getButtonID(JoystickButton button) {
	switch (button) {
	case BUTTON_A:
		return 0;
	case BUTTON_B:
		return 1;
	case BUTTON_X:
		return 2;
	case BUTTON_Y:
		return 3;
	case BUTTON_LB:
		return 4;
	case BUTTON_RB:
		return 5;
	case BUTTON_BACK:
		return 6;
	case BUTTON_START:
		return 7;
	case BUTTON_LS:
		return 8;
	case BUTTON_RS:
		return 9;
	case BUTTON_DIR_PAD_UP:
		return 10;
	case BUTTON_DIR_PAD_RIGHT:
		return 11;
	case BUTTON_DIR_PAD_DOWN:
		return 12;
	case BUTTON_DIR_PAD_LEFT:
		return 13;
	default:
		return NULL;
	}
}

int Joystick::getAxisID(JoystickAxis axis) {
	switch (axis) {
	case AXIS_LS_HORIZONTAL:
		return 0;
	case AXIS_LS_VERTICAL:
		return 1;
	case AXIS_RS_HORIZONTAL:
		return 2;
	case AXIS_RS_VERTICAL:
		return 3;
	case AXIS_LT:
		return 4;
	case AXIS_RT:
		return 5;
	}
}

bool Joystick::buttonPressed(JoystickButton button) {
	const unsigned char *buttons = getAllButtons();
	for (int id = 0; id < button_count; id++) {
		if (buttons[id] != 0) {
			if (getButtonID(button) == id) {
				return true;
			}
		}
	}
	return false;
}

const unsigned char *Joystick::getAllButtons() {
	return glfwGetJoystickButtons(joystick_id, &button_count);
}

bool Joystick::axisUsed(JoystickAxis axis) {
	const float *axes = getAllAxes();
	for (int id = 0; id < axis_count; id++) {
		if (((id != 4 && id != 5) && (axes[id] != 0)) || ((id == 4 || id == 5) && (axes[id] != -1))) {
			if (getAxisID(axis) == id) {
				return true;
			}
		}
	}
	return false;
}

const float *Joystick::getAllAxes() {
	return glfwGetJoystickAxes(joystick_id, &axis_count);
}

float Joystick::getAxisValue(JoystickAxis axis) {
	const float *axes = getAllAxes();
	for (int id = 0; id < axis_count; id++) {
		if (((id != 4 && id != 5) && (axes[id] != 0)) || ((id == 4 || id == 5) && (axes[id] != -1))) {
			if (getAxisID(axis) == id) {
				if (axes[id] > 1)
					return 1;
				else if (axes[id] < -1)
					return -1;
				else
					return axes[id];
			}
		}
	}
}
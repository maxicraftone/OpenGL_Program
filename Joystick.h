#ifndef JOYSTICK_H
#define JOYSTICK_H

enum JoystickButton {
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LB,
	BUTTON_RB,
	BUTTON_BACK,
	BUTTON_START,
	BUTTON_LS,
	BUTTON_RS,
	BUTTON_DIR_PAD_UP,
	BUTTON_DIR_PAD_RIGHT,
	BUTTON_DIR_PAD_DOWN,
	BUTTON_DIR_PAD_LEFT
};
enum JoystickAxis {
	AXIS_LS_HORIZONTAL,
	AXIS_LS_VERTICAL,
	AXIS_RS_HORIZONTAL,
	AXIS_RS_VERTICAL,
	AXIS_LT,
	AXIS_RT
};

class Joystick {
public:
	Joystick(int id);
	bool buttonPressed(JoystickButton button);
	bool axisUsed(JoystickAxis axis);
	int getButtonID(JoystickButton button);
	const unsigned char *getAllButtons();
	int getAxisID(JoystickAxis axis);
	const float *getAllAxes();
	float getAxisValue(JoystickAxis axis);
private:
	int joystick_id;
	int button_count;
	int axis_count;
};

#endif
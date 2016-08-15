#ifndef BUTTON_H_
#define BUTTON_H_

enum BUTTON_STATE
{
	IDLE,
	HELD,
	PRESSED,
	RELEASED,
	STATE_TOTAL,
};

class Button
{
public:
	Button();
	virtual ~Button();
	virtual void Update() = 0;
	BUTTON_STATE GetButtonState();

protected :
	bool isButtonState;
	BUTTON_STATE currentButtonState;
};

#endif // !BUTTON_H_

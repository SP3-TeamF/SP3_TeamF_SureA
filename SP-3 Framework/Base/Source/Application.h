#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "MyMath.h"
#include "GlobalDatas.h"
#include "Collisiontest.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	bool GetMouseUpdate();
	bool GetKeyboardUpdate();

	//Get Window Variables
	static int GetWindowWidth();
	static int GetWindowHeight();

	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;

	//Mouse Functions
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 0;
    const static int m_window_width = 1024;
    const static int m_window_height = 800;

	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;
};

#endif
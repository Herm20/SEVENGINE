#ifndef INPUTPOLLER_H_

#define INPUTPOLLER_H_

#include "InputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>


#define Max_keys 500
#define Max_Buttons 16

class Input
{
	InputManager* inputmanager;
	static bool m_keys[Max_keys];
	static bool m_mouse_buttons[Max_Buttons];
	static double mouseX, mouseY;
	
public:
	Input(GLFWwindow* window);
	inline double GetX() { return mouseX; }
	inline double GetY() { return mouseY; }
	void Init(GLFWwindow* window); // initializer takes a pointer to the window from the renderer class

private:
	friend static void key_callback(GLFWwindow* , int, int, int , int); // callback for keys
	friend static void mouse_button_callback(GLFWwindow* , int , int , int);//callback for mousebutton
	friend static void cursor_position_callback(GLFWwindow*, double, double);//callback for mouse cursor
};

#endif // !INPUTPOLLER_H_

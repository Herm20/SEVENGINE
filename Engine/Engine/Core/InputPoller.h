#ifndef INPUTPOLLER_H_

#define INPUTPOLLER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define Max_keys 500
#define Max_Buttons 16

class Input
{
	//InputManager* inputmanager;
	static bool m_keys[Max_keys];
	static bool m_mouse_buttons[Max_Buttons];
	static double mouseX, mouseY;
	
public:
	void Init(GLFWwindow* window); // initializer takes a pointer to the window from the renderer class
	inline double GetX() { return mouseX; }
	inline double GetY() { return mouseY; }
	static inline int GetKey(int key) { return m_keys[key]; }

private:
	static void key_callback(GLFWwindow* , int, int, int , int); // callback for keys
	static void mouse_button_callback(GLFWwindow* , int , int , int);//callback for mousebutton
	static void cursor_position_callback(GLFWwindow*, double, double);//callback for mouse cursor
};

#endif // !INPUTPOLLER_H_

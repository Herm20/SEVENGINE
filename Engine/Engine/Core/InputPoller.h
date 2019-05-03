#ifndef INPUT_POLLER_H_
#define INPUT_POLLER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define Max_keys 500
#define Max_Buttons 16

class Input
{
	static bool m_keys[Max_keys];
	static bool lastKeyStates[Max_keys];
	static bool m_mouse_buttons[Max_Buttons];
	static bool lastMouseStates[Max_Buttons];
	static double mouseX, mouseY;

public:
	void Init(GLFWwindow* window);
	inline double GetX() { return mouseX; }
	inline double GetY() { return mouseY; }
	static inline int GetKey(int key) { return m_keys[key]; }
	static bool GetKeyDown(int key) { return (!lastKeyStates[key] && m_keys[key]); }
	static bool GetKeyUp(int key) { return (lastKeyStates[key] && !m_keys[key]); }
	static inline int GetMouse(int button) { return m_mouse_buttons[button]; }
	static bool GetMouseDown(int button) { return (!lastMouseStates[button] && m_mouse_buttons[button]); }
	static bool GetMouseUp(int button) { return (lastMouseStates[button] && !m_mouse_buttons[button]); }
	static void UpdateKeyStates(); // keeps track of the current keystates to be checked in the next frame

private:
	static void key_callback(GLFWwindow* , int, int, int , int); // callback for keys
	static void mouse_button_callback(GLFWwindow* , int , int , int); //callback for mousebutton
	static void cursor_position_callback(GLFWwindow*, double, double); //callback for mouse cursor
};

#endif // !INPUT_POLLER_H_

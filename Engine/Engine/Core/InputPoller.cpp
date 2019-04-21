#include "InputPoller.h"
//#include "InputManager.h"
bool Input::m_keys[Max_keys] = {};
bool Input::m_mouse_buttons[Max_Buttons] = {};
bool Input::lastKeyStates[Max_keys] = {};
double Input::mouseX;
double Input::mouseY;

//Private Callbacks///////////////
//callback for key presses
void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::m_keys[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);// modifies the list of key states
	// GLFW_RELEASE
	
}

//callback for  mouse presses
void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Input::m_mouse_buttons[button] = action == GLFW_PRESS;// modifies the list of key states
	/*if (action != GLFW_PRESS)
	{
	}*/
}

//callback for updating mouse cursor position
void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Input::mouseX = xpos;
	Input::mouseY = ypos;
}
//////////////////////////////////

//initializer
void Input::Init(GLFWwindow* window)
{	
	//setting up callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
}

void Input::UpdateKeyStates()/////////////This should be called in the update loop after the all the input has been processsed for that update loop
{
	for (int i = 0; i < Max_keys; i++)
	{
		lastKeyStates[i] = m_keys[i];
	}
}

bool Input::GetKeyDown(int keyValue)
{
	if (!lastKeyStates[keyValue] && m_keys[keyValue])
	{
		return true;
	}
	return false;
}

bool Input::GetKeyUp(int keyValue)
{
	if (lastKeyStates[keyValue] && !m_keys[keyValue])
	{
		return true;
	}
	return false;
}

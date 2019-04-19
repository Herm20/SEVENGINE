#include "InputPoller.h"
//#include "InputManager.h"
bool Input::m_keys[Max_keys];
bool Input::m_mouse_buttons[Max_Buttons];
double Input::mouseX;
double Input::mouseY;


//Private Callbacks///////////////
//callback for key presses
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::m_keys[key] = action == GLFW_PRESS;// modifies the list of key states
	/*if (action == GLFW_PRESS)
	{
	}*/
}

//callback for  mouse presses
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Input::m_mouse_buttons[button] = action == GLFW_PRESS;// modifies the list of key states
	/*if (action != GLFW_PRESS)
	{
	}*/
}

//callback for updating mouse cursor position
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Input::mouseX = xpos;
	Input::mouseY = ypos;
}
//////////////////////////////////

Input::Input(GLFWwindow* window) 
{
	//inputmanager = InputManager::GetInstance();
	Init(window);
}

//initializer
void Input::Init(GLFWwindow* window)
{
	for (int i = 0; i < Max_keys; i++)
	{
		Input::m_keys[i] = false;
	}

	for (int i = 0; i < Max_Buttons; i++)
	{
		Input::m_mouse_buttons[i] = false;
	}
	
	//setting up callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
}

bool Input::ReturnStatus(int keyValue)
{
	return m_keys[keyValue];
}

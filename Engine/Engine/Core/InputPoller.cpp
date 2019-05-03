#include "InputPoller.h"

bool Input::m_keys[Max_keys] = {};
bool Input::m_mouse_buttons[Max_Buttons] = {};
bool Input::lastKeyStates[Max_keys] = {};
bool Input::lastMouseStates[Max_Buttons] = {};
double Input::mouseX;
double Input::mouseY;

//callback for key presses
void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		Input::m_keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		Input::m_keys[key] = false;
	}

}

//callback for  mouse presses
void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Input::m_mouse_buttons[button] = action == GLFW_PRESS;
}

//callback for updating mouse cursor position
void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Input::mouseX = xpos;
	Input::mouseY = ypos;
}

void Input::Init(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
}

void Input::UpdateKeyStates() {
	for (int i = 0; i < Max_keys; i++) {
		lastKeyStates[i] = m_keys[i];
	}
	for (int i = 0; i < Max_Buttons; i++) {
		lastMouseStates[i] = m_mouse_buttons[i];
	}
}
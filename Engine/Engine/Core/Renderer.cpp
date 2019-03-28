#include "Renderer.h"

Renderer::Renderer(const AssetManager* am)
{
	//Initialize the GLFW Library
	if (!glfwInit())
	{
		return;
	}

	//Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(width, height, "SEVENGINE", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	//Make the window's context current
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return;
	}

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	this->am = am;
}


Renderer::~Renderer()
{
	glDeleteProgram(mainShaderProgram);
	mainShaderProgram = 0;
	vertexShader = 0;
	fragmentShader = 0;
	glfwTerminate();
}

//Returns the active window
GLFWwindow * Renderer::GetWindow()
{
	return window;
}

int Renderer::GetWindowHeight()
{
	return height;
}

int Renderer::GetWindowWidth()
{
	return width;
}

void Renderer::CreateBasicProgram()
{
	vertexShader = am->GetShader("VertexShader");
	fragmentShader = am->GetShader("FragmentShader");

	//Creates a graphics pipeline with the necessary shaders for general usage
	mainShaderProgram = glCreateProgram();
	glAttachShader(mainShaderProgram, vertexShader->GetID());
	glAttachShader(mainShaderProgram, fragmentShader->GetID());
	glLinkProgram(mainShaderProgram);

	//Determines program creation success
	GLint linked = 0;
	glGetProgramiv(mainShaderProgram, GL_LINK_STATUS, &linked);

	//Retreives program information upon creation failure
	if (linked == true)
	{
		glUseProgram(mainShaderProgram);
	}

	else
	{
		GLint logLength = 0;
		glGetProgramiv(mainShaderProgram, GL_INFO_LOG_LENGTH, &logLength);
		GLchar* infoLog = new GLchar[logLength];
		glGetProgramInfoLog(mainShaderProgram, logLength, 0, infoLog);
		Logger::Log(Logger::ERROR, infoLog);
		glDeleteProgram(mainShaderProgram);
		delete[] infoLog;
	}

	testMesh = new Mesh(am->GetMesh("box"));
	
	

}

//Iterates through and draws all entities to the screen
void Renderer::Draw()
{
	//Wipe the screen with that sweet sweet cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 0.0f);

	//Clear those buffers
	glClear(GL_COLOR_BUFFER_BIT);

	// Set transform
	glm::vec3 position = glm::vec3(0, 0, 5);
	glm::mat4 posMatrix = glm::translate(glm::mat4(), position);
	glUniformMatrix4fv(3, 1, GL_FALSE, &posMatrix[0][0]);

	// Draw object
	testMesh->Render();
	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

	//Poll for and process events
	glfwPollEvents();
}

bool Renderer::ShouldClose()
{
	return glfwWindowShouldClose(window);
}
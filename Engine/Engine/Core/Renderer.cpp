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

	//Generate our vertex array object
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	CreateTriangle();

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
		printf(infoLog);
		glDeleteProgram(mainShaderProgram);
		delete[] infoLog;
		//TODO: Print error
	}
}

//Iterates through and draws all entities to the screen
void Renderer::Draw()
{
	//Wipe the screen with that sweet sweet cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 0.0f);

	//Clear those buffers
	glClear(GL_COLOR_BUFFER_BIT);

	CreateTriangle();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,			//attribute 0. Must match the layout in the shader
		3,			//size
		GL_FLOAT,	//type
		GL_FALSE,	//normalized?
		0,			//stride
		(void*)0	//array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

	//Poll for and process events
	glfwPollEvents();
}

void Renderer::DrawEntity(Entity * _entity)
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_entity->mData->getVertices()), _entity->mData->getVertices(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,			//attribute 0. Must match the layout in the shader
		3,			//size
		GL_FLOAT,	//type
		GL_FALSE,	//normalized?
		0,			//stride
		(void*)0	//array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

	//Poll for and process events
	glfwPollEvents();
}

//Exists temporarily to provide proof of concept
void Renderer::CreateTriangle()
{
	//Triangle vertices
	static const GLfloat tri_buffer_data[] = {
		-1.0f, -1.0f, +0.0f,
		+1.0f, -1.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
	};

	//Generates and Binds a buffer with our triangle data
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_buffer_data), tri_buffer_data, GL_STATIC_DRAW);
}

#include <glad/glad.h>
#include <glfw3.h>
#include "Game.h"
#include "resource_manager.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_callback(GLFWwindow*, int, int);

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
Game Breakout = Game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glGetError();

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

     glEnable(GL_CULL_FACE);
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     
	Breakout.Init();
	
	while (!glfwWindowShouldClose(window))
	{		
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		Breakout.ProcessInput(deltaTime);
		Breakout.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);		
		Breakout.Render();
		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)  
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}

void framebuffer_callback(GLFWwindow*window, int width, int height)
{
	glViewport(0, 0, width, height);
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
//using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow* window); 

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Currently have OpenGL 4.6 installed. Using 3 now  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Creating Window Object. Width and Height set to 800x600
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
	
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1; 
	}
	//makes window the main context of the current thread
	glfwMakeContextCurrent(window); 

	//Check if GLAD is initialized. Give GLAD the load address of OpenGL function pointers

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initalize GLAD" << std::endl;
		return -1; 
	}

	//size of rendering window. Can be smaller than GLFW window
	glViewport(0, 0, 800, 600); 
	
	//callback before renderloop and after creating window 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render loop

	//Double Buffers - front buffer is the final output image, rendering commands are in the back buffer.
	// Once rendering is done, swap the buffers to updpate image.
	// each iteration of render loop is called a "Frame"  
	
	while (!glfwWindowShouldClose(window)) {

		//input 
		processInput(window); 

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //sets color state 
		glClear(GL_COLOR_BUFFER_BIT);         //retrieve color state and use in buffer


		//check and call events and swap the buffers 
		glfwSwapBuffers(window);         
		glfwPollEvents();                 //checks for input/event triggers 
	}


	//clean/delete GLFW resources 

	glfwTerminate(); 
	return 0; 

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); 
}


//check whether the escape key is pressed. If so then closee the window. 
void processInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	
		glfwSetWindowShouldClose(window, true); 
	}
}

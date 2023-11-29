#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "Shader.h"
//using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow* window); 

//Shader Source code
const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location =1) in vec3 aColor;\n"

"out vec3 ourColor;\n"

"void main()\n"
"{\n"
" gl_Position = vec4 (aPos, 1.0f);\n"
" ourColor = aColor;\n"
"}\0";

//fragment shader source 
const char* fragmentShaderSource1 = 
"#version 330 core\n"
    "out vec4 FragColor;\n"
	"in  vec3 ourColor;\n"
    "void main()\n"
    "{\n"
	"   FragColor = vec4(ourColor,1.0f);\n"
	"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"

"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";



int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Currently have OpenGL 4.6 installed. Using 3 now  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Creating Window Object. Width and Height set to 800x600
	/*--------------------*/
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

	//two different shader objects that use different fragment shaders 

	Shader ourShader1("vertex_shader1.txt","fragment_shader1.txt");   

	Shader ourShader2("vertex_shader1.txt","fragment_shader2.txt"); 


	//VertexShader 
	/*--------------------*/
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader); 

	////check for compile errors
	//int success; 
	//char infoLog[512]; 
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//if (!success)
	//{	
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); 
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl; 
	//}

	////FragmentShader 
 //   /*--------------------*/
	//unsigned int fragmentShader[2]; 


	//fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader[0], 1, &fragmentShaderSource1, NULL);  //replaces source code in a shader object 
	//glCompileShader(fragmentShader[0]);

	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER); 

	//glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);  //replaces source code in a shader object  
	//glCompileShader(fragmentShader[1]); 

	//if (!success) 
	//{ 
	//	glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog); 
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl; 
	//} 


	////Linking Shaders. Links output of each shader to the inputs of the next shader 
	//unsigned int shaderProgram[2];  

	//shaderProgram[0] = glCreateProgram();  //returns ID referance to program 
	//glAttachShader(shaderProgram[0], vertexShader);
	//glAttachShader(shaderProgram[0], fragmentShader[0]);
	//glLinkProgram(shaderProgram[0]);

	//// check for linking errors
	//glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	//}

	//shaderProgram[1] = glCreateProgram(); 
	//glAttachShader(shaderProgram[1], vertexShader); 
	//glAttachShader(shaderProgram[1], fragmentShader[1]);
	//glLinkProgram(shaderProgram[1]); 

	//// check for linking errors
	//glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success); 
	//if (!success) { 
	//	glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog); 
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl; 
	//} 

	////can delete shader objects after linking 
	//glDeleteShader(vertexShader); 
	//glDeleteShader(fragmentShader[0]);
	//glDeleteShader(fragmentShader[1]); 


	//single triangle coordinates. Normalized (-1 to 1) 
	float firstTrivertices[]{

		-.5f,-.5f,0.0f, 1.0f ,  0.0f , 0.0f  ,
		-.25f, 0.5f, 0.0f, 0.0f ,  1.0f   , 0.0f  ,
		0.0f, -0.5f, 0.0f, 0.0f , 0.0f, 1.0f
		 


	}; 

	float secondTrivertices[]{
		0.0,-0.5f, 0.0f,  
		0.25f, 0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 

	};


	// Box (Two Triangles) 
	//float vertices[]{
	//	0.5f,   0.5f, 0.0f,
	//	0.5f,  -0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	-0.5f,  0.5f, 0.0f



	//};

	unsigned int indices[]{
		0,1,3,   //first triangle 
		1,2,3    // second triangle 
	};

	/*Store Vertex Data on Graphics Card*/
	/*--------------------*/

	//created vertex buffer and vertex arrray  

	unsigned int VAOs[2], VBOs[2];   //Can generate several VAO nad VBOs at the same  time

	glGenVertexArrays(2, VAOs); 
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);  

	//binds created buffer to GL_ARRAY_Buffer 
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	//copy user defined data into the bounded buffer 
    //first arg is the buffer, second is size of data, thrid is acutal data, fourth is how to manage data (stream, static, dynamic)
    //static = data is sent once and used many times 
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTrivertices), firstTrivertices, GL_STATIC_DRAW); 

	// 0 = specifies location of position vertex attribute in vertex shader. 
	//3 = Composed of 3 values. Vec3 
	//type of data is GL_FLOAT
	//Do want data normalized? If, NO then GL_FALSE 
	//specifies stride which is how far away the next set of values are. 
	//position offset if data is not right at beggining of array. Void *  0 for this case 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0); 

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1); 


	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTrivertices), secondTrivertices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0); 




	/*Creating EBO*/
	unsigned int EBO; 
	glGenBuffers(1, &EBO); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
	 

	


	/*--------------------*/



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

		//render 
		ourShader1.use(); 
		//glUseProgram(shaderProgram[0]);
		glBindVertexArray(VAOs[0]);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  
		//glBindVertexArray(0); 
		glDrawArrays(GL_TRIANGLES,0,3);                     //third parameter determines the number of vertices to render


		float timeVal = glfwGetTime(); 
		float greenValue = (sin(timeVal) / 2.0f) + 0.5f;
		int vertexColorLoc = glGetUniformLocation(ourShader2.ID, "ourColor"); //get location of variable in shader


		ourShader2.use();
		//glUseProgram(shaderProgram[1]); 
		glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);   //add green value to uniform variable in shader. Shaderprogram must be in use to be able to change uniform value.
		glBindVertexArray(VAOs[1]); 
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		//check and call events and swap the buffers 
		glfwSwapBuffers(window);         
		glfwPollEvents();                 //checks for input/event triggers 
	}


	//de-alocate recources 
	glDeleteVertexArrays(2, VAOs); 
	glDeleteBuffers(2, VBOs); 
	glDeleteProgram(ourShader1.ID);
	glDeleteProgram(ourShader2.ID); 



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
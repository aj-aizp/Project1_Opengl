#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
//using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow* window); 

//Shader Source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//fragment shader source 
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
	"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
   // "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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




	//VertexShader 
	/*--------------------*/
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); 

	//check for compile errors
	int success; 
	char infoLog[512]; 
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{	
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); 
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl; 
	}

	//FragmentShader 
    /*--------------------*/
	unsigned int fragmentShader; 
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);  //replaces source code in a shader object 
	glCompileShader(fragmentShader); 

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Linking Shaders. Links output of each shader to the inputs of the next shader 
	unsigned int shaderProgram; 
	shaderProgram = glCreateProgram();  //returns ID referance to program 
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader); 
	glLinkProgram(shaderProgram); 

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//can delete shader objects after linking 
	glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader); 


	//single triangle coordinates. Normalized (-1 to 1) 
	float vertices[]{

		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	/*Store Vertex Data on Graphics Card*/
	/*--------------------*/

	//created vertex buffer and vertex arrray 
	unsigned int VAO; 
	glGenVertexArrays(1, &VAO); 
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); 

	//binds created buffer to GL_ARRAY_Buffer 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//copy user defined data into the bounded buffer 
    //first arg is the buffer, second is size of data, thrid is acutal data, fourth is how to manage data (stream, static, dynamic)
    //static = data is sent once and used many times 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	 

	// 0 = specifies location of position vertex attribute in vertex shader. 
	//3 = Composed of 3 values. Vec3 
	//type of data is GL_FLOAT
	//Do want data normalized? If, NO then GL_FALSE 
	//specifies stride which is how far away the next set of values are. 
	//position offset if data is not right at beggining of array. Void *  0 for this case 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 


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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);



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
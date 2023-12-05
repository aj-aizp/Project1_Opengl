#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "stb_image.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>



#include "Shader.h"
//using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow* window); 


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

	Shader ourShader3("texture_vertex_shader.txt", "texture_fragment_shader.txt"); 
	



	//Creating a Texture 

	unsigned int texture1, texture2; 

	glGenTextures(1, &texture1); 

	glBindTexture(GL_TEXTURE_2D, texture1); 

	//set texture wrapping options 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//loading an Image and pulling data from it 

	int width, height, nrChannels; 

	unsigned char *data = stbi_load("Texture_Practice.jpg", &width, &height, &nrChannels, 0); 

	//std::cout << width << std::endl; 


	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else {
		std::cout << "Failed to load texture" << std::endl; 
	}
	

	stbi_image_free(data); 

	glGenTextures(1, &texture2); 

	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 


	stbi_set_flip_vertically_on_load(true);  
	//.png have alpha channels. Need to add GL_RGBA instead of GL_RGB 
	data = stbi_load("Union_Soldier_Texture.png", &width, &height, &nrChannels, 0); 

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); 
		glGenerateMipmap(GL_TEXTURE_2D); 
	}

	else {
		std::cout << "Failed to load texture" << std::endl; 
	}

	stbi_image_free(data);

	ourShader3.use(); 

	glUniform1i(glGetUniformLocation(ourShader3.ID, "ourTexture1"), 0); 

	glUniform1i(glGetUniformLocation(ourShader3.ID, "ourTexture2"), 1); 





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


	// Box (Two Triangles). With Texure code, added colors and texture coordinates
	float vertices[]{
		0.5f,   0.5f, 0.0f, 1.0f,0.0f, 0.0f,  1.0f, 1.0f,
		0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f

	};

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	// 0 = specifies location of position vertex attribute in vertex shader. 
	//3 = Composed of 3 values. Vec3 
	//type of data is GL_FLOAT
	//Do want data normalized? If, NO then GL_FALSE 
	//specifies stride which is how far away the next set of values are. 
	//position offset if data is not right at beggining of array. Void *  0 for this case 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 *sizeof(float))); 
	glEnableVertexAttribArray(2); 

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
	//glEnableVertexAttribArray(1); 


	//glBindVertexArray(VAOs[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); 
	//glBufferData(GL_ARRAY_BUFFER, sizeof(secondTrivertices), secondTrivertices, GL_STATIC_DRAW); 

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
	//glEnableVertexAttribArray(0); 




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



		//glUseProgram(shaderProgram[0]);

		//bind texture
		glActiveTexture(GL_TEXTURE0); 
		glBindTexture(GL_TEXTURE_2D, texture1); 
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2); 

		//Create Transform Matrix 

		glm::mat4 trans = glm::mat4(1.0f); 
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f)); 
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));  



		ourShader3.use(); 

		unsigned int transformLoc = glGetUniformLocation(ourShader3.ID, "transform"); 
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); 


		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  
		//glBindVertexArray(0); 
		//glDrawArrays(GL_TRIANGLES,0,3);                     //third parameter determines the number of vertices to render


		//float timeVal = glfwGetTime(); 
		//float greenValue = (sin(timeVal) / 2.0f) + 0.5f;
		//int vertexColorLoc = glGetUniformLocation(ourShader2.ID, "ourColor"); //get location of variable in shader


		//ourShader2.use();
		//glUseProgram(shaderProgram[1]); 
		//glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);   //add green value to uniform variable in shader. Shaderprogram must be in use to be able to change uniform value.
		//glBindVertexArray(VAOs[1]); 
		//glDrawArrays(GL_TRIANGLES, 0, 3); 

		//check and call events and swap the buffers 
		glfwSwapBuffers(window);         
		glfwPollEvents();                 //checks for input/event triggers 
	}


	//de-alocate recources 
	glDeleteVertexArrays(2, VAOs); 
	glDeleteBuffers(2, VBOs); 
	glDeleteProgram(ourShader1.ID);
	glDeleteProgram(ourShader2.ID); 
	glDeleteProgram(ourShader3.ID); 



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
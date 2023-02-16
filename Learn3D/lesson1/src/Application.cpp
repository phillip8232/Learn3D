//Phillip Lim, Student, Number: 9157 , repo :github.com/phillip8232
#include <iostream>
#include <sstream>

#define GLEW_STATIC

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "ShaderProgram.h"
#include "Texture2D.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

#include "Camera.h"

const char* APP_TITLE = "Advaced Game Engine with Modern OpenGL";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
const std::string texture1Filename = "airplane.png";
const std::string texture2Filename = "crate.jpg";

bool gFullscreen = false;
GLFWwindow* pWindow = NULL;

bool gWireframe = false;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);
bool initOpenGL();

int selectedNum = 1; //Change this value or use keyboard input to change value to see shape change.
float rotationSpeed = 1;
bool toggle = false;

//Camera Header
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void windowResizeCallBack(GLFWwindow* window, int width, int height);

//-------------------------Camera------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//position of camera
float lastX = 400;
float lastY = 300;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	if (!initOpenGL())
	{
		std::cerr << "GLFW initialized fail." << std::endl;
		return (-1);
	}
	

	//------------------------FIRST--------------------------//
	GLfloat vert_pos[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2,  // First Triangle
		0, 2, 3   // Second Triangle
	};

	GLuint vbo;
	GLuint ibo;
	GLuint vao;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//------------------------SECOND--------------------------//
	GLfloat vert_tri_pos[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	GLuint tri_indices[] = {
		0, 1, 2,  // First Triangle
	};

	GLuint vbo2;
	GLuint ibo2;
	GLuint vao2;

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_tri_pos), vert_tri_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_indices), tri_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);


	//------------------------THIRD---------------------------//
	GLfloat vert_poly_pos[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //0
		0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   //1
		-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  //2

		0.4f, 0.45f, 0.0f, 1.0f, 1.0f,  //3
		-0.4f, 0.45f, 0.0f, 1.0f, 0.0f, //4
		0.0f, 0.7f,   0.0f, 1.0f, 0.0f, //5
	};

	GLuint poly_indices[] = {
		0, 1, 3,
		0, 3, 5,
		0, 4, 5,
		0, 2, 4,
	};

	GLuint vbo3;
	GLuint ibo3;
	GLuint vao3;

	glGenBuffers(1, &vbo3);
	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_poly_pos), vert_poly_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao3);
	glBindVertexArray(vao3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(poly_indices), poly_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	//------------------------Cube---------------------------//
	GLfloat CubeVert[] =
	{
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, //0
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, //1
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, //2
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, //3

		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, //4
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, //5
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //6
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, //7
		//--top & bottom--//
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, //8
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //9
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, //10
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, //11
	};

	GLuint CubeIndecies[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4 ,6, 7,
		7, 6, 1, 7, 1, 0,
		3, 2, 5, 3, 5, 4,
		11, 0, 3, 11, 3, 8,
		1, 10, 9, 1, 9, 2
	};

	//create cube VBO
	unsigned int textureCubeVBO;
	glGenBuffers(1, &textureCubeVBO);
	unsigned int textureCubeEBO;
	glGenBuffers(1, &textureCubeEBO);

	//create CUBE VAO
	unsigned int textureCubeVAO;
	glGenVertexArrays(1, &textureCubeVAO);
	glBindVertexArray(textureCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textureCubeVBO);

	//give data to Cube VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVert), CubeVert, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureCubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndecies), CubeIndecies, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(6.0f, 5.0f, -15.0f),
		glm::vec3(1.5f,-2.0f, -2.5f),
		glm::vec3(-4.0f, -0.5f, -7.0f)
	};
	//------------------------Pyramid-------------------------//
	GLfloat vert_pyramid_pos[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.5f, -0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		//left & right side
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f,

	};

	GLuint pyramid_indices[] = {
		0, 1, 2,  // First Triangle
		3, 4, 5,
		3, 1, 6,
		2, 4, 7
	};

	GLuint vbo4;
	GLuint ibo4;
	GLuint vao4;

	glGenBuffers(1, &vbo4);
	glBindBuffer(GL_ARRAY_BUFFER, vbo4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pyramid_pos), vert_pyramid_pos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao4);
	glBindVertexArray(vao4);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramid_indices), pyramid_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//---------------------ShaderProgram---------------------//
	ShaderProgram shaderProgram;
	shaderProgram.loadShader("basic.vert", "basic.frag");

	//shader lesson 7 Rotation
	ShaderProgram shaderProgram4;
	shaderProgram4.loadShader("BasicMatrix.vert", "BasicMatrix.frag");

	Texture2D texture1;
	texture1.loadTexture(texture1Filename, true);

	Texture2D texture2;
	texture2.loadTexture(texture2Filename, true);
	
	//load image
	stbi_set_flip_vertically_on_load(true);

	glfwSetFramebufferSizeCallback(pWindow, windowResizeCallBack);
	glfwSetCursorPosCallback(pWindow, mouse_callback);
	glfwSetScrollCallback(pWindow, scroll_callback);
	//Hide the cursor & lock the mouse in the window
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	int width, height, numberChannels;
	unsigned char* image1Data = stbi_load("crate.jpg", &width, &height, &numberChannels, 0);

	//If image was loaded
	if (image1Data)
	{
		std::cout << "Success! image is " << width << " x " << height << " pixels";

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1Data);

		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {
		std::cout << "Image load failed!\n";
	}
	//cleanup image memory
	stbi_image_free(image1Data);


	//Set Z depth buffer
	glEnable(GL_DEPTH_TEST);

	


	while (!glfwWindowShouldClose(pWindow))
	{
		showFPS(pWindow);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		texture1.bind(0);
		texture2.bind(1);

		//activate a program
		shaderProgram.use();

		glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "myTexture1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "myTexture2"), 1);

		GLfloat time = glfwGetTime() * (rotationSpeed * rotationSpeed);
		glm::vec2 pos;
		pos.x = sin(time) / 2;
		pos.y = cos(time) / 2;

		shaderProgram.setUniform("posOffset", pos);

		//Selecting Shape
		if (selectedNum == 1) 
		{
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		else if (selectedNum == 2)
		{
			glBindVertexArray(vao2);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
		else if (selectedNum == 3)
		{
			glBindVertexArray(vao3);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
		else if (selectedNum == 4)
		{
			shaderProgram4.use();

			//Setup Transform Matrix
			glm::mat4 transform = glm::mat4(1.0f);

			//Get transform uniform location
			glUniform1i(glGetUniformLocation(shaderProgram4.getProgram(), "myTexture2"), 1);
			int transformUniformLocation = glGetUniformLocation(shaderProgram4.mHandle, "transform");

			//Set it on the transform Matrix
			glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, glm::value_ptr(transform));

			//Rotate the model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, glm::vec3(1.0f, 1.0f, 0.0f));

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f ,100.0f);

			//transfer the Matrix to the shader
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
		else if (selectedNum == 5)
		{
			shaderProgram4.use();

			//Setup Transform Matrix
			glm::mat4 transform = glm::mat4(1.0f);

			//Get transform uniform location
			glUniform1i(glGetUniformLocation(shaderProgram4.getProgram(), "myTexture2"), 1);
			int transformUniformLocation = glGetUniformLocation(shaderProgram4.mHandle, "transform");

			//Set it on the transform Matrix
			glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, glm::value_ptr(transform));

			//Rotate the model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, glm::vec3(1.0f, 1.0f, 0.0f));

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

			view = camera.GetViewMatrix();
			projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

			//transfer the Matrix to the shader
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(textureCubeVAO);

			//toggle
			if (toggle)
			{
				glDrawElements(GL_TRIANGLES, (6 * 6), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				//glDrawElements(GL_TRIANGLES, (6 * 6), GL_UNSIGNED_INT, nullptr);
				for (int i = 0; i < 4; i++)
				{
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, cubePositions[i]);

					if (i % 2 == 0) {
						model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, glm::vec3(0.5f, 1.0f, 0.0f));
					}
					else {
						model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, glm::vec3(1.0f, 0.5f, 0.0f));
					}
					glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "model"), 1, GL_FALSE, glm::value_ptr(model));
					glDrawElements(GL_TRIANGLES, (6 * 6), GL_UNSIGNED_INT, nullptr);
				};
			}

			glBindVertexArray(0);
		}
		else if (selectedNum == 6)
		{
			shaderProgram4.use();

			//Setup Transform Matrix
			glm::mat4 transform = glm::mat4(1.0f);

			//Get transform uniform location
			glUniform1i(glGetUniformLocation(shaderProgram4.getProgram(), "myTexture2"), 1);
			int transformUniformLocation = glGetUniformLocation(shaderProgram4.mHandle, "transform");

			//Set it on the transform Matrix
			glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, glm::value_ptr(transform));

			//Rotate the model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

			//transfer the Matrix to the shader
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.mHandle, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(vao4);
			glDrawElements(GL_TRIANGLES, 6 * 4, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(pWindow);
	}

	//clean program
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
	return 0;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // clockwise order
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		selectedNum = 1;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		selectedNum = 2;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		selectedNum = 3;
	}
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		selectedNum = 4;
	}
	else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
		selectedNum = 5;
		toggle = !toggle;
	}
	else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
	{
		selectedNum = 6;
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		rotationSpeed = rotationSpeed - 0.1;
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		rotationSpeed = rotationSpeed + 0.1;
	}
}

void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); //return the number of second since GLFW started, as double.

	elapsedSeconds = currentSeconds - previousSeconds;
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed << APP_TITLE << " FPS: " << fps << " Frame Time: " << msPerFrame << "(ms)";

		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}

bool initOpenGL()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		system("pause");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (gFullscreen)
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);

		if (pVmode != NULL)
		{
			pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
		}
	}
	else
	{
		pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	}

	if (pWindow == NULL)
	{
		std::cerr << "Failed to create window" << std::endl;

		glfwTerminate();

		system("pause");
		return false;
	}

	glfwMakeContextCurrent(pWindow);

	glfwSetKeyCallback(pWindow, glfw_onKey);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;

		glfwTerminate();

		system("pause");
		return false;
	}

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	return true;
}

//for mouse input
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	//Update last x and y
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);

}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	//set FoV for camera
	camera.ProcessMouseScroll(yOffset);

}

//Resize to Change view port
void windowResizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


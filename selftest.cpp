//GL LIBRARIES
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//glm is used to create perspective and transform matrices
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//STANDARD LIBRARIES
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

//PERSONAL LIBRARIES
#include "pngloader.h"

using namespace std;

const int WIDTH = 1000;
const int HEIGHT = 1000;

//HELPER FUCNTIONS FROM EXAMPLES
// helper to check and display for shader compiler errors
bool check_shader_compile_status(GLuint obj) {
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(obj, length, &length, &log[0]);
		std::cerr << "Shader Error: " << &log[0];
		return false;
	}
	return true;
}

// helper to check and display for shader linker error
bool check_program_link_status(GLuint obj) {
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(obj, length, &length, &log[0]);
		std::cerr << "Shader Error: " << &log[0];
		return false;
	}
	return true;
}

void checkError(string text)
{
	//check for error in setup
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		cerr << text << error << endl;
	}
}

void glfwWindowLoader(GLFWwindow* &window)
{
	if(glfwInit() == GL_FALSE) {
		std::cerr << "failed to init GLFW" << std::endl;
		exit(1);
	}

	// select opengl version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create a window
	if((window = glfwCreateWindow(WIDTH, HEIGHT, "Shader Test", 0, 0)) == 0) {
			std::cerr << "failed to open window" << std::endl;
			glfwTerminate();
			exit(1);
	}


	glfwMakeContextCurrent(window);

	//if(glxwInit()) {
	//	std::cerr << "failed to init GL3W" << std::endl;
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return 1;
	//}
}

void makeCubeVBO(GLuint& vao, GLuint& vbo, GLuint& ibo)
{
	//setup buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat cubeData[] =
	{
	//  VERTEX COORDS          TEX COORDS         NORMAL VECTOR
	//  X     Y     Z           U     V           X     Y     Z
	//face 0:
	   1.0f, 1.0f, 1.0f,       1.0f, 1.0f,       0.0f, 0.0f, 1.0f, // vertex 0
	  -1.0f, 1.0f, 1.0f,       0.0f, 1.0f,       0.0f, 0.0f, 1.0f, // vertex 1
	   1.0f,-1.0f, 1.0f,       1.0f, 0.0f,       0.0f, 0.0f, 1.0f, // vertex 2
	  -1.0f,-1.0f, 1.0f,       0.0f, 0.0f,       0.0f, 0.0f, 1.0f, // vertex 3

	// face 1:
	   1.0f, 1.0f, 1.0f,       1.0f, 1.0f,       1.0f, 0.0f, 0.0f, // vertex 0
	   1.0f,-1.0f, 1.0f,       0.0f, 1.0f,       1.0f, 0.0f, 0.0f, // vertex 1
	   1.0f, 1.0f,-1.0f,       1.0f, 0.0f,       1.0f, 0.0f, 0.0f, // vertex 2
	   1.0f,-1.0f,-1.0f,       0.0f, 0.0f,       1.0f, 0.0f, 0.0f, // vertex 3

	// face 2:
	   1.0f, 1.0f, 1.0f,       1.0f, 1.0f,       0.0f, 1.0f, 0.0f, // vertex 0
	   1.0f, 1.0f,-1.0f,       0.0f, 1.0f,       0.0f, 1.0f, 0.0f, // vertex 1
	  -1.0f, 1.0f, 1.0f,       1.0f, 0.0f,       0.0f, 1.0f, 0.0f, // vertex 2
	  -1.0f, 1.0f,-1.0f,       0.0f, 0.0f,       0.0f, 1.0f, 0.0f, // vertex 3

	// face 3:
	   1.0f, 1.0f,-1.0f,       1.0f, 1.0f,       0.0f, 0.0f,-1.0f, // vertex 0
	   1.0f,-1.0f,-1.0f,       0.0f, 1.0f,       0.0f, 0.0f,-1.0f, // vertex 1
	  -1.0f, 1.0f,-1.0f,       1.0f, 0.0f,       0.0f, 0.0f,-1.0f, // vertex 2
	  -1.0f,-1.0f,-1.0f,       0.0f, 0.0f,       0.0f, 0.0f,-1.0f, // vertex 3

	// face 4:
	  -1.0f, 1.0f, 1.0f,       1.0f, 1.0f,      -1.0f, 0.0f, 0.0f, // vertex 0
	  -1.0f, 1.0f,-1.0f,       0.0f, 1.0f,      -1.0f, 0.0f, 0.0f, // vertex 1
	  -1.0f,-1.0f, 1.0f,       1.0f, 0.0f,      -1.0f, 0.0f, 0.0f, // vertex 2
	  -1.0f,-1.0f,-1.0f,       0.0f, 0.0f,      -1.0f, 0.0f, 0.0f, // vertex 3

	// face 5:
	   1.0f,-1.0f, 1.0f,       1.0f, 1.0f,       0.0f,-1.0f, 0.0f, // vertex 0
	  -1.0f,-1.0f, 1.0f,       0.0f, 1.0f,       0.0f,-1.0f, 0.0f, // vertex 1
	   1.0f,-1.0f,-1.0f,       1.0f, 0.0f,       0.0f,-1.0f, 0.0f, // vertex 2
	  -1.0f,-1.0f,-1.0f,       0.0f, 0.0f,       0.0f,-1.0f, 0.0f  // vertex 3
	}; // 6 faces with 4 vertices with 8 components (floats)

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4 * 8, cubeData, GL_STATIC_DRAW);

	//set up positions of attributes inside of the array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8.0f, (char*)0 + 0*sizeof(GLfloat));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8.0f, (char*)0 + 3*sizeof(GLfloat));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8.0f, (char*)0 + 5*sizeof(GLfloat));

	//make index buffer
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLuint indexData[] = {
		// face 0:
		0,1,2,      // first triangle
		2,1,3,      // second triangle
		// face 1:
		4,5,6,      // first triangle
		6,5,7,      // second triangle
		// face 2:
		8,9,10,     // first triangle
		10,9,11,    // second triangle
		// face 3:
		12,13,14,   // first triangle
		14,13,15,   // second triangle
		// face 4:
		16,17,18,   // first triangle
		18,17,19,   // second triangle
		// face 5:
		20,21,22,   // first triangle
		22,21,23,   // second triangle
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6 * 6, indexData, GL_STATIC_DRAW);
}


void loadShadersFromFile(GLuint& fullShader, GLuint& vertShader, GLuint& fragShader)
{
	//			VERTEX
	ifstream vertexStream("testvertex.glsl");
	string vertex;
	vertex.assign((istreambuf_iterator<char>(vertexStream)), (std::istreambuf_iterator<char>()));

	//now load this shader into OpenGL
	const char *vertSource = vertex.c_str(); //turn source from string (a class), to an array of chars (a pointer)
	int length = vertex.size();

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, &length);
	glCompileShader(vertShader);

	//check the compilation
	if(!check_shader_compile_status(vertShader))
	{
		glfwTerminate();
		exit(1);
	}


	//			FRAGMENT
	ifstream fragmentStream("testfragment.glsl");
	string fragment;
	fragment.assign((istreambuf_iterator<char>(fragmentStream)), (std::istreambuf_iterator<char>()));

	//now load this shader into OpenGL
	const char *fragSource = fragment.c_str(); //turn source from string (a class), to an array of chars (a pointer)
	length = fragment.size();

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, &length);
	glCompileShader(fragShader);

	//check the compilation
	if(!check_shader_compile_status(fragShader))
	{
		glfwTerminate();
		exit(1);
	}


	//			COMBINED
	// create program
	fullShader = glCreateProgram();

	// attach shaders
	glAttachShader(fullShader, vertShader);
	glAttachShader(fullShader, fragShader);

	// link the program and check for errors
	glLinkProgram(fullShader);
	check_program_link_status(fullShader);
}

//binds chessboard texture to GL context
void textureLoader()
{
	//setup handle
	GLuint chess;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &chess);
	glBindTexture(GL_TEXTURE_2D, chess);

	checkError("Texture Bind GL Error: ");

	//set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	checkError("Texture Filter GL Error: ");

	//get data
	GLubyte* imageData = makeCheckerboard(8);

	checkError("Loader GL Error: ");

	//apply to texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	checkError("Texture Application GL Error: ");
}

int main()
{
	//make OS window for rendering
	GLFWwindow *window;
	glfwWindowLoader(window);

	glewExperimental = GL_TRUE;
	glewInit();

	//load shaders
	GLuint shader, vertex, fragment;
	loadShadersFromFile(shader, vertex, fragment);
	GLint projectionLocation = glGetUniformLocation(shader, "transformMatrix");
	GLint lightDirectionLocation = glGetUniformLocation(shader, "lightDir");
	GLint texLocation = glGetUniformLocation(shader, "tex");
	glUseProgram(shader);

	checkError("Shader GL Error (External): ");

	//make buffers
	GLuint vertexArray, vertexBuffer, indexBuffer;
	makeCubeVBO(vertexArray, vertexBuffer, indexBuffer);

	checkError("VBO GL Error: ");

	//load textures
	textureLoader();

	//set static uniforms
	glUniform3f(lightDirectionLocation, -5.0f, -3.0f, -5.0f);
	glUniform1i(texLocation, 0);

	//begin render loop
	glEnable(GL_DEPTH_TEST);

	checkError("Uniform GL Error: ");

	while(!glfwWindowShouldClose(window))
	{
		//all window operations
		glfwPollEvents();

		float t = glfwGetTime();

		//clear framebuffer
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// calculate ViewProjection matrix
		glm::mat4 Projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.f);

		// translate the world/view position
		glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

		// make the camera rotate around the origin
		View = glm::rotate(View, 2.0f * t, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 ViewProjection = Projection*View;

		// set the uniform
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(ViewProjection));

		// bind the vao
		glBindVertexArray(vertexArray);

		// draw
		glDrawElements(GL_TRIANGLES, 6*6, GL_UNSIGNED_INT, 0);

		checkError("Frame GL Error: ");

		glfwSwapBuffers(window);
	}
}

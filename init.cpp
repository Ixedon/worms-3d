
#include "init.hpp"

//Freeing of resources
void freeOpenGLProgram() {
	delete shaderProgram; //Delete shader program

	glDeleteVertexArrays(1,&vao); //Delete VAO
	//Delete VBOs
	glDeleteBuffers(1,&bufVertices);
	glDeleteBuffers(1,&bufColors);
	glDeleteBuffers(1,&bufNormals);


}


void zeby_wersje_stykaly()
{
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

//Window resize event processing procedure
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Window coordinates
    if (height!=0) {
        aspect=(float)width/(float)height; //Compute window size aspect ratio
    } else {
        aspect=1;
    }
}

//Error handling procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Key event processing procedure
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_y = -3.14;
		if (key == GLFW_KEY_RIGHT) speed_y = 3.14;
		if (key == GLFW_KEY_UP) speed_x = -3.14;
		if (key == GLFW_KEY_DOWN) speed_x = 3.14;
	}


	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
	}
}


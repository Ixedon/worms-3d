/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define GLM_FORCE_RADIANS
const float PI = 3.141592653589793f;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "include/shaderprogram.h"
#include "include/objloader.hpp"
#include "include/texture.hpp"

using namespace glm;




float speed_x = 0; // [radians/s]
float speed_y = 0; // [radians/s]
float dist,dist2;

float aspect=1; //Ratio of width to height

//Shader program object
ShaderProgram *shaderProgram;

//VAO and VBO handles
GLuint vao;
GLuint bufVertices; //handle for VBO buffer which stores vertex coordinates
GLuint bufUVs;
GLuint bufColors;  //handle for VBO buffer which stores vertex colors
GLuint bufNormals; //handle for VBO buffer which stores vertex normals
GLuint Texture;
GLuint Texture_cr;
GLuint TextureID;
GLuint TextureID_cr;
// //Cube
// float* vertices=Models::CubeInternal::vertices;
// float* colors=Models::CubeInternal::colors;
// float* normals=Models::CubeInternal::normals;


 // Read our .obj file
 std::vector<glm::vec3> vertices;
 std::vector<glm::vec2> uvs;
 std::vector<glm::vec3> normals; // Won't be used at the moment.

//Teapot
/*float* vertices=Models::TeapotInternal::vertices;
float* colors=Models::TeapotInternal::colors;
float* normals=Models::TeapotInternal::normals;
int vertexCount=Models::TeapotInternal::vertexCount;*/




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

//Window resize event processing procedure
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Window coordinates
    if (height!=0) {
        aspect=(float)width/(float)height; //Compute window size aspect ratio
    } else {
        aspect=1;
    }
}


void prepareObject(ShaderProgram*);


//Initialization procedure
void initOpenGLProgram(GLFWwindow* window) {
	//************Insert initialization code here************
	glClearColor(0, 0, 0, 1); //Clear the screen to black
	glEnable(GL_DEPTH_TEST); //Turn on Z-Buffer
	glEnable(GL_TEXTURE_2D);
	glfwSetKeyCallback(window, key_callback); //Register key event processing procedure
    glfwSetFramebufferSizeCallback(window,windowResize);

	shaderProgram=new ShaderProgram("vshader.txt",NULL,"fshader.txt"); //Read, compile and link the shader program
    shaderProgram->use();            //wazne ze tutaj
	// Load the texture
  	//Texture = loadBMP_custom("texture/pocisk2.bmp");   //for pocisk
  	//Texture = loadBMP_custom("texture/worms.bmp");     //for worms
  	Texture = loadBMP_custom("texture/desert.bmp");     //for desert
    

    Texture_cr = loadBMP_custom("texture/colorramp-bw.bmp");     //color ramp


    // Get a handle for our "myTextureSampler" uniform
    TextureID = shaderProgram->getUniformLocation("myTextureSampler");
    TextureID_cr = shaderProgram->getUniformLocation("ColorRamp");

    //bool res = loadOBJ("models/pocisk2.obj", vertices, uvs, normals);        //smooth model (modif 1)
    //bool res = loadOBJ("models/pocisk2-flat.obj", vertices, uvs, normals);  //flat model  (modif 1)
    //bool res = loadOBJ("models/pocisk2-hd.obj", vertices, uvs, normals);        //smooth hd model (modif 3)
    //bool res = loadOBJ("models/pocisk2-hda.obj", vertices, uvs, normals);        //flat hd model (modif 3)
    //bool res = loadOBJ("models/pocisk2-shd.obj", vertices, uvs, normals);        //super hd model (modif 5)

    //bool res = loadOBJ("texture/worms-2.obj", vertices, uvs, normals);        //worms model

     bool res = loadOBJ("models/desert-shd.obj", vertices, uvs, normals);        //desert model
    //dist = -3.0f;    //for worm
   // dist = -10.0f;  //for pocisk
    dist2 = 0.0f;
    dist = -10.0f; dist2 = 50.0f; //for desert

	prepareObject(shaderProgram);

}

//Creates a VBO buffer from an array
GLuint makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1,&handle);//Generate handle for VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER,handle);  //Active the handle
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Copy the array to VBO

	return handle;
}

//Assigns VBO buffer handle to an attribute of a given name
void assignVBOtoAttribute(ShaderProgram *shaderProgram,const char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location=shaderProgram->getAttribLocation(attributeName); //Get slot number for the attribute
	glBindBuffer(GL_ARRAY_BUFFER,bufVBO);  //Activate VBO handle
	glEnableVertexAttribArray(location); //Turn on using of an attribute of a number passed as an argument
	glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, NULL); //Data for the slot should be taken from the current VBO buffer
}




//Preparation for drawing of a single object
void prepareObject(ShaderProgram* shaderProgram) {





	//Build VBO buffers with object data
	bufVertices=makeBuffer(&vertices[0], vertices.size(), sizeof(glm::vec3)); //VBO with vertex coordinates
	bufUVs=makeBuffer(&uvs[0], uvs.size(), sizeof(glm::vec2)); //VBO with texture coordiantes
	//bufColors=makeBuffer(&uvs, uvs.size() , sizeof(glm::vec2));//VBO with vertes colors
	bufNormals=makeBuffer(&normals[0], normals.size(), sizeof(glm::vec3));//VBO with vertex normals

	//Create VAO which associates VBO with attributes in shading program
	glGenVertexArrays(1,&vao); //Generate VAO handle and store it in the global variable

	glBindVertexArray(vao); //Activate newly created VAO

	assignVBOtoAttribute(shaderProgram,"vertex",bufVertices,3); //"vertex" refers to the declaration "in vec4 vertex;" in vertex shader
	assignVBOtoAttribute(shaderProgram,"vertexUV",bufUVs,2); //"UV" refers to the declaration "in vec4 UV;" in vertex shader
	//assignVBOtoAttribute(shaderProgram,"color",bufColors,4); //"color" refers to the declaration "in vec4 color;" in vertex shader
	assignVBOtoAttribute(shaderProgram,"normal",bufNormals,3); //"normal" refers to the declaration "in vec4 normal;" w vertex shader


    //glEnable(GL_TEXTURE_2D);
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);


    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, Texture_cr);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID_cr, 1);
    //glEnable(GL_TEXTURE_2D);

	glBindVertexArray(0); //Deactivate VAO
}



void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM) {
	//Turn on the shading program that will be used for drawing.
	//While in this program it would be perfectly correct to execute this once in the initOpenGLProgram,
	//in most cases more than one shading program is used and hence, it should be switched between drawing of objects
	//while we render a single scene.
	//shaderProgram->use();

	//Set uniform variables P,V and M in the vertex shader by assigning the appropriate matrices
	//In the lines below, expression:
	//  shaderProgram->getUniformLocation("P")
	//Retrieves the slot number corresponding to a uniform variable of a given name.
	//WARNING! "P" in the instruction above corresponds to the declaration "uniform mat4 P;" in the vertex shader,
	//while mP in glm::value_ptr(mP) corresponds to the argument "mat4 mP;" in THIS file.
	//The whole line below copies data from variable mP to the uniform variable P in the vertex shader. The rest of the instructions work similarly.
	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));

	//Activation of VAO and therefore making all associations of VBOs and attributes current
	glBindVertexArray(vao);

	//Drawing of an object
	glDrawArrays(GL_TRIANGLES,0,vertices.size());

	//Tidying up after ourselves (not needed if we use VAO for every object)
	glBindVertexArray(0);
}

//Procedure which draws the scene
void drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	//************Place the drawing code here******************l

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers

	//glm::mat4 P = glm::perspective(50 * PI / 180,aspect, 1.0f, 50.0f); //Compute projection matrix
	glm::mat4 P = glm::perspective(50 * PI / 180,aspect, 1.0f, 100.0f); //ostatni parametr - odleglosc renderowania

	glm::mat4 V = glm::lookAt( //Compute view matrix
		glm::vec3(0.0f, dist2, dist),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Compute model matrix
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_x, glm::vec3(1, 0, 0));
	M = glm::rotate(M, angle_y, glm::vec3(0, 1, 0));

	//Draw object
	drawObject(vao,shaderProgram,P,V,M);

	//Swap front and back buffers
	glfwSwapBuffers(window);

}





//Freeing of resources
void freeOpenGLProgram() {
	delete shaderProgram; //Delete shader program

	glDeleteVertexArrays(1,&vao); //Delete VAO
	//Delete VBOs
	glDeleteBuffers(1,&bufVertices);
	glDeleteBuffers(1,&bufColors);
	glDeleteBuffers(1,&bufNormals);


}


void zeby_ten_glupi_opengl_w_koncu_zaczal_u_mnie_dzialac_siedzialem_nad_tym_4_godziny_z_50_tabami_w_przegladarce_niech_ogarna_w_te_wersje_po_ludzku()
{
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}


int main(void)
{


	GLFWwindow* window; //Pointer to window object

	glfwSetErrorCallback(error_callback);//Register error callback procedure

	if (!glfwInit()) { //Initialize GLFW procedure
		fprintf(stderr, "Can't initialize GLFW GLFW.\n");
		exit(EXIT_FAILURE);
	}


	zeby_ten_glupi_opengl_w_koncu_zaczal_u_mnie_dzialac_siedzialem_nad_tym_4_godziny_z_50_tabami_w_przegladarce_niech_ogarna_w_te_wersje_po_ludzku();


	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Create 500x500 window with "OpenGL" as well as OpenGL context.

	if (!window) //If window could not be created, then end the program
	{
		fprintf(stderr, "Can't create window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Since this moment, the window context is active and OpenGL commands will work with it.
	glfwSwapInterval(1); //Synchronize with the first VBLANK signal

	if (glewInit() != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW.\n");
		exit(EXIT_FAILURE);
	}



	initOpenGLProgram(window); //Initialization procedure

	float angle_x = 0; //Object rotation angle
	float angle_y = 0; //Object rotation angle

	glfwSetTime(0); //Zero time counter

	//Main loop
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) //As long as window shouldnt be closed...
	{
		angle_x += speed_x*glfwGetTime(); //Increase angle by the angle speed times the time passed since the previous frame
		angle_y += speed_y*glfwGetTime(); //Increase angle by the angle speed times the time passed since the previous frame
		glfwSetTime(0); //Zero time counter
		drawScene(window,angle_x,angle_y); //Execute drawing procedure
		glfwPollEvents(); //Execute callback procedures which process events
	}

	freeOpenGLProgram(); //Free resources

	glfwDestroyWindow(window); //Delete OpenGL context and window
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}

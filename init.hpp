//////////////////////biblioteki/////////////////////
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


/////////////////////zmienne/////////////////

//////externy pozwalaja na dzielenie zmiennych miedzy plikami


extern float aspect; //Ratio of width to height
extern float speed_x; // [radians/s]
extern float speed_y; // [radians/s]
//Shader program object
extern ShaderProgram *shaderProgram;

//VAO and VBO handles
extern GLuint vao;
extern GLuint bufVertices; //handle for VBO buffer which stores vertex coordinates
extern GLuint bufUVs;
extern GLuint bufColors;  //handle for VBO buffer which stores vertex colors
extern GLuint bufNormals; //handle for VBO buffer which stores vertex normals
extern GLuint Texture;
extern GLuint Texture_cr;
extern GLuint TextureID;
extern GLuint TextureID_cr;



//////////////////funkcje/////////////////

void freeOpenGLProgram();
void zeby_wersje_stykaly();
void windowResize(GLFWwindow*, int, int); 
void error_callback(int, const char*);
void key_callback(GLFWwindow* , int ,int , int , int);



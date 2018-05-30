#include "init.hpp"
#include "plansza.hpp"
#include "obiekt.hpp"



class Gra
{
public:
	Gra();
	~Gra();
	void zeby_wersje_stykaly();
	static void windowResize(GLFWwindow*, int, int); 
	static void error_callback(int, const char*);
	static void key_callback(GLFWwindow* , int ,int , int , int);
	void drawScene(GLFWwindow*, float , float);
	void initOpenGLProgram(GLFWwindow*); 
	void freeOpenGLProgram();
	void run();
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	static float aspect; //Ratio of width to height
 	static float speed_x; // [radians/s]
 	static float speed_y; // [radians/s]
	//Shader program object
 	ShaderProgram *shaderProgram;
	//VAO and VBO handles
	GLuint vao;


	Obiekt* pustynia;
	 

};
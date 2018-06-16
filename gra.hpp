#include "init.hpp"
#include "obiekt.hpp"
#include "plansza.hpp"
#include "worms.hpp"
#include "bazooka.hpp"
#include "explosion.hpp"


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

	std::vector<Obiekt*> obiekty;

};
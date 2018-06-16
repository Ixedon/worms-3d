#include "init.hpp"
#include "obiekt.hpp"
class Explosion : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu
	//Worms(GLuint);

	void load_stuff();
	void bindTextures();
	void move(glm::mat4&);

	float x,y,z;
	//vector<vec3> positions;
};
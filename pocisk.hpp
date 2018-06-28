#include "init.hpp"
#include "obiekt.hpp"
class Pocisk : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu
	//Worms(GLuint);

	void load_stuff();
	void bindTextures();
};
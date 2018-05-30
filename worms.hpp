#include "init.hpp"
#include "obiekt.hpp"
class Worms : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu

	void load_stuff();
	void bindTextures();
};
#include "init.hpp"
#include "obiekt.hpp"
class Bazooka : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu

	void load_stuff();
	void bindTextures();

};
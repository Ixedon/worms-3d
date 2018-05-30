#include "init.hpp"
#include "obiekt.hpp"
class Plansza : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu

	void load_stuff(ShaderProgram*);
	void bindTextures();
};
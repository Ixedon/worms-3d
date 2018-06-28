#include "init.hpp"
#include "obiekt.hpp"
class Plansza : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu

	void load_stuff();
	void bindTextures();
	bool czy_nad(float, float,float);
	float wysokosc(float, float);
	float rozklad(float, float, float, float, float, float);
};
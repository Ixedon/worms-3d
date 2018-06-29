#include "init.hpp"
#include "obiekt.hpp"
class Pocisk : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu
	//Worms(GLuint);

	void load_stuff();
	void bindTextures();
	int drawObject2(glm::mat4, glm::mat4, glm::mat4);

	std::vector<float> ttl;
	const unsigned long long maxttl = 100;
};
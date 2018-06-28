#include "init.hpp"
#include "obiekt.hpp"
class Explosion : public Obiekt
{	
public:
	using Obiekt::Obiekt;   //uzycie konstruktora obiektu
	//Worms(GLuint);

	void load_stuff();
	void bindTextures();

	void Create();
	void drawObject(glm::mat4, glm::mat4, glm::mat4);
	void create_shaderProgram();


	//unsigned long long time;
	std::vector<float> ttl;
	const unsigned long long maxttl = 100;
	int ilosc = 0;

	GLuint Texture2;
	GLuint TextureID2;
 	

};
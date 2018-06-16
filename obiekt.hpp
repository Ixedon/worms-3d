#ifndef OBIEKT_H
#define OBIEKT_H


#include "init.hpp"
class Obiekt
{
public:
	explicit Obiekt(GLuint);
	virtual ~Obiekt();

	
	GLuint makeBuffer(void*, int , int );
	void updateBuffer(GLuint, void*, int , int , int);
	void assignVBOtoAttribute(const char*, GLuint, int, bool);
	void prepareObject();
	
	void Destroy();
	virtual void Create();
	virtual void create_shaderProgram();
	
	virtual void bindTextures()=0;        //funckja czysto wirtualna
	virtual void load_stuff()=0;
	virtual void move(glm::mat4&){}        //mozliwosc nadpisania w konkretnych obiektach
	virtual void drawObject(glm::mat4, glm::mat4, glm::mat4);

////////////////////////////////////
	GLuint vao;
	GLuint Texture;
	GLuint TextureID;
	GLuint bufVertices; //handle for VBO buffer which stores vertex coordinates
	GLuint bufUVs;
	GLuint bufColors;  //handle for VBO buffer which stores vertex colors
	GLuint bufNormals; //handle for VBO buffer which stores vertex normals
	GLuint bufM;

	 // Read our .obj file
 	std::vector<glm::vec3> vertices;
 	std::vector<glm::vec2> uvs;
 	std::vector<glm::vec3> normals; 

 	GLuint id;
 	ShaderProgram* shaderProgram;

 	std::vector<mat4> M;    //macierz M poszczegolnych instancji (sama sie aktualizuje na podstawie ponizych vectorow)
 	std::vector<vec3> pos;  //pozycje poszczegolnych instancji
 	std::vector<vec3> rot;  //rotacje poszczegolnych instancji
 	std::vector<vec3> sca;  //skala poszczegolnych instancji

 	int maxInstances;
};


#endif

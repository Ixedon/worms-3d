#ifndef OBIEKT_H
#define OBIEKT_H


#include "init.hpp"
class Obiekt
{
public:
	explicit Obiekt(GLuint);
	virtual ~Obiekt();

	
	GLuint makeBuffer(void*, int , int );
	void assignVBOtoAttribute(const char*, GLuint, int);
	void prepareObject();
	void drawObject(glm::mat4, glm::mat4, glm::mat4);
	void Destroy();
	void create_shaderProgram();
	
	virtual void bindTextures()=0;
	virtual void load_stuff()=0;

////////////////////////////////////
	GLuint vao;
	GLuint Texture;
	GLuint TextureID;
	GLuint bufVertices; //handle for VBO buffer which stores vertex coordinates
	GLuint bufUVs;
	GLuint bufColors;  //handle for VBO buffer which stores vertex colors
	GLuint bufNormals; //handle for VBO buffer which stores vertex normals

	 // Read our .obj file
 	std::vector<glm::vec3> vertices;
 	std::vector<glm::vec2> uvs;
 	std::vector<glm::vec3> normals; 

 	GLuint id;
 	ShaderProgram* shaderProgram;

};


#endif

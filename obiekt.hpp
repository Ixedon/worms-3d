#ifndef OBIEKT_H
#define OBIEKT_H


#include "init.hpp"
class Obiekt
{
public:
	explicit Obiekt(GLuint);
	virtual ~Obiekt();

	
	GLuint makeBuffer(void*, int , int );
	void assignVBOtoAttribute(ShaderProgram*,const char*, GLuint, int);
	void prepareObject(ShaderProgram*);
	void drawObject(ShaderProgram*, mat4, mat4, mat4);
	void Destroy();
	
	virtual void bindTextures(){}
	virtual void load_stuff(ShaderProgram*){}

////////////////////////////////////
	GLuint vao;
	GLuint Texture;
	GLuint Texture_cr;
	GLuint TextureID;
	GLuint TextureID_cr;
	GLuint bufVertices; //handle for VBO buffer which stores vertex coordinates
	GLuint bufUVs;
	GLuint bufColors;  //handle for VBO buffer which stores vertex colors
	GLuint bufNormals; //handle for VBO buffer which stores vertex normals

	 // Read our .obj file
 	std::vector<glm::vec3> vertices;
 	std::vector<glm::vec2> uvs;
 	std::vector<glm::vec3> normals; 

 	GLuint id;

};


#endif

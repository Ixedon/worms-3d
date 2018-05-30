#include "init.hpp"
class Plansza
{
public:
	Plansza(GLuint*);
	~Plansza();

	void load_stuff(ShaderProgram*);
	GLuint makeBuffer(void*, int , int );
	void assignVBOtoAttribute(ShaderProgram*,const char*, GLuint, int);
	void prepareObject(ShaderProgram*);
	void drawObject(GLuint, ShaderProgram*, mat4, mat4, mat4);


////////////////////////////////////
	GLuint* vao;
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

};
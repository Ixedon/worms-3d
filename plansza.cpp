#include "plansza.hpp"


Plansza::Plansza (GLuint* v)
{
	vao = v;
}


void Plansza::load_stuff(ShaderProgram *shaderProgram)
{
	Texture = loadBMP_custom("texture/desert.bmp");     //for desert
	Texture_cr = loadBMP_custom("texture/colorramp-bw.bmp");     //color ramp
	TextureID = shaderProgram->getUniformLocation("myTextureSampler");
    TextureID_cr = shaderProgram->getUniformLocation("ColorRamp");
    bool res = loadOBJ("models/desert-shd.obj", vertices, uvs, normals);        //desert model
}

Plansza::~Plansza() {
	//Delete VBOs
	glDeleteBuffers(1,&bufVertices);
	glDeleteBuffers(1,&bufColors);
	glDeleteBuffers(1,&bufNormals);
}



//Creates a VBO buffer from an array
GLuint Plansza::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1,&handle);//Generate handle for VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER,handle);  //Active the handle
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Copy the array to VBO

	return handle;
}

//Assigns VBO buffer handle to an attribute of a given name
void Plansza::assignVBOtoAttribute(ShaderProgram *shaderProgram,const char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location=shaderProgram->getAttribLocation(attributeName); //Get slot number for the attribute
	glBindBuffer(GL_ARRAY_BUFFER,bufVBO);  //Activate VBO handle
	glEnableVertexAttribArray(location); //Turn on using of an attribute of a number passed as an argument
	glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, NULL); //Data for the slot should be taken from the current VBO buffer
}




//Preparation for drawing of a single object
void Plansza::prepareObject(ShaderProgram* shaderProgram) {



	//Build VBO buffers with object data
	bufVertices=makeBuffer(&vertices[0], vertices.size(), sizeof(glm::vec3)); //VBO with vertex coordinates
	bufUVs=makeBuffer(&uvs[0], uvs.size(), sizeof(glm::vec2)); //VBO with texture coordiantes
	//bufColors=makeBuffer(&uvs, uvs.size() , sizeof(glm::vec2));//VBO with vertes colors
	bufNormals=makeBuffer(&normals[0], normals.size(), sizeof(glm::vec3));//VBO with vertex normals

	//Create VAO which associates VBO with attributes in shading program
	glGenVertexArrays(1,vao); //Generate VAO handle and store it in the global variable

	glBindVertexArray(*vao); //Activate newly created VAO

	assignVBOtoAttribute(shaderProgram,"vertex",bufVertices,3); //"vertex" refers to the declaration "in vec4 vertex;" in vertex shader
	assignVBOtoAttribute(shaderProgram,"vertexUV",bufUVs,2); //"UV" refers to the declaration "in vec4 UV;" in vertex shader
	assignVBOtoAttribute(shaderProgram,"normal",bufNormals,3); //"normal" refers to the declaration "in vec4 normal;" w vertex shader

	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);


    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, Texture_cr);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID_cr, 1);
    //glEnable(GL_TEXTURE_2D);

	glBindVertexArray(0); //Deactivate VAO
}



void Plansza::drawObject(GLuint fvao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM) {
	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));

	//Activation of VAO and therefore making all associations of VBOs and attributes current
	glBindVertexArray(fvao);

	//Drawing of an object
	glDrawArrays(GL_TRIANGLES,0,vertices.size());

	//Tidying up after ourselves (not needed if we use VAO for every object)
	glBindVertexArray(0);
}
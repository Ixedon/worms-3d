#include "obiekt.hpp"

Obiekt::Obiekt(GLuint ident)
{
	id = ident;
	maxInstances = 10;
}

Obiekt::~Obiekt()
{
	Destroy();
}


void Obiekt::Create()
{
	M.push_back(mat4(1.0f));
	pos.push_back(vec3(0.0f,0.0f,0.0f));
	rot.push_back(vec3(0.0f,0.0f,0.0f));
	sca.push_back(vec3(1.0f,1.0f,1.0f));

	// M.push_back(mat4(1.0f));
	// pos.push_back(vec3(0.0f,1.0f,0.0f));
	// rot.push_back(vec3(1.0f,1.0f,0.0f));


	create_shaderProgram();
    load_stuff();
	prepareObject();
}


void Obiekt::Destroy()
{
	delete shaderProgram; //Delete shader program
		//Delete VBOs
	glDeleteBuffers(1,&bufVertices);
	glDeleteBuffers(1,&bufColors);
	glDeleteBuffers(1,&bufNormals);

	glDeleteVertexArrays(1,&vao); //Delete VAO
}




//Creates a VBO buffer from an array
GLuint Obiekt::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1,&handle);//Generate handle for VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER,handle);  //Active the handle
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Copy the array to VBO
	//glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_DYNAMIC_DRAW);//Copy the array to VBO

	return handle;
}

void Obiekt::updateBuffer(GLuint handle, void *data, int maxvertexCount, int vertexCount, int vertexSize)
{
	glBindBuffer(GL_ARRAY_BUFFER,handle);  //Active the handle
	glBufferData(GL_ARRAY_BUFFER, maxvertexCount*vertexSize, data, GL_STATIC_DRAW);//Copy the array to VBO
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount*vertexSize * 4, data);
}

//Assigns VBO buffer handle to an attribute of a given name
void Obiekt::assignVBOtoAttribute(const char* attributeName, GLuint bufVBO, int vertexSize, bool isMatrix) {
	GLuint location=shaderProgram->getAttribLocation(attributeName); //Get slot number for the attribute
	glBindBuffer(GL_ARRAY_BUFFER,bufVBO);  //Activate VBO handle
	if(isMatrix) //https://learnopengl.com/Advanced-OpenGL/Instancing
	{
		glEnableVertexAttribArray(location); //Turn on using of an attribute of a number passed as an argument
		glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 4*sizeof(vec4), (void*)0 ); //Data for the slot should be taken from the current VBO buffer
		glEnableVertexAttribArray(location + 1);
		glVertexAttribPointer(location +1 ,vertexSize,GL_FLOAT, GL_FALSE, 4*sizeof(vec4), (void*)(sizeof(vec4)) );
		glEnableVertexAttribArray(location + 2);
		glVertexAttribPointer(location +2 ,vertexSize,GL_FLOAT, GL_FALSE, 4*sizeof(vec4), (void*)(2*sizeof(vec4)) );
		glEnableVertexAttribArray(location + 3);
		glVertexAttribPointer(location +3 ,vertexSize,GL_FLOAT, GL_FALSE, 4*sizeof(vec4), (void*)(3*sizeof(vec4)) );


		glVertexAttribDivisor(location, 1);
    	glVertexAttribDivisor(location + 1, 1);
    	glVertexAttribDivisor(location + 2, 1);
    	glVertexAttribDivisor(location + 3, 1);
	}
	else
	{
		glEnableVertexAttribArray(location); //Turn on using of an attribute of a number passed as an argument
		glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, NULL); //Data for the slot should be taken from the current VBO buffer
	}
}

void Obiekt::create_shaderProgram()
{
	shaderProgram=new ShaderProgram("vshader.txt",NULL,"fshader.txt"); //Read, compile and link the shader program
}


//Preparation for drawing of a single object
void Obiekt::prepareObject() {

	//Build VBO buffers with object data
	bufVertices=makeBuffer(&vertices[0], vertices.size(), sizeof(glm::vec3)); //VBO with vertex coordinates
	bufUVs=makeBuffer(&uvs[0], uvs.size(), sizeof(glm::vec2)); //VBO with texture coordiantes
	//bufColors=makeBuffer(&uvs, uvs.size() , sizeof(glm::vec2));//VBO with vertes colors
	bufNormals=makeBuffer(&normals[0], normals.size(), sizeof(glm::vec3));//VBO with vertex normals

	bufM=makeBuffer(&M[0], maxInstances, sizeof(glm::mat4));//VBO with M matrices



	//Create VAO which associates VBO with attributes in shading program
	glGenVertexArrays(1,&vao); //Generate VAO handle and store it in the global variable
    glBindVertexArray(vao); //Activate newly created VAO
    

	assignVBOtoAttribute("vertex",bufVertices,3, 0); //"vertex" refers to the declaration "in vec4 vertex;" in vertex shader
	assignVBOtoAttribute("vertexUV",bufUVs,2, 0); //"UV" refers to the declaration "in vec4 UV;" in vertex shader
	assignVBOtoAttribute("normal",bufNormals,3, 0); //"normal" refers to the declaration "in vec4 normal;" w vertex shader

	assignVBOtoAttribute("M",bufM,4, 1); //"normal" refers to the declaration "in vec4 normal;" w vertex shader

	//bindTextures();

	glBindVertexArray(0); //Deactivate VAO
	
}



void Obiekt::drawObject(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM) {
	shaderProgram->use();            

	//move(mM);
	for (int i = 0; i < M.size(); ++i)
	{
		M[i] = mM;
		M[i] = glm::translate(M[i], pos[i]);
		M[i] = glm::rotate(M[i], rot[i][0], vec3(1, 0, 0));
		M[i] = glm::rotate(M[i], rot[i][1], vec3(0, 1, 0));
		M[i] = glm::rotate(M[i], rot[i][2], vec3(0, 0, 1));
		M[i] = glm::scale(M[i], sca[i]);
	}
	//M[1] = glm::translate(M[1], glm::vec3(1,1,1));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
	//glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));
	
	updateBuffer(bufM, &M[0], maxInstances ,M.size(),sizeof(glm::mat4));//VBO with M matrices


	//Activation of VAO and therefore making all associations of VBOs and attributes current
	glBindVertexArray(vao);

	bindTextures();    //wazne ze tutaj

	//Drawing of an object
	glDrawArraysInstanced(GL_TRIANGLES,0,vertices.size(), M.size());

	//Tidying up after ourselves (not needed if we use VAO for every object)
	glBindVertexArray(0);
}
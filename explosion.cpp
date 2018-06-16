#include "explosion.hpp"


// Worms::Worms(GLuint ident)
// {
//     id = ident;
// }

void Explosion::load_stuff()
{
	Texture = loadBMP_custom("texture/worms.bmp");     //for desert
    bool res = loadOBJ("models/worms-2.obj", vertices, uvs, normals);        //desert model

    x = 0.0f;
    y = 3.0f;
    z = 0.0f;
}


void Explosion::bindTextures()
{
    TextureID = shaderProgram->getUniformLocation("myTextureSampler");
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
}

void Explosion::move(glm::mat4& M)
{
    M = glm::translate(M, glm::vec3(x,y,z));
}


void Explosion::Create()
{
    positions.push_back(vec3(1.0,1.0,1.0));

    create_shaderProgram();
    load_stuff();
    prepareObject();
}

void Explosion::drawObject(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM)
{
    shaderProgram->use();            

    //move(mM);

    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));

    //Activation of VAO and therefore making all associations of VBOs and attributes current
    glBindVertexArray(vao);

    bindTextures();    //wazne ze tutaj

    //Drawing of an object
    glDrawArrays(GL_POINTS,0,vertices.size());

    //Tidying up after ourselves (not needed if we use VAO for every object)
    glBindVertexArray(0);
}
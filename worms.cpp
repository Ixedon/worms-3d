#include "worms.hpp"


// Worms::Worms(GLuint ident)
// {
//     id = ident;
// }

void Worms::load_stuff()
{
	Texture = loadBMP_custom("texture/worms.bmp");     //for desert
    bool res = loadOBJ("models/worms-2.obj", vertices, uvs, normals);        //desert model

    x = 0.0f;
    y = 3.0f;
    z = 0.0f;
}



void Worms::bindTextures()
{
    TextureID = shaderProgram->getUniformLocation("myTextureSampler");
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
}

void Worms::move(glm::mat4& M)
{
    M = glm::translate(M, glm::vec3(x,y,z));
}
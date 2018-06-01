#include "bazooka.hpp"

void Bazooka::load_stuff()
{
	Texture = loadBMP_custom("texture/bazooka.bmp");     //for bazooka
    bool res = loadOBJ("models/bazooka.obj", vertices, uvs, normals);        //bazooka model
}



void Bazooka::bindTextures()
{
    TextureID = shaderProgram->getUniformLocation("myTextureSampler");
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
}

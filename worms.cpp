#include "worms.hpp"


void Worms::load_stuff()
{
	Texture = loadBMP_custom("texture/worms.bmp");     //for desert
    bool res = loadOBJ("models/worms-2.obj", vertices, uvs, normals);        //desert model

    x=y=z=0.0f;
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

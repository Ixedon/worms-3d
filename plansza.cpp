#include "plansza.hpp"


void Plansza::load_stuff()
{
	Texture = loadBMP_custom("texture/desert.bmp");     //for desert
	
    bool res = loadOBJ("models/desert-math.obj", vertices, uvs, normals);        //desert model
}



void Plansza::bindTextures()
{
	TextureID = shaderProgram->getUniformLocation("myTextureSampler");
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
}

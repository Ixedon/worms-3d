#include "plansza.hpp"


void Plansza::load_stuff(ShaderProgram *shaderProgram)
{
	Texture = loadBMP_custom("texture/desert.bmp");     //for desert
	Texture_cr = loadBMP_custom("texture/colorramp-bw.bmp");     //color ramp
	TextureID = shaderProgram->getUniformLocation("myTextureSampler");
    TextureID_cr = shaderProgram->getUniformLocation("ColorRamp");
    bool res = loadOBJ("models/desert-shd.obj", vertices, uvs, normals);        //desert model
}



void Plansza::bindTextures()
{
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
}

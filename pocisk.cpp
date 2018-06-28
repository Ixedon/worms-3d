#include "pocisk.hpp"

void Pocisk::load_stuff()
{
	Texture = loadBMP_custom("texture/pocisk2.bmp");     //for desert
    bool res = loadOBJ("models/pocisk2.obj", vertices, uvs, normals);        //desert model

    M.clear();
    //sca[0] = vec3(0.2f, 0.2f, 0.2f);  //usatwienie poczatkowej pozycji wormsa o indeksie 0
}



void Pocisk::bindTextures()
{
    TextureID = shaderProgram->getUniformLocation("myTextureSampler");
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
}

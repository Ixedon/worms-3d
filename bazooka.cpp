#include "bazooka.hpp"

void Bazooka::load_stuff()
{
	Texture = loadBMP_custom("texture/bazooka.bmp");     //for bazooka
    bool res = loadOBJ("models/bazooka.obj", vertices, uvs, normals);        //bazooka model
    pos[0] = vec3(0.0f, 0.5f, 0.7f);  //usatwienie poczatkowej pozycji wormsa o indeksie 0
    rot[0] = vec3(0.0f, 0.0f, 0.0f);
    sca[0] = vec3(-0.2f, 0.2f, 0.2f);

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

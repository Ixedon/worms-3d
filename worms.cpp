#include "worms.hpp"


// Worms::Worms(GLuint ident)
// {
//     id = ident;
// }

void Worms::load_stuff()
{
	Texture = loadBMP_custom("texture/worms.bmp");     //for desert
    bool res = loadOBJ("models/worms-2.obj", vertices, uvs, normals);        //desert model


    pos[0] = vec3(0.0f, 3.0f, 0.0f);  //usatwienie poczatkowej pozycji wormsa o indeksie 0
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

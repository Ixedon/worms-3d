#include "pocisk.hpp"

void Pocisk::load_stuff()
{
	Texture = loadBMP_custom("texture/pocisk2.bmp");     //for desert
    bool res = loadOBJ("models/pocisk2.obj", vertices, uvs, normals);        //desert model

    M.clear();
    pos.clear();
    rot.clear();
    sca.clear();
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


int Pocisk::drawObject2(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM)
{

    shaderProgram->use();      
    int ktory = 10000;      

    //if(M.size()==ilosc)M.clear();

    for (int i = 0; i < M.size(); ++i)
    {
        if(ttl[i]>0) 
        {
                ttl[i]--;

        		pos[i] = pos[i]+vec3(0.1f,0.0f,0.0f);

        }
        else {if(pos[i]!=vec3(1000,1000,0))ktory = i; pos[i]=vec3(1000,1000,0);}

    }

    for (int i = 0; i < M.size(); ++i)
	{
		M[i] = mM;
		M[i] = glm::rotate(M[i], rot[i][0], vec3(1, 0, 0));
		M[i] = glm::rotate(M[i], rot[i][1], vec3(0, 1, 0));
		M[i] = glm::rotate(M[i], rot[i][2], vec3(0, 0, 1));
		M[i] = glm::translate(M[i], pos[i]);
		M[i] = glm::scale(M[i], sca[i]);
	}


    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    //glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));
    
    updateBuffer(bufM, &M[0], maxInstances ,M.size(),sizeof(glm::mat4));//VBO with M matrices
    //updateBuffer(bufM, &M[0], maxInstances ,M.size(),sizeof(glm::mat4));//VBO with M matrices


    //Activation of VAO and therefore making all associations of VBOs and attributes current
    glBindVertexArray(vao);

    bindTextures();    //wazne ze tutaj

    //Drawing of an object
    //glPointSize(20);

    //glDrawArraysInstanced(GL_POINTS,0, vertices.size(), M.size());
    glDrawArraysInstanced(GL_TRIANGLES,0, vertices.size(), M.size());

    //Tidying up after ourselves (not needed if we use VAO for every object)
    glBindVertexArray(0);


    return ktory;
 }
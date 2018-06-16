#include "explosion.hpp"


// Worms::Worms(GLuint ident)
// {
//     id = ident;
// }

void Explosion::load_stuff()
{
	Texture = loadBMP_custom("texture/explosion.bmp");     //for desert
    vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
    uvs.push_back(vec2(0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 1.0f, 1.0f));

    maxInstances = 100000;

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


void Explosion::create_shaderProgram()
{
    shaderProgram=new ShaderProgram("vshader-par.txt",NULL,"fshader-par.txt"); //Read, compile and link the shader program
}


void Explosion::Create()
{

    for (int i = 0; i < 1000; ++i)
    {
        M.push_back(mat4(1.0f));
        pos.push_back(vec3(0,0,0));
        rot.push_back(vec3(0.0f,0.0f,0.0f));
        sca.push_back(vec3(1.0f,1.0f,1.0f));
        ttl.push_back(maxttl);
    }
    
    time = 0;

    create_shaderProgram();
    load_stuff();
    prepareObject();
}

void Explosion::drawObject(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM)
{
    shaderProgram->use();            



    for (int i = 0; i < M.size(); ++i)
    {
        if(ttl[i]>0) 
        {
            if(rand()%3 == 0)
            {
                pos[i] = vec3((maxttl - --ttl[i])/5.0f * cos(i*2*PI/float(M.size())),
                                      (maxttl - ttl[i])/5.0f * sin(i*2*PI/float(M.size())),
                                      0
                                      );
                //sca[i]=vec3(ttl[i],ttl[i],ttl[i]);
            }
        }
        else pos[i]=vec3(0,0,0);


        M[i] = mM;
        M[i] = glm::translate(M[i], pos[i]);
        M[i] = glm::rotate(M[i], rot[i][0], vec3(1, 0, 0));
        M[i] = glm::rotate(M[i], rot[i][1], vec3(0, 1, 0));
        M[i] = glm::rotate(M[i], rot[i][2], vec3(0, 0, 1));
        M[i] = glm::scale(M[i], sca[i]);
    }

    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    //glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));
    
    updateBuffer(bufM, &M[0], maxInstances ,M.size(),sizeof(glm::mat4));//VBO with M matrices


    //Activation of VAO and therefore making all associations of VBOs and attributes current
    glBindVertexArray(vao);

    bindTextures();    //wazne ze tutaj

    //Drawing of an object
    glPointSize(10);

    glDrawArraysInstanced(GL_POINTS,0, vertices.size(), M.size());
    //glDrawArraysInstanced(GL_TRIANGLES,0, vertices.size(), M.size());

    //Tidying up after ourselves (not needed if we use VAO for every object)
    glBindVertexArray(0);
}
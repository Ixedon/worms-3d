#include "explosion.hpp"


// Worms::Worms(GLuint ident)
// {
//     id = ident;
// }

void Explosion::load_stuff()
{
	Texture = loadBMP_custom("texture/explosion.bmp");     //for desert
    //bool res = loadOBJ("models/worms-2.obj", vertices, uvs, normals);        //desert model
    //bool res = loadOBJ("models/point.obj", vertices, uvs, normals);        //desert model
    vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
    uvs.push_back(vec2(0.0f, 0.0f));
    normals.push_back(vec3(1.0f, 1.0f, 1.0f));

    //vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    //vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    //vertices.push_back(vec3(-0.5f, 0.5f, 0.0f));
    //vertices.push_back(vec3(0.5f, 0.5f, 0.0f));

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
    shaderProgram=new ShaderProgram("vshader.txt",NULL,"fshader-par.txt"); //Read, compile and link the shader program
}


void Explosion::Create()
{

    for (int i = 0; i < 1; ++i)
    {
        M.push_back(mat4(1.0f));
        pos.push_back(vec3(i,i,i));
        rot.push_back(vec3(90.0f,0.0f,0.0f));
    }
    


    create_shaderProgram();
    load_stuff();
    prepareObject();
}

void Explosion::drawObject(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM)
{
    shaderProgram->use();            

    //move(mM);
    for (int i = 0; i < M.size(); ++i)
    {
        M[i] = mM;
        M[i] = glm::translate(M[i], pos[i]);
        M[i] = glm::rotate(M[i], rot[i][0], vec3(1, 0, 0));
        M[i] = glm::rotate(M[i], rot[i][1], vec3(0, 1, 0));
        M[i] = glm::rotate(M[i], rot[i][2], vec3(0, 0, 1));
    }
    //M[1] = glm::translate(M[1], glm::vec3(1,1,1));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    //glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));
    
    updateBuffer(bufM, &M[0], maxInstances ,M.size(),sizeof(glm::mat4));//VBO with M matrices


    //Activation of VAO and therefore making all associations of VBOs and attributes current
    glBindVertexArray(vao);

    bindTextures();    //wazne ze tutaj

    //Drawing of an object
    glPointSize(30);
    glDrawArraysInstanced(GL_POINTS,0, vertices.size(), M.size());
    //glDrawArraysInstanced(GL_TRIANGLES,0, vertices.size(), M.size());

    //Tidying up after ourselves (not needed if we use VAO for every object)
    glBindVertexArray(0);
}
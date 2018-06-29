#include "explosion.hpp"


// Worms::Worms(GLuint ident)
// {
//     id = ident;
// }

void Explosion::load_stuff()
{
	Texture = loadBMP_custom("texture/explosion.bmp");     //for desert
    Texture2 = loadBMP_custom("texture/smoke.bmp");     //for desert
    //vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
    float ps = 0.5f;
    float ps2 = 2* ps;

    // vertices.push_back(vec3(-ps, -ps, 0.0f));    
    // vertices.push_back(vec3(ps, -ps, 0.0f));
    // vertices.push_back(vec3(-ps, ps, 0.0f));


    // vertices.push_back(vec3(ps, -ps, 0.0f));
    // vertices.push_back(vec3(-ps, ps, 0.0f));    
    
    // vertices.push_back(vec3( ps, ps, 0.0f));


    vertices.push_back(vec3( -ps, ps2, 0.0f));
    vertices.push_back(vec3( -ps2, ps, 0.0f));
    vertices.push_back(vec3( -ps2, -ps, 0.0f));

    vertices.push_back(vec3( -ps, ps2, 0.0f));
    vertices.push_back(vec3( ps, ps2, 0.0f));
    vertices.push_back(vec3( ps2, ps, 0.0f));

    vertices.push_back(vec3( -ps, ps2, 0.0f));
    vertices.push_back(vec3( -ps2, -ps, 0.0f));
    vertices.push_back(vec3( ps, -ps2, 0.0f));

    vertices.push_back(vec3( -ps, ps2, 0.0f));
    vertices.push_back(vec3( ps2, ps, 0.0f));
    vertices.push_back(vec3( ps, -ps2, 0.0f));


    vertices.push_back(vec3( -ps2, -ps, 0.0f));
    vertices.push_back(vec3( -ps, -ps2, 0.0f));
    vertices.push_back(vec3( ps, -ps2, 0.0f));
    
    vertices.push_back(vec3( ps, -ps2, 0.0f));
    vertices.push_back(vec3( ps2, -ps, 0.0f));
    vertices.push_back(vec3( ps2, ps, 0.0f));


    uvs.push_back(vec2(0.5f, 0.5f));
    normals.push_back(vec3(1.0f, 1.0f, 1.0f));

    maxInstances = 1000;


    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    srand(time(NULL));

}


void Explosion::bindTextures()
{
    TextureID = shaderProgram->getUniformLocation("myTextureSampler");
    TextureID2 = shaderProgram->getUniformLocation("myTextureSampler2");
	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);


    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, Texture2);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID2, 1);
}


void Explosion::create_shaderProgram()
{
    shaderProgram=new ShaderProgram("vshader-par.txt",NULL,"fshader-par.txt"); //Read, compile and link the shader program
}


void Explosion::Create2(vec3 poz)
{
    M.clear();
    pos.clear();
    rot.clear();
    sca.clear();
    ttl.clear();

    for (int i = 0; i < 500; ++i)
    {
        M.push_back(mat4(1.0f));
        pos.push_back(vec3(0,0,0));
        pos_orig.push_back(poz);
        rot.push_back(vec3(0.0f,0.0f,0.0f));
        //sca.push_back(vec3(0.5f,0.5f,0.5f));
        sca.push_back(vec3(2.0f,2.0f,2.0f));
        //ttl.push_back(float(maxttl)/10*(rand()%10 +1));
        ttl.push_back(maxttl);
    }
    
   // time = 0;

    create_shaderProgram();
    load_stuff();
    prepareObject();
}

void Explosion::drawObject(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM)
{
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    shaderProgram->use();            

    if(M.size()==ilosc)M.clear();

    for (int i = 0; i < M.size(); ++i)
    {
        if(ttl[i]>0) 
        {
                ttl[i]-=(rand()%5 +1)/5;
                //ttl[i]--;
                pos[i] = pos_orig[i] + vec3((maxttl - ttl[i])/2.0f * cos(i*2*PI/float(M.size())),
                                      (maxttl - ttl[i])/2.0f * sin(i*2*PI/float(M.size())),
                                      0
                                      );
                //sca[i]=vec3(ttl[i],ttl[i],ttl[i]);
        }
        else {pos[i]=vec3(1000,1000,0);ilosc++;}


       // M[i] = mM;
        M[i] = mat4(1.0f);
        M[i] = glm::translate(M[i], pos[i]);
       // M[i] = glm::rotate(M[i], rot[i][0], vec3(1, 0, 0));
       // M[i] = glm::rotate(M[i], rot[i][1], vec3(0, 1, 0));
       // M[i] = glm::rotate(M[i], rot[i][2], vec3(0, 0, 1));
        M[i] = glm::scale(M[i], sca[i]);


    // double dArray[16] = {0.0};

    // const float *pSource = (const float*)glm::value_ptr(M[i]);
    // for (int j = 0; j < 16; ++j)
    //     {dArray[j] = pSource[j];}


    // dArray[0] = dArray[5] = dArray[10] = 1;//sqrt(dArray[0]*dArray[0] + dArray[4]*dArray[4] + dArray[8]*dArray[8]);
    // dArray[1] = dArray[2] = dArray[4] = dArray[6] = dArray[8] = dArray[9] = dArray[12] = dArray[13] = dArray[14] = 0.0f;
    // dArray[15] =1;

    // M[i]  = make_mat4(dArray);

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
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
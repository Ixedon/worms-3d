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

float Plansza::rozklad(float a, float ad, float am, float b, float bd, float bm)
{
	return(4/sqrt(2*PI*0.35*0.35)*exp(-((a*am + ad)*(a*am + ad)+(b*bm + bd)*(b*bm + bd))/(2*0.35*0.35))/2);
}


float Plansza::wysokosc(float x, float y)
{
    x=x*1.2;  //moze jest potrzebne, moze nie
    y=y*1.2;

    float z;
    z = rozklad(x,0.5,1,y,0.5,1)/1.8;
    z = z+ rozklad(x,-0.5,1,y,-0.9,1.3)/1.5;
    z = z+ rozklad(x,-0.75,1,y,1,2)/4;
    z = z- rozklad(x,0.5,0.75,y,-0.5,0.75)/5;
        
    z = z- rozklad(x,-0.1,1.5,y,0,1.5)/4;
    z = z+ rozklad(x,-0.2,1,y,0.5,1)/5;
    z = z+ rozklad(x,-0.75,1,y,1,1)/2;
    return z;
}

bool Plansza::czy_nad(float x, float y, float w)   //sprawdza czy punkt x,y,w jest nad plansza
//nie testowane, przydatne przy wykrywaniu kolizji z plansza (player controller i o)
{
    return (w>wysokosc(x,y));
}
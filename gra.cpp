#include "gra.hpp"

Gra::Gra(){Gra::grob = this;}
Gra::~Gra(){}


//inicjalizacja
float Gra::speed_x = 0;
float Gra::speed_y = 0;
float Gra::aspect=1;
Gra* Gra::grob = NULL;

Worms* worms;
Plansza* pustynia;
Pocisk* pocisk;
Bazooka* bazooka;
Explosion* explosion;

void Gra::initOpenGLProgram(GLFWwindow* window) {
	//************Insert initialization code here************
	glClearColor(0, 0, 0, 1); //Clear the screen to black
	glEnable(GL_DEPTH_TEST); //Turn on Z-Buffer
	glEnable(GL_TEXTURE_2D);
	glfwSetKeyCallback(window, Gra::key_callback); //Register key event processing procedure
	glfwSetMouseButtonCallback(window, Gra::mouse_button_callback);
    glfwSetFramebufferSizeCallback(window,windowResize);

    for (int i = 0; i < obiekty.size(); ++i)
    {
    	if(i!=4){obiekty[i]->Create();}
    	else {explosion -> Create2 (vec3(0,0,0));}
    }

}


//Freeing of resources
void Gra::freeOpenGLProgram() {

	//delete pustynia;
	for (int i = 0; i < obiekty.size(); ++i) delete obiekty[i];
}


void Gra::zeby_wersje_stykaly()
{
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

//Window resize event processing procedure
void Gra::windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Window coordinates
    if (height!=0) {
        aspect=(float)width/(float)height; //Compute window size aspect ratio
    } else {
        aspect=1;
    }
}

//Error handling procedure
void Gra::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Key event processing procedure
void Gra::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_y = -3.14;
		if (key == GLFW_KEY_RIGHT) speed_y = 3.14;
		if (key == GLFW_KEY_UP) speed_x = -3.14;
		if (key == GLFW_KEY_DOWN) speed_x = 3.14;
	}


	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
	}
}

void Gra::strzal()
{
	std::cerr << "strzel\n";
    obiekty[2]->makeInstance(vec3(1.5f,0.5f,0.7f), vec3(0.0f,0.0f,0.0f), vec3(-0.15f,0.15f,0.15f)  );
    pocisk->ttl.push_back(pocisk->maxttl);
}

void Gra::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)Gra::grob->strzal();
}



//Procedure which draws the scene
void Gra::drawScene(GLFWwindow* window, float angle_x, float angle_y) {

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers

	//glm::mat4 P = glm::perspective(50 * PI / 180,aspect, 1.0f, 50.0f); //Compute projection matrix
	glm::mat4 P = glm::perspective(50 * PI / 180,aspect, 1.0f, 400.0f); //ostatni parametr - odleglosc renderowania

	float dist = -10.0f;
	//float dist2 = 200.0f; //for desert
	//float dist2 = 50.0f; //for desert
	float dist2 = 0.0f; //for worms

	glm::mat4 V = glm::lookAt( //Compute view matrix
		glm::vec3(0.0f, dist2, dist),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Compute model matrix
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_x, glm::vec3(1, 0, 0));
	M = glm::rotate(M, angle_y, glm::vec3(0, 1, 0));

	//Draw object


	//pustynia->drawObject2(P,V,M, angle_x, angle_y);
	//for (int i = 1; i < obiekty.size(); ++i)
	for (int i = 0; i < obiekty.size(); ++i)
	{
		if(i!=2)obiekty[i]->drawObject(P,V,M);
		else
		{
			int ktory = pocisk->drawObject2(P,V,M);
			if(ktory!=10000)
			{
				//explosion -> makeInstance(pocisk ->pos[ktory], vec3(0.0f,0.0f,0.0f), vec3(1.0f) );
				explosion->Create2(pocisk ->pos[ktory]);
			}
		}
	}

	//Swap front and back buffers
	glfwSwapBuffers(window);
}

void Gra::run()
{
	worms = new Worms(0);
	pustynia = new Plansza(1);
	bazooka = new Bazooka(2);
	explosion = new Explosion(3);
	pocisk = new Pocisk(4);

	obiekty.push_back(pustynia);
	obiekty.push_back(worms);
	obiekty.push_back(pocisk);
	obiekty.push_back(bazooka);
	obiekty.push_back(explosion);
	




	GLFWwindow* window; //Pointer to window object

	glfwSetErrorCallback(error_callback);//Register error callback procedure

	if (!glfwInit()) { //Initialize GLFW procedure
		fprintf(stderr, "Can't initialize GLFW GLFW.\n");
		exit(EXIT_FAILURE);
	}


	zeby_wersje_stykaly();


	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Create 500x500 window with "OpenGL" as well as OpenGL context.

	if (!window) //If window could not be created, then end the program
	{
		fprintf(stderr, "Can't create window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Since this moment, the window context is active and OpenGL commands will work with it.
	glfwSwapInterval(1); //Synchronize with the first VBLANK signal

	if (glewInit() != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW.\n");
		exit(EXIT_FAILURE);
	}


	initOpenGLProgram(window); //Initialization procedure



	float angle_x = -0.1; //Object rotation angle
	float angle_y = 0; //Object rotation angle

	glfwSetTime(0); //Zero time counter


	//Main loop
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) //As long as window shouldnt be closed...
	{
		angle_x += speed_x*glfwGetTime(); //Increase angle by the angle speed times the time passed since the previous frame
		angle_y += speed_y*glfwGetTime(); //Increase angle by the angle speed times the time passed since the previous frame

		glfwSetTime(0); //Zero time counter
		drawScene(window,angle_x,angle_y); //Execute drawing procedure
		glfwPollEvents(); //Execute callback procedures which process events
	}

	freeOpenGLProgram(); //Free resources

	glfwDestroyWindow(window); //Delete OpenGL context and window
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}

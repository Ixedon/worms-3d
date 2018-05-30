#include "gra.hpp"

Gra::Gra(){}
Gra::~Gra(){}



float Gra::speed_x = 0;
float Gra::speed_y = 0;
float Gra::aspect=1;

void Gra::initOpenGLProgram(GLFWwindow* window) {
	//************Insert initialization code here************
	glClearColor(0, 0, 0, 1); //Clear the screen to black
	glEnable(GL_DEPTH_TEST); //Turn on Z-Buffer
	glEnable(GL_TEXTURE_2D);
	glfwSetKeyCallback(window, Gra::key_callback); //Register key event processing procedure
    glfwSetFramebufferSizeCallback(window,windowResize);

	shaderProgram=new ShaderProgram("vshader.txt",NULL,"fshader.txt"); //Read, compile and link the shader program
    shaderProgram->use();            //wazne ze tutaj

    

    for (int i = 0; i < obiekty.size(); ++i)
    {
    	obiekty[i]->load_stuff(shaderProgram);
		obiekty[i]->prepareObject(shaderProgram);
    }
    


}



//Freeing of resources
void Gra::freeOpenGLProgram() {
	delete shaderProgram; //Delete shader program
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


//Procedure which draws the scene
void Gra::drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	//************Place the drawing code here******************l

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers

	//glm::mat4 P = glm::perspective(50 * PI / 180,aspect, 1.0f, 50.0f); //Compute projection matrix
	glm::mat4 P = glm::perspective(50 * PI / 180,aspect, 1.0f, 100.0f); //ostatni parametr - odleglosc renderowania

	float dist = -10.0f; float dist2 = 50.0f; //for desert

	glm::mat4 V = glm::lookAt( //Compute view matrix
		glm::vec3(0.0f, dist2, dist),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Compute model matrix
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_x, glm::vec3(1, 0, 0));
	M = glm::rotate(M, angle_y, glm::vec3(0, 1, 0));

	//Draw object
	for (int i = 0; i < obiekty.size(); ++i)
		obiekty[i]->drawObject(shaderProgram,P,V,M);

	//Swap front and back buffers
	glfwSwapBuffers(window);
}

void Gra::run()
{
	

	Obiekt* worms = new Worms(1);
	Obiekt* pustynia = new Plansza(2);

	obiekty.push_back(pustynia);
	obiekty.push_back(worms);

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

	float angle_x = 0; //Object rotation angle
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
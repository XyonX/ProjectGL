#include<stdio.h>

#include<GL\glew.h>
#include<GLFW/glfw3.h>


const GLint WIDTH = 1280 ,HEIGHT = 720;

int main()
{
	//initialize GLFW
	if(!glfwInit())
	{
		printf("glfw initialization failed");
		glfwTerminate();
		return 1;
	}

	//SETUP WINDOW PREOPERTIES

	//OPENGL VERSION
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR ,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR ,3);
	//OPENGL PROFILE-CORE==NOT BACKWARD COMPATIBLE
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	//ALLOW FORWARD COMPATIBILITY
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);


	// Creating main window
	GLFWwindow*MainWindow = glfwCreateWindow(WIDTH,HEIGHT,"WINDOW",NULL,NULL);

	
	if(!MainWindow)
	{
		printf("glfw window creation failed");
		glfwTerminate();
		return 1;
	}

	//get buffer size information
	int BufferWidth ,BufferHeight ;
	glfwGetFramebufferSize(MainWindow,&BufferWidth,&BufferHeight);
	//set context for glfw to use
	glfwMakeContextCurrent(MainWindow);
	//allow modern extension features
	glewExperimental=GL_TRUE;
	//Initialize glew
	if(glewInit() != GLEW_OK)
	{
		printf("glew Initialization Failed ");
		glfwDestroyWindow(MainWindow);
		glfwTerminate();
	}

	//setup viewport size	//GL FUNCTION
	glViewport(0,0,BufferWidth,BufferHeight);

	//LOOP UNTIL WINDOW CLOSE
	while (!glfwWindowShouldClose(MainWindow))
	{
		//get and handle user input  events (like mouse movement resize window)
		glfwPollEvents();

		//clear window
		glClearColor(0.1f,0.6f,0.8f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(MainWindow);
	}
	
	
	
}
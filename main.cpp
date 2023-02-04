#include<stdio.h>

#include<GL\glew.h>
#include<GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


GLuint VAO , VBO, Shader ;
const GLint WIDTH = 1280 ,HEIGHT = 720;

//vertex shader source for vertex
static const char* vShader = R"(					

#version 330									
layout (location = 0) in vec3 pos ;															

void main ()									

{												
	gl_position = vec4 (pos.x,pos.y,pos.z,1.0); 										

})";

//fragment shader 
static const char* fShader = R"(

#version 330
out vec4 FragColor;   

void main()
{
	FragColor = vec4 (0.5,0.5,0.0,1.0);
})";



void CreateTriangle()
{
	// vertex for 
	GLfloat vertices[]=
		{
			-0.5,-0.5,0.0,
			0.5,-0.5,0.0,
			0.0,1.0,0.0,
		};
	//GENERATING VERTEX ARRAY OBJECT (VAO)
	// VAO holds information about how vertex data is stored in memory.
	// It stores the configuration of the vertex data and the vertex attribute pointers
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	//GENERATING VERTEX BUFFER OBJECT (VBO)
	//IT STORES VERTEX DATA
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	//THIS ONE DECLARES ABOUT THE STRUCTURE OF VERTICES
	//INDEX-if we want to use same vertex twice then we use index
	//SIZE-Size number of float we are using for one vertex ,(here,x,y,z)
	//NORMALIZED-Want to normalize or not 
	//STRIDE- number of stride , (can be rgb if want in a vertex , here ,0)
	//pointer-
	glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,0,0);
	glEnableVertexAttribArray(0);

	//UNBINDING VBO & VAO ( First VBO then VAO)
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
}
void AddShader(GLuint theProgram , const char* ShaderCode , GLenum ShadeType)
{
	GLuint theShader =glCreateShader(ShadeType);
	const GLchar* theCode[1];
	theCode[0]=ShaderCode;

	GLint codeLength [1];
	codeLength[0]=strlen(ShaderCode);

	glShaderSource(theShader,1,theCode,codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] ={0};
	glGetProgramiv(Shader,GL_VALIDATE_STATUS,&result);
	if(!result)
	{
		glGetShaderInfoLog(Shader,sizeof(eLog),NULL,eLog);
		printf("ERROR Comiling %d Shader :&s  \n" ,ShadeType,eLog);
	}

	glAttachShader(theProgram,theShader);
}
void CompileShader()
{

	 Shader= glCreateProgram();
	if(!Shader)
	{
		printf("Error Creating Shader Program");
		return;
	}

	/*GLuint VertexShader , FragmentShader;
	GLint codeLength [1];
	codeLength[0]=strlen(vShader);
	VertexShader= glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader,1,&vShader,codeLength);
	glCompileShader(VertexShader);
	glAttachShader(Shader,VertexShader);

	codeLength[0]=strlen(fShader);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader,1,&fShader,codeLength);
	glCompileShader(FragmentShader);
	glAttachShader(Shader,FragmentShader);*/
	
	AddShader(Shader,vShader,GL_VERTEX_SHADER);
	AddShader(Shader,fShader,GL_FRAGMENT_SHADER);
	GLint result = 0;
	GLchar eLog[1024] ={0};

	glLinkProgram(Shader);
/*	glGetProgramiv(Shader,GL_LINK_STATUS,&result);
	if(!result)
	{
		glGetProgramInfoLog(Shader,sizeof(eLog),NULL,eLog);
		printf("ERROR lINKING pROGRAM : %S \n" ,eLog);
			
	}
	glValidateProgram(Shader);
	glGetProgramiv(Shader,GL_VALIDATE_STATUS,&result);
	if(!result)
	{
		glGetProgramInfoLog(Shader,sizeof(eLog),NULL,eLog);
		printf("ERROR VALIDATING pROGRAM : %S \n" ,eLog);
	}*/
	
}

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

	CreateTriangle();
	CompileShader();
	//LOOP UNTIL WINDOW CLOSE
	while (!glfwWindowShouldClose(MainWindow))
	{
		//get and handle user input  events (like mouse movement resize window)
		glfwPollEvents();

		
		//clear window
		glClearColor(0.1f,0.6f,0.8f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(Shader);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(0);

		glUseProgram(0);
		
		glfwSwapBuffers(MainWindow);
	}
	
	
	
}
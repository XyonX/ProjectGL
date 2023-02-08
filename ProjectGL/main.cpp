#include<stdio.h>

#include<GL\glew.h>
#include<GLFW/glfw3.h>
#include<cmath>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


GLuint VAO , VBO, Shader  ;
GLint	uniformModel , valueUniform;
const float toRadians = 3.14159265f / 180.0f; ;
const GLint WIDTH = 1280 ,HEIGHT = 720;

bool direction =true;
float triOfset =0.0f;
float triMaxOffset =0.7;
float triIncrement=0.0005f;


//vertex shader source for vertex
static const char* vShader = R"(					

#version 330									
layout (location = 0) in vec3 pos ;															
uniform mat4 model;
uniform float value ;
void main ()									
{												
	gl_Position =   vec4 (pos.x,pos.y,pos.z,1.0); 										

})";

//fragment shader 
static const char* fShader = R"(

#version 330
out vec4 FragColor;   

void main()
{
	FragColor = vec4 (0.99,0.62,0.007,1.0);
})";


//this funtion creates triangle
void CreateTriangle()
{
	// vertex for 
	GLfloat vertices[]=
		{
			/*-0.5,-0.5,0.0,
			0.5,-0.5,0.0,
			0.0,0.5,0.0,*/
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f
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
	GLuint theShader = glCreateShader(ShadeType);
	const GLchar* theCode[1];
	theCode[0]=ShaderCode;

	GLint codeLength [1];
	codeLength[0]=strlen(ShaderCode);
	
	glShaderSource(theShader,1,theCode,codeLength);
	glCompileShader(theShader);

	GLint result =0;
	GLchar eLog [1024] = {0};
	glGetShaderiv(theShader,GL_COMPILE_STATUS,&result);
	if(!result)
	{
		glGetShaderInfoLog(theShader,sizeof(eLog),NULL,eLog);
		printf("Error Compiling the %d shader  :%s \n",ShadeType,eLog);
		return;
	}
	glAttachShader(theProgram  ,theShader );
}

void CompileShader()
{
	Shader= glCreateProgram();
	if(!Shader)
	{
		printf("Error Creating Shader Program");
	}
	AddShader(Shader,vShader,GL_VERTEX_SHADER);
	AddShader(Shader,fShader,GL_FRAGMENT_SHADER);

	GLint result =0;
	GLchar eLog [1024] = {0};
	glLinkProgram(Shader);
	glGetProgramiv(Shader,GL_LINK_STATUS,&result);
	if(!result)
	{
		glGetProgramInfoLog(Shader,sizeof(eLog),NULL,eLog);
		printf("Error Linking Program :%s \n",eLog);
		return;
	}
	glValidateProgram(Shader);
	glGetProgramiv(Shader,GL_VALIDATE_STATUS,&result);
	if(!result)
	{
		glGetProgramInfoLog(Shader,sizeof(eLog),NULL,eLog);
		printf("Error Validating Program :%s \n",eLog);
		return;
	}

	uniformModel =glGetUniformLocation(Shader , "model");
	valueUniform=glGetUniformLocation(Shader,"value");
	
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

	//SETUP WINDOW PROPERTIES

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


		if(direction)
		{
			triOfset+=triIncrement;
		}
		else
		{
			triOfset-=triIncrement;
		}

		if(abs(triOfset)>=triMaxOffset)
		{
			direction=!direction;
		}
		
		//clear window
		//glClearColor(0.71,0.72,0.84,1.0f);
		glClearColor(0.0,0.0,0.0,1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(Shader);

		// thius is a diagonal matrix which will act as base axis and upon will be applied transformation
		glm::mat4 model ;
		//model = glm::translate(model,glm::vec3(triOfset,0,0));
		//model = glm::rotate(model,45*toRadians,glm::vec3(0.0f,0.0f,1.0f));
		model = glm::scale(model,glm::vec3(2.0f,2.0f,1.0f));
		
		//glUniform1f(uniformXMove,triOfset);
		//glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(model));
		glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(model));
		glUniform1f(valueUniform,10.0f);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES,0,3);

		
		glBindVertexArray(0);
		glUseProgram(0);
		
		glfwSwapBuffers(MainWindow);
	}
	
	
	
}
#include<stdio.h>
#include <iostream> 
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"



int main ()
{
    ///*********************************
    ///*********************************
    ///SETTING UP GLFW AND GLEW

    // initializing glfw 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* Window = glfwCreateWindow(800,800,"GL_WINDOW ",NULL,NULL);

    // cheaking wheather the window availalle or not 
    if(Window == NULL)
    {
        std::cout<<"Failed To Create Window " <<std::endl;
        glfwTerminate();
        return -1 ;
    }
    
    // if the winow available then we are making the window current window 
    glfwMakeContextCurrent(Window);
    
    // setting the viewport to gl use 
    glViewport(0,0,800,800);
    glClearColor(0.65f,0.11f,0.89f,1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Window);

    // init glew                    // 02
    glewInit();
    
    // check if glew initialize or not 
    if (glewInit() != GLEW_OK)
    {

        printf("glew initialization failed ");
        glfwDestroyWindow(Window);
        glfwTerminate();
    }

    ///**********************************
    ///**********************************
    ///**********************************
    ///ACTUAL STARTING OF GLFW CODE


    ///
    ///
    ///
    ///setting up Vertices and indices 
    GLfloat vertices [] =
  {
        //COORDINATE        //COLOR         //TEXTURE COORDINATE    
        -0.5f,-0.5f,0.0f,   1.0f,0.0f,0.0f, 0.0f,0.0f,
        -0.5f,0.5f,0.0f,    0.0f,1.0f,0.0f, 0.0f,1.0f,
        0.5f,0.5f,0.0f,     0.0f,0.0f,1.0f, 1.0f,1.0f,
        0.5f,-0.5f,0.0f,    1.0f,1.0f,0.0f , 1.0f,0.0f
    };
    GLuint Indices []=
    {
     
        0,1,2,
        0,2,3
        
    };
    ///
    ///
    ///
    //SETTING VAO AND VBO
    VAO VAO1 ;
    VAO1.Bind();
    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(Indices,sizeof(Indices));
    VAO1.LinkAttrib(VBO1,0,3,GL_FLOAT , 8*sizeof(float),(void*)0);
    VAO1.LinkAttrib(VBO1,1,3,GL_FLOAT,8*sizeof(float),(void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1,2,2,GL_FLOAT,8*sizeof(float),(void*)(6*sizeof(float)));
    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();

    ///
    ///
    ///CREATING SHADER 
    Shader Shader1("default.vert","default.frag");

    //getting the uniform
    // Gets ID of uniform called "scale"
    GLuint uniID = glGetUniformLocation(Shader1.ID, "scale");


    const char * Image = "Resources/xoro.jpg";
    Texture Texture01(Image,GL_TEXTURE_2D,GL_TEXTURE0,GL_RGB,GL_UNSIGNED_INT);
    Texture01.texUnit(Shader1,"tex0",0);

    
   

    ///
    ///Activating Shader
    Shader1.Activate();
    
    // STARTING OF MAIN PROGRAM LOOP
    while (!glfwWindowShouldClose(Window))
    {
        // Specify the color of the background
        glClearColor(0.8f,0.966f,0.98f,1.f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        Shader1.Activate();
        // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
        glUniform1f(uniID,0.5f);
        // Binds texture so that is appears in rendering
        Texture01.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
       // glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(Window);
        // TAKE CARE OF GLFW EVENT 
        glfwPollEvents();
    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    Texture01.Delete();
    
    // code executing here mean we press the cross button and we are ready to exit  and clean up
    glfwDestroyWindow(Window);
    glfwTerminate();
    return  0 ;
    
    
}

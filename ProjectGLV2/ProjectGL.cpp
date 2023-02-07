#include<stdio.h>
#include <iostream> 
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



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
        -0.5f,-0.5f,0.0f,   1.0f,0.0f,0.0f, 0.0f,0.0f,
        -0.5f,0.5f,0.0f,    0.0f,1.0f,0.0f, 0.0f,5.0f,
        0.5f,0.5f,0.0f,     0.0f,0.0f,1.0f, 5.0f,5.0f,
        0.5f,-0.5f,0.0f,    1.0f,1.0f,0.0f , 5.0f,0.0f
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
    ///
    //Setting up image dat
    Shader Shader1("default.vert","default.frag");
    
    int HeightImg , WidthImg ,NumColCh;

    // Loading the texture in a char
    unsigned char*ImageChar = stbi_load("Resources/xoro.jpg",&WidthImg,&HeightImg,&NumColCh,0);
    stbi_set_flip_vertically_on_load(true);

    ///
    ///
    ///
    //Creating and setting up texture
    GLuint Texture ;
    // GENERATING TEXTURE 
    glGenTextures(1,&Texture);
    // ACTIVATING TEXTURE
    glActiveTexture(GL_TEXTURE0);
    // BINDING WITH ACTIVE TEXTURE
    glBindTexture(GL_TEXTURE_2D,Texture);
    // SETTING TEXTURE SETTING HOW IT SHOULD APPEAR//HERE MODIFYING MIN FILTER// DECIDES PIXELATED OR BLURRY
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    // SETTING TEXTURE SETTING HOW IT SHOULD APPEAR//HERE MODIFYING MIN FILTER// DECIDES PIXELATED OR BLURRY
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // SETTING TEXTURE SETTING HOW IT SHOULD APPEAR//HERE MODIFYING MAG FILTER// DECIDES HOW TEXTURE WILL REPEAT
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);

    // GEBNERAte texture image 
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,WidthImg,HeightImg,0,GL_RGB,GL_UNSIGNED_BYTE,ImageChar);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ImageChar);
    glBindTexture(GL_TEXTURE_2D,0);
    
    GLuint tex0Uni = glGetUniformLocation(Shader1.ID,"tex0");
    Shader1.Activate();
    glUniform1i(tex0Uni,0);
    // looping  until we press the x mark on the window 
    while (!glfwWindowShouldClose(Window))
    {
        glClearColor(0.8f,0.966f,0.98f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        Shader1.Activate();
        glUniform1f(tex0Uni,0.5f);
        glBindTexture(GL_TEXTURE_2D,Texture);
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
    glDeleteTextures(1,&Texture);
    
    // code executing here mean we press the cross button and we are ready to exit  and clean up
    glfwDestroyWindow(Window);
    glfwTerminate();
    return  0 ;
    
    
}

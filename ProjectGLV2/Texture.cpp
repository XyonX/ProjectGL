#include "Texture.h"

Texture::Texture(const char* image, GLenum textype,GLenum slot, GLenum format, GLenum pixelType)
{

    //type of texture object
    type =textype;

    //Setting up image data
    int HeightImg , WidthImg ,NumColCh;

    // Loading the texture in a char
    //flipping at the  time of loading 
    stbi_set_flip_vertically_on_load(true);
    unsigned char*ImageChar = stbi_load(image,&WidthImg,&HeightImg,&NumColCh,0);


    ///
    ///
    ///
    //Creating and setting up texture
    ///GLuint Texture ;HERE USING ID
    // GENERATING TEXTURE 
    glGenTextures(1,&ID);
    // ACTIVATING TEXTURE(GL_TEXTURE0)
    glActiveTexture(slot);
    // BINDING WITH ACTIVE TEXTURE
    glBindTexture(textype,ID);
    // SETTING TEXTURE SETTING HOW IT SHOULD APPEAR//HERE MODIFYING MIN FILTER// DECIDES PIXELATED OR BLURRY
    glTexParameteri(textype,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    // SETTING TEXTURE SETTING HOW IT SHOULD APPEAR//HERE MODIFYING MIN FILTER// DECIDES PIXELATED OR BLURRY
    glTexParameteri(textype,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    // SETTING TEXTURE SETTING HOW IT SHOULD APPEAR//HERE MODIFYING MAG FILTER// DECIDES HOW TEXTURE WILL REPEAT
    glTexParameteri(textype,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(textype,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    ///
    ///
    ///
    // GENERATING TEXTURE IMAGE FROM THE CHAR SOURCE  AND SETTING UP
    glTexImage2D(textype,0,GL_RGB,WidthImg,HeightImg,0,GL_RGB,GL_UNSIGNED_BYTE,ImageChar);
    glGenerateMipmap(textype);
    stbi_image_free(ImageChar);

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(textype, 0);
}

void Texture::texUnit(Shader& Shader, const char* uniform, GLuint unit)
{
    ///
    ///Getting UNIFORM ID
    GLuint texUni = glGetUniformLocation(Shader.ID,uniform);
    Shader.Activate();
    glUniform1i(texUni,unit);
    
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D,ID);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}

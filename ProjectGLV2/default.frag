//Fragment Shader source code

#version 330 core
/*
out vec4 FragColor;
in vec3 color;
in vec2 texcoord;

uniform sampler2D tex0;
void main()

{
  
  FragColor =texture(tex0,texcoord);

}*/

out vec4 FragColor;
in vec3 color ;
in vec2 TexCoord;

uniform sampler2D tex0;
void main()
{
  //FragColor = vec4(color, 1.0f);
  FragColor=texture(tex0,TexCoord);
}
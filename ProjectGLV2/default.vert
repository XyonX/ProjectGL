// Vertex Shader source code


#version 330 core
/*
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 acolor;
layout (location = 2) in vec2 aTex;

out vec3 color ;
out vec2 texcoord;

uniform float scale ;

void main()
{
  gl_Position = vec4(aPos.x +aPos.x *scale, aPos.y+ aPos.y*scale, aPos.z + aPos.z*scale, 1.0);
  color = acolor;
  texcoord =aTex;

}*/
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color ;
out vec2 TexCoord;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   color =aColor;
   TexCoord=aTex;
}
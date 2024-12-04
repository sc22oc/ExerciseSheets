#version 430

layout ( location = 0 ) in vec3 iPosition;
layout ( location = 1 ) in vec3 iColor;
out vec3 v2fColor;

layout ( location = 0 ) uniform mat4 projCamWor;

void main()
{
    v2fColor = iColor;
    
    gl_Position = projCamWor * vec4(iPosition, 1.0);
}

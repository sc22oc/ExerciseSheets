#version 430

layout ( location = 0 ) in vec3 iPosition;
layout ( location = 1) in vec2 iTexCoord;

layout ( location = 0 ) uniform mat4 projCamWor;

out vec2 v2fTexCoord;

void main()
{
    v2fTexCoord = iTexCoord;    
    gl_Position = projCamWor * vec4(iPosition, 1.0);
}

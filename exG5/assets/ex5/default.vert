#version 430

layout ( location = 0 ) in vec3 iPosition;
layout ( location = 1 ) in vec3 iColor;
layout ( location = 2 ) in vec3 iNormal;
out vec3 v2fColor;
out vec3 v2fNormal;

layout ( location = 0 ) uniform mat4 projCamWor;
layout ( location = 1 ) uniform mat3 uNormalMatrix;

void main()
{
    v2fColor = iColor;
    v2fNormal = normalize(uNormalMatrix * iNormal);
    
    gl_Position = projCamWor * vec4(iPosition, 1.0);
}
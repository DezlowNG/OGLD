// TYPE=VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}

// TYPE=FRAGMENT
#version 330 core
void main()
{
    // gl_FragDepth = gl_FragCoord.z;
}
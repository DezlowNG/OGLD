// TYPE=VERTEX

#version 450 core
layout (location = 0) in vec3 aPos;
uniform mat4 MVP;
void main()
{
    gl_Position = MVP * vec4(aPos.xyz, 1.0);
};

// TYPE=FRAGMENT

#version 450 core
out vec4 FragColor;
uniform vec3 color;
void main()
{
    FragColor = vec4(color.xyz, 1.0f);
};

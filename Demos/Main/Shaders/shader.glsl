// TYPE=VERTEX

#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos.xyz, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

// TYPE=FRAGMENT

#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
};

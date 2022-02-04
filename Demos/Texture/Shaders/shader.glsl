// TYPE=VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;

out vec2 UV;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    UV = aPos.xy;
}

// TYPE=FRAGMENT
#version 330 core
out vec4 FragColor;
uniform sampler2D uTexture;
uniform int uTextureWidth, uTextureHeight;
in vec2 UV;
void main()
{
    vec4 Texture = texture2D(uTexture, vec2(UV.x / uTextureWidth, UV.y / uTextureHeight));
    if(Texture.a < 0.1)
        discard;
    FragColor = Texture.rgba;
}
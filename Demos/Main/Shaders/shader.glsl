// TYPE=VERTEX
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;
out vec4 MVP;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    mat4 lightSpaceMatrix;
};

uniform mat4 model;

void main()
 {
     FragPos = vec3(model * vec4(aPos, 1.0));
     Normal = transpose(inverse(mat3(model))) * aNormal;
     TexCoords = aTexCoords;
     FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
     MVP = view * model * vec4(aPos, 1.0);

     gl_Position = projection * MVP;
 }

// TYPE=FRAGMENT
#version 330 core
out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPosLightSpace;
in vec4 MVP;

uniform struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
} material;

uniform struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} light;

uniform sampler2D shadowMap;
uniform vec3 viewPos;

uniform struct Fog
{
    float MinDist;
    float MaxDist;
} uFog;

uniform bool uDrawShadows;
uniform bool uDrawFog;

float ShadowCalculation()
{
    vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = !uDrawShadows ? 1.0 : texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            }
        }
        shadow /= 9.0;
        if(projCoords.z > 1.0)
            shadow = 0.0;

    return shadow;
}

void main()
{
    vec3 color = texture(material.diffuse, TexCoords).rgb;
    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.4);
    vec3 ambient = 0.25 * color;
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = 6.5 * pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = vec3(2.0) * spec * texture(material.specular, TexCoords).rgb;

    vec3 lighting;
    if (uDrawShadows)
    {
        float shadow = ShadowCalculation();
        lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    }
    else
    {
        float shadow = ShadowCalculation();
        lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    }

    lighting = lighting / (lighting + vec3(1.0));
    lighting = pow(lighting, vec3(1.0/2.2));

    if (uDrawFog)
    {
        vec4  fog_colour = vec4(0.4, 0.4, 0.4, 1.0);

        float dist = length(MVP.xyz);
        float fog_factor = (uFog.MaxDist - dist) /
                          (uFog.MaxDist - uFog.MinDist);
        fog_factor = clamp(fog_factor, 0.0, 1.0);

        FragColor = mix(fog_colour, vec4(lighting, 1.0), fog_factor);
    }
    else
    {
        FragColor = vec4(lighting, 1.0);
    }
}
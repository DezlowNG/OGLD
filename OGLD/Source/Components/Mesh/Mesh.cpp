#include "Mesh.h"

static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

Mesh::Mesh(std::string const& path)
{
    const char* MeshVertShader = {
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aNormal;\n"
        "layout(location = 2) in vec2 aTexCoords;\n"
        "layout(location = 3) in vec3 aTangent;\n"
        "layout(location = 4) in vec3 aBitangent;\n"
        "out vec3 FragPos;\n"
        "out vec3 TangentLightPos;\n"
        "out vec3 TangentViewPos;\n"
        "out vec3 TangentFragPos;\n"
        "out vec2 TexCoords;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 viewPos;\n"
        "void main()\n"
        "{\n"
        "    vec4 pos = model * vec4(aPos, 1.0);\n"
        "    FragPos = pos.xyz;\n"
        "    TexCoords = aTexCoords;\n"
        "    mat3 normalMatrix = transpose(inverse(mat3(model)));\n"
        "    vec3 T = normalize(normalMatrix * aTangent);\n"
        "    vec3 N = normalize(normalMatrix * aNormal);\n"
        "    T = normalize(T - dot(T, N) * N);\n"
        "    vec3 B = cross(N, T);\n"
        "    mat3 TBN = transpose(mat3(T, B, N));\n"
        "    TangentLightPos = TBN * lightPos;\n"
        "    TangentViewPos = TBN * viewPos;\n"
        "    TangentFragPos = TBN * FragPos;\n"
        "    gl_Position = projection * view * pos;\n"
        "}\0"
    };

    const char* MeshFragShader = {
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 FragPos;\n"
        "in vec3 TangentLightPos;\n"
        "in vec3 TangentViewPos;\n"
        "in vec3 TangentFragPos;\n"
        "in vec2 TexCoords;\n"
        "uniform sampler2D texture_diffuse1;\n"
        "uniform sampler2D texture_specular1;\n"
        "uniform sampler2D texture_normal1;\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 viewPos;\n"
        "void main()\n"
        "{\n"
        "   vec3 normal = texture(texture_normal1, TexCoords).rgb;\n"
        "   normal = normalize(normal * 2.0 - 1.0);\n"
        "   vec3 color = texture(texture_diffuse1, TexCoords).rgb;\n"
        "   vec3 ambient = 0.1 * color;\n"
        "   vec3 lightDir = normalize(TangentLightPos - TangentFragPos);\n"
        "   float diff = max(dot(lightDir, normal), 0.0);\n"
        "   vec3 diffuse = diff * color;\n"
        "   vec3 viewDir = normalize(TangentViewPos - TangentFragPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, normal);\n"
        "   vec3 halfwayDir = normalize(lightDir + viewDir);\n"
        "   float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);\n"
        "	vec3 specular = vec3(0.3) * spec;\n"
        "	FragColor = vec4(ambient + diffuse + specular, 1.0);\n"
        "}\0"
    };

    model = glm::mat4(1.0f);
    shader.LoadFromSource(MeshVertShader, MeshFragShader);
    loadModel(path);
}

void Mesh::Draw()
{
    shader.use();
    shader.setMat4("view", mLight->camera->GetViewMatrix());
    shader.setMat4("projection", mLight->camera->Projection);
    shader.setMat4("model", model);
    shader.setVec3("viewPos", mLight->camera->Position);
    shader.setVec3("lightPos", mLight->GetPosition());

    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(this->shader);
}

void Mesh::loadModel(std::string const& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Mesh::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

MeshStruct Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;

        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return MeshStruct(vertices, indices, textures);
}

std::vector<Texture> Mesh::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

OBJLoader::OBJLoader() {}

OBJLoader::~OBJLoader() {
    // Cleanup textures if necessary
}

// Helper to split string
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool OBJLoader::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    // Extract base directory
    size_t lastSlash = filename.find_last_of("/\\");
    baseDir = (lastSlash == std::string::npos) ? "" : filename.substr(0, lastSlash + 1);

    std::string line;
    std::string currentMaterial = "default";
    
    // Ensure a default mesh group exists
    bool groupActive = false;
    MeshGroup currentGroup;
    currentGroup.materialName = currentMaterial;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            Vector3 v;
            ss >> v.x >> v.y >> v.z;
            temp_vertices.push_back(v);
        } else if (prefix == "vt") {
            Vector2 vt;
            ss >> vt.x >> vt.y;
            temp_texCoords.push_back(vt);
        } else if (prefix == "vn") {
            Vector3 vn;
            ss >> vn.x >> vn.y >> vn.z;
            temp_normals.push_back(vn);
        } else if (prefix == "usemtl") {
            if (!currentGroup.vertices.empty()) {
                meshGroups.push_back(currentGroup);
                currentGroup.vertices.clear();
            }
            ss >> currentMaterial;
            currentGroup.materialName = currentMaterial;
        } else if (prefix == "mtllib") {
            std::string mtlFilename;
            ss >> mtlFilename;
            loadMtl(baseDir + mtlFilename);
        } else if (prefix == "f") {
            std::string vertexStr;
            std::vector<Vertex> faceVertices;
            
            while (ss >> vertexStr) {
                std::vector<std::string> parts = split(vertexStr, '/');
                Vertex v;
                
                // Position
                int vIdx = std::stoi(parts[0]) - 1;
                v.position = temp_vertices[vIdx];

                // TexCoord
                if (parts.size() > 1 && !parts[1].empty()) {
                    int vtIdx = std::stoi(parts[1]) - 1;
                    v.texCoord = temp_texCoords[vtIdx];
                } else {
                    v.texCoord = {0.0f, 0.0f};
                }

                // Normal
                if (parts.size() > 2 && !parts[2].empty()) {
                    int vnIdx = std::stoi(parts[2]) - 1;
                    v.normal = temp_normals[vnIdx];
                } else {
                    v.normal = {0.0f, 0.0f, 1.0f}; // Default normal
                }
                
                faceVertices.push_back(v);
            }

            // Triangulate fan
            for (size_t i = 1; i < faceVertices.size() - 1; ++i) {
                currentGroup.vertices.push_back(faceVertices[0]);
                currentGroup.vertices.push_back(faceVertices[i]);
                currentGroup.vertices.push_back(faceVertices[i + 1]);
            }
        }
    }

    if (!currentGroup.vertices.empty()) {
        meshGroups.push_back(currentGroup);
    }

    file.close();
    
    // Calculate normals if missing (simple flat shading normals)
    // This is a basic fallback; ideally we'd average normals for smooth shading
    // but for this assignment, reading provided normals is priority.
    
    return true;
}

void OBJLoader::loadMtl(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open MTL file " << filename << std::endl;
        return;
    }

    std::string line;
    std::string currentMtlName;
    Material currentMtl;
    bool mtlActive = false;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "newmtl") {
            if (mtlActive) {
                materials[currentMtlName] = currentMtl;
            }
            ss >> currentMtlName;
            currentMtl = Material(); // Reset
            currentMtl.name = currentMtlName;
            mtlActive = true;
        } else if (prefix == "Ka") {
            ss >> currentMtl.Ka.x >> currentMtl.Ka.y >> currentMtl.Ka.z;
        } else if (prefix == "Kd") {
            ss >> currentMtl.Kd.x >> currentMtl.Kd.y >> currentMtl.Kd.z;
        } else if (prefix == "Ks") {
            ss >> currentMtl.Ks.x >> currentMtl.Ks.y >> currentMtl.Ks.z;
        } else if (prefix == "Ns") {
            ss >> currentMtl.Ns;
        } else if (prefix == "map_Kd") {
            std::string texFile;
            ss >> texFile;
            currentMtl.map_Kd = texFile;
            currentMtl.textureID = loadTexture(baseDir + texFile);
        }
    }
    if (mtlActive) {
        materials[currentMtlName] = currentMtl;
    }
}

unsigned int OBJLoader::loadTexture(const std::string& filename) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}

void OBJLoader::draw() {
    for (const auto& group : meshGroups) {
        // Apply Material
        if (materials.find(group.materialName) != materials.end()) {
            const Material& mtl = materials.at(group.materialName);
            
            GLfloat ambient[] = { mtl.Ka.x, mtl.Ka.y, mtl.Ka.z, 1.0f };
            GLfloat diffuse[] = { mtl.Kd.x, mtl.Kd.y, mtl.Kd.z, 1.0f };
            GLfloat specular[] = { mtl.Ks.x, mtl.Ks.y, mtl.Ks.z, 1.0f };
            GLfloat shininess[] = { mtl.Ns };

            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

            if (mtl.textureID > 0) {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, mtl.textureID);
            } else {
                glDisable(GL_TEXTURE_2D);
            }
        } else {
            // Default material
            glDisable(GL_TEXTURE_2D);
            GLfloat defaultColor[] = { 0.8f, 0.8f, 0.8f, 1.0f };
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, defaultColor);
        }

        glBegin(GL_TRIANGLES);
        for (const auto& v : group.vertices) {
            glNormal3f(v.normal.x, v.normal.y, v.normal.z);
            glTexCoord2f(v.texCoord.x, v.texCoord.y);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();
    }
}

Vector3 OBJLoader::getCenter() const {
    if (temp_vertices.empty()) return {0,0,0};
    float minX = 1e9, minY = 1e9, minZ = 1e9;
    float maxX = -1e9, maxY = -1e9, maxZ = -1e9;

    for (const auto& v : temp_vertices) {
        if (v.x < minX) minX = v.x;
        if (v.y < minY) minY = v.y;
        if (v.z < minZ) minZ = v.z;
        if (v.x > maxX) maxX = v.x;
        if (v.y > maxY) maxY = v.y;
        if (v.z > maxZ) maxZ = v.z;
    }
    return { (minX + maxX) / 2.0f, (minY + maxY) / 2.0f, (minZ + maxZ) / 2.0f };
}

float OBJLoader::getMaxDimension() const {
    if (temp_vertices.empty()) return 1.0f;
    float minX = 1e9, minY = 1e9, minZ = 1e9;
    float maxX = -1e9, maxY = -1e9, maxZ = -1e9;

    for (const auto& v : temp_vertices) {
        if (v.x < minX) minX = v.x;
        if (v.y < minY) minY = v.y;
        if (v.z < minZ) minZ = v.z;
        if (v.x > maxX) maxX = v.x;
        if (v.y > maxY) maxY = v.y;
        if (v.z > maxZ) maxZ = v.z;
    }
    
    float dx = maxX - minX;
    float dy = maxY - minY;
    float dz = maxZ - minZ;
    
    return std::max(dx, std::max(dy, dz));
}

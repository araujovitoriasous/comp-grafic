#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <map>

// Basic structures for 3D data
struct Vector3 {
    float x, y, z;
};

struct Vector2 {
    float x, y;
};

struct Vertex {
    Vector3 position;
    Vector2 texCoord;
    Vector3 normal;
};

struct Material {
    std::string name;
    Vector3 Ka; // Ambient
    Vector3 Kd; // Diffuse
    Vector3 Ks; // Specular
    float Ns;   // Shininess
    std::string map_Kd; // Diffuse texture map
    unsigned int textureID; // OpenGL texture ID
};

struct MeshGroup {
    std::string materialName;
    std::vector<Vertex> vertices;
};

class OBJLoader {
public:
    OBJLoader();
    ~OBJLoader();

    bool load(const std::string& filename);
    void draw(); // Helper to draw using immediate mode (glBegin/glEnd) or Arrays

    const std::vector<MeshGroup>& getMeshGroups() const { return meshGroups; }
    const std::map<std::string, Material>& getMaterials() const { return materials; }
    
    // Helper to get center and size for camera positioning
    Vector3 getCenter() const;
    float getMaxDimension() const;

private:
    std::vector<MeshGroup> meshGroups;
    std::map<std::string, Material> materials;
    std::string baseDir;

    void loadMtl(const std::string& filename);
    unsigned int loadTexture(const std::string& filename);
    
    // Temporary storage during parsing
    std::vector<Vector3> temp_vertices;
    std::vector<Vector2> temp_texCoords;
    std::vector<Vector3> temp_normals;
};

#endif


#version 330 core

// Identical to the layout configured in Mesh::SetupMesh().
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;       // local space -> world space
uniform mat4 view;        // world space -> camera/view space
uniform mat4 projection;  // view space -> clip space

void main()
{
    TexCoord = aTexCoord;

    // calculates the position of the vertex in world space, which is needed for lighting calculations
    // before transforming to view space and clip space. The w component is set to 1.0 to ensure proper translation.
    vec4 worldPosition = model * vec4(aPosition, 1.0);
    FragPos = worldPosition.xyz;

    // normals must be transformed by the inverse transpose of the model matrix to account for any non-uniform scaling that may have been applied to the model. This ensures that the normals remain perpendicular to the surface after transformations, which is crucial for accurate lighting calculations.
    // non uniform scaling can skew the normals, leading to incorrect lighting. The inverse transpose of the model matrix corrects this by effectively "undoing" the scaling effect on the normals.
    // transport the normals to world space using the inverse transpose of the model matrix. This is necessary because normals are directional vectors and should not be affected by translation, only by rotation and scaling.
    mat3 normalMatrix = mat3(transpose(inverse(model)));
    Normal = normalMatrix * aNormal;

    gl_Position = projection * view * worldPosition;
}

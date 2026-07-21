/*
    Vertex shader da treasure chest.

    Este estágio executa uma vez para cada vértice. Além de produzir a
    posição final em clip space, ele prepara os três dados interpolados que
    o fragment shader necessita para calcular Phong lighting por pixel:

      TexCoord - coordenada usada para amostrar a textura;
      FragPos  - posição do fragmento em world space;
      Normal   - normal da superfície transformada para world space.

    Todos os vetores usados na iluminação ficam no mesmo espaço (world
    space). Isso é essencial: produtos escalares entre vetores expressos em
    espaços diferentes não representam ângulos corretos.
*/

#version 330 core

// Layout idêntico ao configurado em Mesh::SetupMesh().
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

    // Calculada separadamente porque a iluminação precisa desta posição
    // antes que view e projection alterem o sistema de coordenadas.
    vec4 worldPosition = model * vec4(aPosition, 1.0);
    FragPos = worldPosition.xyz;

    // Normais não devem ser transformadas diretamente por model quando há
    // escala não uniforme (como nas paredes finas do baú). A inversa
    // transposta preserva a perpendicularidade entre normal e superfície.
    mat3 normalMatrix = mat3(transpose(inverse(model)));
    Normal = normalMatrix * aNormal;

    gl_Position = projection * view * worldPosition;
}

/*
    Fragment shader com Phong lighting por fragmento.

    O modelo soma três componentes:

      ambient  - iluminação mínima, independente da orientação;
      diffuse  - luz fosca, dependente do ângulo entre normal e luz;
      specular - reflexo brilhante, dependente também da câmera.

    A textura fornece a cor difusa do material. Ambiente e difusa modulam
    essa cor; o reflexo especular é somado separadamente com a cor da luz.
*/

#version 330 core

in vec2 TexCoord;
in vec3 FragPos; // posição interpolada em world space
in vec3 Normal;  // normal interpolada em world space

out vec4 FragColor;

uniform sampler2D texture1;

// Dados da luz pontual e da câmera, enviados por Main.cpp.
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 fillLightPos;
uniform vec3 fillLightColor;
uniform vec3 viewPos;

// Propriedades ajustáveis do material/iluminação.
uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;
uniform float rimStrength;
uniform vec3 rimColor;
uniform float exposure;

// Reutiliza a equação Phong para cada luz. O retorno contém a cor difusa
// da madeira e o highlight especular produzido por uma fonte pontual.
vec3 calculatePointLight(
    vec3 position,
    vec3 color,
    vec3 normal,
    vec3 viewDirection,
    vec3 albedo)
{
    vec3 lightDirection = normalize(position - FragPos);
    float diffuseAmount = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diffuseAmount * color * albedo;

    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(
        max(dot(viewDirection, reflectedDirection), 0.0), shininess);
    vec3 specular = specularStrength * specularAmount * color;

    return diffuse + specular;
}

void main()
{
    vec4 texel = texture(texture1, TexCoord);

    // A interpolação pode alterar o comprimento da normal, portanto ela é
    // normalizada novamente para que os produtos escalares sejam corretos.
    vec3 normal = normalize(Normal);
    // Ambiente: mantém visíveis as regiões que não apontam para a luz.
    vec3 ambient = ambientStrength * lightColor;
    vec3 viewDirection = normalize(viewPos - FragPos);

    // A principal modela frente/topo. A luz de preenchimento vem do lado
    // oposto, deixando Phong visível na caixa inteira, aberta ou fechada.
    vec3 primaryLight = calculatePointLight(
        lightPos, lightColor, normal, viewDirection, texel.rgb);
    vec3 fillLight = calculatePointLight(
        fillLightPos, fillLightColor, normal, viewDirection, texel.rgb);

    // Rim light: intensifica apenas ângulos rasantes em relação à câmera.
    // Mesmo fechado, o baú ganha uma silhueta clara e a separação entre
    // tampa e base fica mais fácil de perceber.
    float rimAmount = pow(
        1.0 - max(dot(normal, viewDirection), 0.0), 3.0);
    vec3 rim = rimStrength * rimAmount * rimColor;

    vec3 finalColor = ambient * texel.rgb + primaryLight + fillLight + rim;

    // A exposição reduz a luminosidade geral sem eliminar as diferenças
    // entre ambiente, difusa, especular e contorno.
    finalColor *= exposure;

    // Aproxima a conversão linear -> sRGB depois do ajuste de exposição.
    finalColor = pow(max(finalColor, vec3(0.0)), vec3(1.0 / 2.2));
    FragColor = vec4(finalColor, texel.a);
}

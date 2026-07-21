
#version 330 core

in vec2 TexCoord;
in vec3 FragPos; // postion interpolated in world space
in vec3 Normal;  // normal interpolated in world space

out vec4 FragColor;

uniform sampler2D texture1;

// data from light sources and camera, sent from Main.cpp.
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 fillLightPos;
uniform vec3 fillLightColor;
uniform vec3 viewPos;

// Adjustable properties for the lighting model, allowing for fine-tuning of the visual appearance of the scene.
uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;
uniform float rimStrength;
uniform vec3 rimColor;
uniform float exposure;

// reutilizes the same lighting model for both the primary light and the fill light, allowing for consistent shading across different light sources. The function calculates the diffuse reflection of the wood and the specular highlight produced by a point light source.
// from wood to metal, the specular highlight is more pronounced, and the diffuse reflection is less dominant. The function takes into account the position and color of the light source, the surface normal, the view direction, and the albedo (base color) of the material to compute the final color contribution from each light source.
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

    // the interpolated normal is not guaranteed to be unit length, so it is 
    // normalized before being used in lighting calculations to ensure accurate results.
    vec3 normal = normalize(Normal);
    // Ambient light is a constant illumination that affects all surfaces equally, regardless of their orientation or position relative to the light source. It simulates indirect lighting and provides a base level of brightness to the scene.
    vec3 ambient = ambientStrength * lightColor;
    vec3 viewDirection = normalize(viewPos - FragPos);

    // the principal light is the main source of illumination, creating strong highlights and shadows based on the surface orientation. The fill light is a secondary light source that softens shadows and reduces contrast, providing a more balanced lighting effect. The fill light is positioned opposite to the principal light, ensuring that Phong shading remains visible across the entire surface, whether the chest is open or closed.
    // oposite to the principal light, ensuring that Phong shading remains visible across the entire surface, whether the chest is open or closed.
    vec3 primaryLight = calculatePointLight(
        lightPos, lightColor, normal, viewDirection, texel.rgb);
    vec3 fillLight = calculatePointLight(
        fillLightPos, fillLightColor, normal, viewDirection, texel.rgb);

    // Rim light: intensifies the edges of the object, creating a glowing outline effect that enhances the perception of depth and volume. It is particularly effective in highlighting the contours of the chest, making it stand out against the background.
    // even closer to the edges, the rim light is more pronounced, creating a halo effect that accentuates the shape of the chest. This effect is achieved by calculating the angle between the surface normal and the view direction, with a stronger rim light applied to surfaces facing away from the camera. The rim light's color and intensity can be adjusted to achieve the desired visual impact, allowing for creative control over the final appearance of the chest.
  
    float rimAmount = pow(
        1.0 - max(dot(normal, viewDirection), 0.0), 3.0);
    vec3 rim = rimStrength * rimAmount * rimColor;

    vec3 finalColor = ambient * texel.rgb + primaryLight + fillLight + rim;

    // The exposure adjustment is applied to the final color after combining all lighting contributions, including ambient, diffuse, specular, and rim lighting. This step ensures that the overall brightness of the scene can be controlled, allowing for a more realistic and visually appealing rendering. The exposure factor can be adjusted to simulate different lighting conditions, such as bright sunlight or dim indoor lighting, enhancing the overall visual experience.
    // between the exposure adjustment and the sRGB conversion, the final color is clamped to ensure that it remains within a valid range, preventing any potential artifacts or color distortions. This step is crucial for maintaining the integrity of the rendered image, ensuring that the colors remain vibrant and true to life.
    finalColor *= exposure;

    // aproximate sRGB conversion, which is a standard color space used for displaying images on screens. The conversion is applied to the final color after all lighting calculations and exposure adjustments have been made, ensuring that the colors are accurately represented when displayed on various devices. This step is essential for achieving a consistent and visually appealing appearance across different platforms and display technologies.
    finalColor = pow(max(finalColor, vec3(0.0)), vec3(1.0 / 2.2));
    FragColor = vec4(finalColor, texel.a);
}

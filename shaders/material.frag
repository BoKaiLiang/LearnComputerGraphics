#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {

    // Ambient
    vec3 ambient = material.ambient * light.ambient;

    // Diffuse
    vec3 normal_dir = normalize(Normal);
    vec3 lightsrc_dir = normalize(light.position - FragPos);
    float diff = max(dot(normal_dir, lightsrc_dir), 0.0);
    vec3 diffuse = diff * material.diffuse * light.diffuse;

    // Specular
    vec3 view_dir = normalize(viewPos);
    vec3 reflect_dir = reflect(-lightsrc_dir, normal_dir);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * light.specular;

    // Result
    vec3 result = ambient + diff + specular;
    FragColor = vec4(result, 1.0);
}
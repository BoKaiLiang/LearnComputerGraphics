#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cut_off;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {

    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    // Diffuse
    vec3 normal_dir = normalize(Normal);
    vec3 lightsrc_dir = normalize(light.position - FragPos);
    float diff = max(dot(normal_dir, lightsrc_dir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    // Specular
    vec3 view_dir = normalize(viewPos - FragPos);
    vec3 reflect_dir = reflect(-lightsrc_dir, normal_dir);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    // Spotlight soft edge
    float theta = dot(lightsrc_dir, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // Attenuation
    float dist =length(light.position - FragPos);
    float att = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
    ambient *= att;
    diffuse *= att;
    specular *= att;

    // Result
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
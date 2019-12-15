#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 ViewPos;
uniform vec3 ObjColor;
uniform vec3 LightColor;

void main() {
    // Ambient
    float ambient_stren = 0.1;
    vec3 ambient_light = ambient_stren * LightColor;

    // Diffuse
    vec3 normal_dir = normalize(Normal);
    vec3 lightsrc_dir = normalize(LightPos - FragPos);
    float diff = max(dot(normal_dir, lightsrc_dir), 0.0);
    vec3 diffuse_light = diff * LightColor;

    // Specular
    float specular_stren = 0.5;
    vec3 view_dir = normalize(ViewPos - FragPos);
    vec3 reflect_dir = reflect(-lightsrc_dir, normal_dir);
    float spec = pow(max(dot(view_dir, lightsrc_dir), 0.0), 256);
    vec3 specular_light = specular_stren * spec * LightColor;

    // Result
    vec3 PhongShading = (ambient_light + diffuse_light + specular_light) * ObjColor;
    FragColor = vec4(PhongShading, 1.0);
}
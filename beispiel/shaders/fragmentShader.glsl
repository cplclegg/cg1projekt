#version 330 core

struct PointLight {
    vec3 pl_pos;
    vec3 pl_color;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 sl_pos;
    vec3 sl_color;
    vec3 sl_direction;
    float innerAngle;
    float outerAngle;
    float intensity;
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

in vec2 textureCoord;
in vec3 fNormal;
in vec3 FragPos;

uniform sampler2D diffuseMap;
uniform sampler2D diffuseDetailMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D emissiveMap;
uniform samplerCube skybox; // may be needed to environmental reflections

uniform float shininess;
uniform vec3 specularColor;
uniform vec3 diffuseColor;

uniform vec3 viewPos;
uniform int numPointLights;
uniform int numSpotLights;

uniform PointLight[10] pointLights;
uniform SpotLight[2] spotLights;

void main() {
    vec3 norm = normalize(fNormal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < numPointLights; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    gl_FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    float distance = length(light.pl_pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
    vec3 lightDir = normalize(light.pl_pos - fragPos);
    // diff
    float diffuseCoefficient = max (dot( normal, lightDir.xyz ), 0.0);

    // spec
    //vec3 reflectDir = reflect(-lightDir, normal);                                   // phong
    //float specularCoefficient = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // phong
    vec3 halfwayDir = normalize(viewDir + lightDir);                               // blinn-phong
    float specularCoefficient = pow(max(dot(normal, halfwayDir), 0.0), shininess); // blinn-phong

    // calc result
    vec3 ambient = vec3(texture(diffuseMap, textureCoord))
                    * attenuation;
    vec3 diffuse = light.pl_color
                    * diffuseCoefficient
                    * vec3(texture(diffuseMap, textureCoord))
                    * diffuseColor
                    * attenuation;
    vec3 specular = light.pl_color
                    * specularCoefficient
                    * vec3(texture(diffuseMap, textureCoord))
                    * texture(specularMap, textureCoord).r
                    * specularColor
                    * attenuation;
    return (ambient + diffuse + specular);
    //return specular;
}

/*
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

    // diff
    vec3 lightDir = normalize(light.pl_pos - fragPos);
    float distance = length(light.pl_pos - fragPos);
    float reflectionCoefficient = max (dot( normal, lightDir.xyz ), 0.0);
    float diffuseCoefficient = (max(reflectionCoefficient, 0.0)); // this is the one to use
    float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*(distance*distance));

    // spec
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularCoefficient = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // calc result
    vec3 ambient = light.pl_color * vec3(texture(diffuseMap, textureCoord));
    vec3 diffuse = light.pl_color
                        * diffuseCoefficient
                        * vec3(texture(diffuseMap, textureCoord))
                        * diffuseColor
                        * attenuation;
    vec3 specular = light.pl_color
                        * specularCoefficient
                        * vec3(texture(diffuseMap, textureCoord))
                        * texture(specularMap, textureCoord).r
                        * specularColor
                        * attenuation;
    return (ambient + diffuse + specular);
}*/

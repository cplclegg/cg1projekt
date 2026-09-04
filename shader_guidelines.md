# Guidelines for writing shaders compatible with this projects abstractions

## Vertex Shader

The vertex shader must have 3 layout locations declared in order to use
the ObjectData .obj loading:
### Layout in-variables
```glsl
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;
```
This order corresponds to the way object file are read and stored in memory.
### Matrix uniforms
The draw call abstraction expects to upload 4 matrices, 3 of them 4x4 and one 3x3.
The uniform names for these are hardcoded and must be adhered to.
```glsl
uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProj;
uniform mat3 mNormal;
```
### Out-variables
The vertex shader should declare at least 3 out-variables:
```glsl
out vec2 textureCoord;
out vec3 fNormal;
out vec3 FragPos;
// fNormal = mNormal*vNormal;
```
### Required out-variable ``gl_Position``
``gl_Position = mProj * mView * mWorld * vec4(vPosition, 1.0);``

### Example of a complete vertex shader

```glsl
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;

uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProj;
uniform mat3 mNormal;

out vec2 textureCoord;
out vec3 fNormal;
out vec3 FragPos;
void main() {
    FragPos = vec3(mWorld * vec4(vPosition, 1.0));
    textureCoord = vTexCoord;
    fNormal = mNormal * vNormal;
    gl_Position = mProj * mView * mWorld * vec4(vPosition, 1.0);
}
```
## Fragment shader
The fragment shader has several requirements to make it work with the abstractions of this project.
The struct and variable/uniform names used in this documentation are mandatory for now. A better solution is probably out of scope for this project.
### Lighting data

The fragment shader must declare 2 structs for lighting data:

```glsl
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
```
Additionally, it must also declare 2 uniforms for the numbers of lights in the scene:

```glsl
uniform int numPointLights;
uniform int numSpotLights;
```

as well as 2 uniform arrays for storing multiple light casters:

```glsl
uniform PointLight[10] pointLights; // array size may be adjusted
uniform SpotLight[2] spotLights;    // array size may be adjusted
```

### Lighting calculation function
Lighting calculation is abstracted in glsl functions that should be used in the fragment shader:
#### Calculating contribution from point lights
```glsl
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    float distance = length(light.pl_pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*(distance*distance));
    vec3 lightDir = normalize(light.pl_pos - fragPos);
    
    // diff
    float diffuseCoefficient = max (dot( normal, lightDir.xyz ), 0.0);

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
}
```
#### Calculating contribution from spotlights
```glsl
/* 
    tba
*/
```
#### Calculating contribution from directional lights
```glsl
/* 
    tba
*/
```
### The fragment shaders ``void main()``
The fragment shader needs to normalize the fragment normal and calculate the viewing direction as follows:
```glsl
vec3 norm = normalize(fNormal);
vec3 viewDir = normalize(viewPos - FragPos);
```

The sampling of the textures is done by the lighting calculator functions.
To determine the total result in standard cases (no emissive map, normal map or diffuseDetail map used)
the shader initializes a 3d result vector to 0. It then loops over the lighting data arrays,
handing each array index to its corresponding lighting calculator. The results of each iteration of each
lighting data loop is added to the result to make up one final result, that is returned with an added alpha
component of 1.0.

```GLSL
    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < numPointLights; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    for (int j = 0; j < numSpotLights; j++) {
        result += CalcSpotLight(spotLights[j], norm, FragPos, viewDir);
    }
    for (int i = 0; i < numDirLights; i++) {
        result += CalcDirLight(dirLights[i], norm, FragPos, viewDir);
    }
    gl_FragColor = vec4(result, 1.0);
```

So in total the minimal main-function of the fragment shader looks like this:
```glsl
void main() {
    vec3 norm = normalize(fNormal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < numPointLights; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    for (int j = 0; j < numSpotLights; j++) {
        result += CalcSpotLight(spotLights[j], norm, FragPos, viewDir);
    } /* remove comment if dir lights have been implemented 
    for (int i = 0; i < numDirLights; i++) {
        result += CalcDirLight(dirLights[i], norm, FragPos, viewDir);
    } */

    gl_FragColor = vec4(result, 1.0);
}
```

### Texture samplers

The cpu side abstraction layer expects the fragment shader to declare up to 6 samplers.
The first 5 are meant for use with diffuse textures, normal maps, specular maps, and emissive maps.

```glsl
uniform sampler2D diffuseMap; 
uniform sampler2D diffuseDetailMap;
uniform sampler2D normalMap;  
uniform sampler2D specularMap;
uniform sampler2D emissiveMap;
uniform samplerCube skybox;
```

### Texture-related uniforms

The fragment shader declares up to 3 further uniforms to influence lighting and texture. These are set to standard values if not changed in the corresponding Material object.
```glsl
uniform float shininess;
uniform vec3 specularColor;
uniform vec3 diffuseColor;
```

### Mandatory in-variables and uniforms

```glsl
in vec2 textureCoord;
in vec3 fNormal;      // the fragments normal with vertex shaders transformation applied
in vec3 FragPos;      // the fragments position in world space
uniform vec3 viewPos; // the translation vector contained in the inverse view matrix
```

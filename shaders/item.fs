#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;
    vec3 color;
    float ambient;
    float diffuse;
    float specular;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float ambient;
    float diffuse;
    float specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 color;
    vec3 direction;
    float phi;
    float ambient;
    float diffuse;
    float specular;
};

uniform vec3 cameraPos;
uniform Material material;
uniform DirLight dirLight[9];
uniform PointLight pointLight[9];
uniform SpotLight spotLight;

uniform int dirLightAmount;
uniform int pointLightAmount;

vec3 CalculateDirLight(DirLight light,vec3 normal,vec3 cameraDir);
vec3 CalculatePointLight(PointLight light,vec3 normal,vec3 cameraDir);
vec3 CalculateSpotLight(SpotLight light,vec3 normal,vec3 cameraDir);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 cameraDir = normalize(cameraPos - FragPos);
    vec3 result;
    for(int i=0;i<dirLightAmount;i++){
        result += CalculateDirLight(dirLight[i],normal,cameraDir);
    }
    for(int i=0;i<pointLightAmount;i++){
        result += CalculatePointLight(pointLight[i],normal,cameraDir);
    }
    result += CalculateSpotLight(spotLight,normal,cameraDir);
    FragColor = vec4(result, 1.0);
}

vec3 CalculateDirLight(DirLight light,vec3 normal,vec3 cameraDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord)) * light.color;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) * light.color;
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord)) * light.color;
    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light,vec3 normal,vec3 cameraDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord)) * light.color;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) * light.color;
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord)) * light.color;
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*(distance*distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light,vec3 normal,vec3 cameraDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    float cosPhi = cos(light.phi);
    float cosTheta = dot(light.direction,normalize(lightDir));
    if(cosTheta > cosPhi){
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
        vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord)) * light.color;
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) * light.color;
        vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord)) * light.color;
        return ambient+diffuse+specular;
    }else{
        vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord)) * light.color;
        return ambient;
    }
}
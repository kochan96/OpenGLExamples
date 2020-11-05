#version 440 core
out vec4 color;

struct Material {
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};

struct DirLight {
    vec3 Direction;
	
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct PointLight {
    vec3 Position;
    
    bool EnableAttenuation;
    float Constant;
    float Linear;
    float Quadratic;
	
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct SpotLight {
    vec3 Position;
    vec3 Direction;
    float CutOff;
    float OuterCutOff;

    bool EnableAttenuation;
    float Constant;
    float Linear;
    float Quadratic;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;       
};

#define NR_POINT_LIGHTS  4

in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TextureCoord;

uniform vec3 u_ViewPos;
uniform DirLight u_DirLight;

uniform int u_PointLightsCount;
uniform PointLight u_PointLights[NR_POINT_LIGHTS];

uniform SpotLight u_SpotLight;
uniform Material u_Material;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

float CalculateAttenuation(vec3 lightPosition, float constant, float linear, float quadratic);
vec3 CalcualteAmbient(vec3 ambientLight);
vec4 CalculateDiffuse(vec3 diffuseLight, vec3 normal, vec3 lightDir);
vec3 CalculateSpecular(vec3 specularLight, vec3 normal, vec3 lightDir, vec3 viewDir);

void main()
{
	vec3 normal = normalize(v_Normal);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 result = vec3(0.0f);

    result += CalculateDirLight(u_DirLight,normal,viewDir);

    for(int i = 0; i < u_PointLightsCount && i < NR_POINT_LIGHTS; i++) {
        result += CalculatePointLight(u_PointLights[i], normal, v_FragPos, viewDir);
    }

    result += CalculateSpotLight(u_SpotLight, normal, v_FragPos, viewDir);

    color = vec4(result, 1.0f);
    
};


vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.Direction);
    
    vec3 ambient = CalcualteAmbient(light.Ambient);
    vec4 diffuse = CalculateDiffuse(light.Diffuse, normal, lightDir);
    vec3 specular  = vec3(0.0f);
    if(diffuse.w  > 0.0f)
        specular = CalculateSpecular(light.Specular, normal, lightDir, viewDir);

    return ambient + vec3(diffuse) + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.Position - fragPos);
    
    vec3 ambient = CalcualteAmbient(light.Ambient);
    vec4 diffuse = CalculateDiffuse(light.Diffuse, normal, lightDir);
    vec3 specular  = vec3(0.0f);
    if(diffuse.w  > 0.0f)
        specular = CalculateSpecular(light.Specular, normal, lightDir, viewDir);
    
    if(light.EnableAttenuation)
    {
        float attenuation = CalculateAttenuation(light.Position, light.Constant,light.Linear, light.Quadratic);
        ambient*= attenuation;
        diffuse*= attenuation;
        specular*= attenuation;
    }

    return ambient + vec3(diffuse) + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.Position - fragPos);

    vec3 ambient = CalcualteAmbient(light.Ambient);
    vec4 diffuse = CalculateDiffuse(light.Diffuse, normal, lightDir);
    vec3 specular = CalculateSpecular(light.Specular, normal, lightDir, viewDir);

    float theta = dot(lightDir, normalize(-light.Direction));
    // Calculate the outer cone difference
    float epsilon   = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    if(light.EnableAttenuation)
    {
        float attenuation = CalculateAttenuation(light.Position, light.Constant,light.Linear, light.Quadratic);
        ambient*= attenuation;
        diffuse*=attenuation;
        specular*= attenuation;
    }

    diffuse *= intensity;
    specular *= intensity;

    return ambient + vec3(diffuse) + specular;
}

float CalculateAttenuation(vec3 lightPosition, float constant, float linear, float quadratic) {
    float distanceTo    = length(lightPosition - v_FragPos);
    float attenuation = 1.0f / ((constant) + (linear * distanceTo) + (quadratic * (distanceTo* distanceTo)));

    return attenuation;
}

vec3 CalcualteAmbient(vec3 ambientLight) {
    return vec3(texture(u_Material.Diffuse, v_TextureCoord)) * ambientLight;
}

vec4 CalculateDiffuse(vec3 diffuseLight, vec3 normal, vec3 lightDir) {
    float diffuseFactor = dot(normal,lightDir);

    vec3 diffuseObject = vec3(texture(u_Material.Diffuse,v_TextureCoord));
    vec3 diffuse = max(diffuseFactor,0.0f) * diffuseObject * diffuseLight;

    return vec4(diffuse, diffuseFactor);
}

vec3 CalculateSpecular(vec3 specularLight, vec3 normal, vec3 lightDir, vec3 viewDir) {

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float specularFactor = pow(max(dot(normal, halfwayDir), 0.0), u_Material.Shininess);
    vec3 specularObject = vec3(texture(u_Material.Specular, v_TextureCoord));

    return specularFactor * specularLight * specularObject;
}

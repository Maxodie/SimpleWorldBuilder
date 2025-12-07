###custom
sampler2D uMaterial.albedoMapID AlbedoTexture;
vec4 uMaterial.albedoColor AlbedoColor;

sampler2D uMaterial.metallicMapID MetallicTexture;
float uMaterial.metallicPercentage Metallic;

sampler2D uMaterial.roughnessMapID RoughnessTexture;
float uMaterial.roughnessPercentage Roughness;

sampler2D uMaterial.ambiantOcclusionMapID OcclusionTexture;


###fragment
#version 410 core

layout (location = 0) out vec4 FragColor;

in vec3 iNormal;
in vec3 iWorldPos;
in vec2 iTexCoords;

struct Material
{
    float albedoMapID;
    vec4 albedoColor;

    float metallicMapID;
    float metallicPercentage;

    float roughnessMapID;
    float roughnessPercentage;

    float ambiantOcclusionMapID;
};

struct Light
{
    vec3 position;
    vec4 color;
};

uniform Material uMaterial;
uniform vec3 uCamPos;

#define MAX_LIGHT_COUNT 10
uniform Light uLights[MAX_LIGHT_COUNT];
uniform int uLightCount;

uniform sampler2D Textures[32]; //cap


float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
const float PI = 3.14159265359;

void main()
{
    // FragColor = texture(Textures[int(round(uMaterial.albedoMapID))], iTexCoords) * uMaterial.albedoColor;
    // vec3 albedo     = pow(texture(Textures[int(round(uMaterial.albedoMapID))], iTexCoords).rgb, 2.2);
    // vec3 albedo     = texture(Textures[1], iTexCoords).rgb * vec3(uMaterial.albedoColor);
    vec3 albedo     = texture(Textures[int(round(uMaterial.albedoMapID))], iTexCoords).rgb * vec3(uMaterial.albedoColor);
    // vec3 normal     = getNormalFromNormalMap();
    float metallic  = texture(Textures[int(round(uMaterial.metallicMapID))], iTexCoords).r * uMaterial.metallicPercentage;
    float roughness = texture(Textures[int(round(uMaterial.roughnessMapID))], iTexCoords).r * uMaterial.roughnessPercentage;
    float ao        = texture(Textures[int(round(uMaterial.ambiantOcclusionMapID))], iTexCoords).r;

    vec3 N = normalize(iNormal);
    vec3 V = normalize(uCamPos - iWorldPos);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < uLightCount; ++i)
    {
        // calculate per-light radiance
        vec3 L = normalize(uLights[i].position - iWorldPos);
        vec3 H = normalize(V + L);
        float distance    = length(uLights[i].position - iWorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = vec3(uLights[i].color) * attenuation;

        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, roughness);
        float G   = GeometrySmith(N, V, L, roughness);
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;

        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)) * uLightCount;

    FragColor = vec4(color, 1.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

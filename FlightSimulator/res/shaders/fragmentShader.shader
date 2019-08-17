#version 330 core

out vec4 fragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Pointlight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constantValue;
	float linearValue;
	float quadraticValue;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constantValue;
	float linearValue;
	float quadraticValue;
};

struct NumberOfLights {
	int numberOfPointLights;
	int numberOfSpotLights;
};

in vec3 fragPos;
in vec2 fragTextureCoords;
in vec3 fragNormals;
in vec3 camaraPosition;

uniform Material material;
uniform NumberOfLights numberOfLights;
uniform Pointlight pointLight[20];
uniform SpotLight spotLight[20];
uniform DirectionalLight directionalLight;

vec3 calculateDirectionalLight(DirectionalLight directionalLight) {
	vec3 ambient = directionalLight.ambient * texture(material.diffuse, fragTextureCoords).rgb;

	vec3 lightDir = normalize(-directionalLight.direction);
	vec3 norm = normalize(fragNormals);
	float diff = max(dot(lightDir, norm),0.0f);
	vec3 diffuse = directionalLight.diffuse * diff * texture(material.diffuse, fragTextureCoords).rgb;

	vec3 toCamaraVector = normalize(camaraPosition - fragPos);
	vec3 reflectedLight = reflect(-lightDir, norm);
	float spec = pow(max(dot(toCamaraVector, reflectedLight),0.0f),material.shininess);
	vec3 specular = directionalLight.specular * spec * texture(material.specular, fragTextureCoords).rgb;

	return ambient + diffuse + specular;
}
vec3 calculatePointLight(Pointlight pointLight) {
	vec3 ambient = pointLight.ambient * texture(material.diffuse, fragTextureCoords).rgb;

	vec3 norm = normalize(fragNormals);
	vec3 lightDir = normalize(pointLight.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = pointLight.diffuse * diff * texture(material.diffuse, fragTextureCoords).rgb;

	vec3 toCamaraVector = normalize(camaraPosition - fragPos);
	vec3 reflectedLight = reflect(-lightDir, norm);
	float spec = pow(max(dot(toCamaraVector, reflectedLight), 0.0f), material.shininess);
	vec3 specular = pointLight.specular * spec * texture(material.specular, fragTextureCoords).rgb;

	float distance = length(pointLight.position - fragPos);
	float attenuation = 1.0 / (pointLight.constantValue + pointLight.linearValue * distance + pointLight.quadraticValue * distance * distance);
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}
vec3 calculateSpotLight(SpotLight spotLight) {

	vec3 ambient = spotLight.ambient * texture(material.diffuse, fragTextureCoords).rgb;

	vec3 norm = normalize(fragNormals);
	vec3 lightDir = normalize(spotLight.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, fragTextureCoords).rgb;

	vec3 toCamaraVector = normalize(camaraPosition - fragPos);
	vec3 reflectedLight = reflect(-lightDir, norm);
	float spec = pow(max(dot(toCamaraVector, reflectedLight), 0.0), material.shininess);
	vec3 specular = spotLight.specular * spec * texture(material.specular, fragTextureCoords).rgb;
		
	float theta = dot(normalize(spotLight.direction), normalize(fragPos - spotLight.position));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(spotLight.position - fragPos);
	float attenuation = 1.0 / (spotLight.constantValue + spotLight.linearValue * distance + spotLight.quadraticValue * distance * distance);
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

void main() {
	vec3 emission = texture(material.emission, fragTextureCoords).rgb;

	vec3 result = calculateDirectionalLight(directionalLight);

	for (int i = 0; i < numberOfLights.numberOfPointLights; i++) {
		result += calculatePointLight(pointLight[i]);
	}

	for (int i = 0; i < numberOfLights.numberOfSpotLights; i++) {
		result += calculateSpotLight(spotLight[i]);
	}

	result += emission;
	fragColor = vec4(result, 1.0f);
}
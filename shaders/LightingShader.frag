#version 330 core
in vec3 Normals;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D ourTexture;

void main()
{

	//Difuse lighting
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//Specular lighting
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	//Ambient lighting
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse + specular);

	FragColor = vec4(texture(ourTexture, TexCoord).rgb * result, 1.0);
}

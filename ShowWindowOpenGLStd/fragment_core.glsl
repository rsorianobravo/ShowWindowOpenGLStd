#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;	
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

// Uniforms

uniform Material material;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightPos0;

uniform vec3 cameraPos;


// Functions

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 posToLightDirVec = normalize(vs_position - lightPos0);
	vec3 diffuseColor = vec3(1.f,1.f,1.f);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;
	
	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos)
{
	vec3 lightToPosDirVec  = normalize(lightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - cameraPos);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 70);
	vec3 specularFinal = material.specular * specularConstant;

	return specularFinal;
}

void main()
{
	//fs_color = vec4(vs_color, 1.0f);
	//fs_color = /*texture(texture0, vs_texcoord) * */ texture(texture1, vs_texcoord) * vec4(vs_color, 1.0f);

	// Ambient Light
	//vec3 ambientLight= vec3(0.1f,0.f,0.f);
	//vec3 ambientLight= material.ambient;
	vec3 ambientFinal= calculateAmbient(material);


	// Diffuse Light
	/*
	vec3 posToLightDirVec = normalize(vs_position - lightPos0);
	vec3 diffuseColor = vec3(1.f,1.f,1.f);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	//vec3 diffuseFinal = diffuseColor * diffuse;
	vec3 diffuseFinal = material.diffuse * diffuse;
	*/

	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);


	//Specular Light
	/*
	vec3 lightToPosDirVec  = normalize(lightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - cameraPos);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 70);
	//vec3 specularFinal = vec3(1.f, 1.f, 1.f) * specularConstant;
	vec3 specularFinal = material.specular * specularConstant;
	*/

	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);


	//Attenuation 

	/*
	fs_color = texture(material.diffuseTex, vs_texcoord) 
		* vec4(vs_color, 1.0f)
		* (vec4(ambientLight,1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f))
	;
	*/

		fs_color = texture(material.diffuseTex, vs_texcoord) 
		* vec4(vs_color, 1.0f)
		* (vec4(ambientFinal,1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f))
	;
}
 
#version 430 core
#define MAX_LIGHT 203

in vec4 vPosEye;//eye space ÁÂÇ¥
in vec3	vNormal;//normal transformation Àû¿ëÇÑ normal vector
out vec4 fColor;

uniform mat4	MV;
uniform mat4	MV_L;
uniform mat4	V;
uniform mat3	matNormal;
uniform int Max_Light;

struct TMaterial
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	vec3	emission;
	float	shininess;
};
struct TLight
{
	vec3	position[MAX_LIGHT];
	vec3	ambient[MAX_LIGHT];
	vec3	diffuse[MAX_LIGHT];
	vec3	specular[MAX_LIGHT];
	uint	On[MAX_LIGHT];
};
uniform TMaterial	material;
uniform TLight		light;

const float k0 = 1.0; //constant attenuation
const float k1 = 1.5; //linear attenuation
const float k2 = 2.0; //quadratic attenuation

void main()
{
	fColor = vec4(0.0);
	
	
	for(int i=0;i<Max_Light;i++)
	{
	if(light.On[i] ==uint(0))
		continue;
	vec3 n = normalize(vNormal);
	vec3 vEyeSpaceLightPosition = (MV_L*vec4(light.position[i],1)).xyz;
	vec3 L = (vEyeSpaceLightPosition-vPosEye.xyz);//±¤¿ø¹æÇâÀÇ º¤ÅÍ
	float d =length(L);
	L = normalize(L);
	
	vec3	v = normalize(-vPosEye.xyz);
	vec3	h = normalize(L + v);
	float	l_dot_n = max(dot(L, n), 0.0);

	float attenuationAmount = 1.0/(k0 + (k1*d) + (k2*d*d));
	vec3 ambient = material.ambient*light.ambient[i];
	vec3 diffuse = material.diffuse*max(0,dot(vNormal.xyz,L))*light.diffuse[i];
	diffuse *= attenuationAmount;
	vec3 specular = vec3(0.0);
	if(l_dot_n > 0.0)
	{
		specular = light.specular[i] * material.specular * pow(max(dot(h, n), 0.0), material.shininess);
	}


	fColor += vec4(ambient + diffuse + specular, 1);

	}			
}					
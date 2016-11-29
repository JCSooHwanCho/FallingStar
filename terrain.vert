#version 430 core
layout(location = 0) in float x;
layout(location = 1) in float y;
layout(location = 2) in float z;
layout(location = 3) in float nx;
layout(location = 4) in float ny;
layout(location = 5) in float nz;
uniform mat4	MVP;
uniform mat4	MV;
uniform mat3	matNormal;
out vec3	vNormal;
out vec4	vPosEye;
void main()
{
	vec4 aPosition = vec4(x,y,z,1);
	vec3 aNormal = vec3(nx,ny,nz);
	
	vPosEye = MV*aPosition;//Model-View를 적용함. Eye Space에서의 좌표
	vNormal = normalize(matNormal*aNormal);//normal transformation을 적용한 normal vector를 normalize함
	gl_Position = MVP*aPosition;//Projection까지 적용하여 실제로 그려지는 좌표
}
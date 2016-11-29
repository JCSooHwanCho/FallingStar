#version 430 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in float aPointSize;
layout(location = 3) in uint On;
layout(location = 4) in uint Selected;
out vec4 vColor;
uniform mat4	MVP;
void main()
{
	
	gl_Position = MVP*vec4(aPosition,1);
	if(On==1)
	{	
		gl_PointSize = aPointSize;
	}
	else if(On==0&&Selected==1)
	{
		gl_PointSize = aPointSize;
	}
	else
	{
		gl_PointSize = 0.0;
	}

	vColor = vec4(aColor,1);	
}

// simple toon vertex shader
// www.lighthouse3d.com


varying vec3 normal, lightDir;
varying vec4 color;
varying vec2 texture_coordinate;

void main()
{	
	lightDir = normalize(vec3(1.0,1.0,3.0));
	normal = gl_NormalMatrix * gl_Normal;
	//normal = normalize(gl_Normal);
	gl_Position = ftransform();
	color = gl_Color;
	texture_coordinate = vec2(gl_MultiTexCoord0);
}


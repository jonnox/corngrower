// simple toon fragment shader
// www.lighthouse3d.com

varying vec3 normal, lightDir;
varying vec4 color;
varying vec2 texture_coordinate; uniform sampler2D my_color_texture;
//uniform sampler2D normal_texture;

void main()
{
	float intensity;
	vec3 n;
	vec4 colorB;
	vec4 texcolor;
	int rnd;
	float i,r,g,b;

	n = normalize(normal);
	
	//vec3 n = normalize(texture2D(normal_texture, gl_TexCoord[0].st).rgb * 2.0 - 1.0);

	r = 153.0f / 255.0f;
	g = 102.0f / 255.0f;
	b = 51.0f / 255.0f;
	
	i = max(dot(lightDir,n),0.1);
	
	colorB = vec4(color.x*i + 0.01,color.y*i + 0.08,color.z*i + 0.01,1.0);
	texcolor = texture2D(my_color_texture, texture_coordinate);
	
	gl_FragColor = colorB;
	if(color.x == 0.0 && color.y == 0.0 && color.z == 0.0){
		gl_FragColor = texcolor;
	}
}


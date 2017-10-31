#version 400

in vec4 position;
in vec4 color;
in vec3 normal;

out vec4 frag_colour;

uniform vec4 light1;
uniform vec4 light2;
uniform vec4 light3;

uniform float light1_int;
uniform float light2_int;
uniform float light3_int;


uniform mat4 viewMatrix;
uniform sampler2D utexture;
in vec2 tex;

void main () 
{
	// Defining Materials
	vec4 diffuse = vec4(0.3, 0.3, 0.3, 1.0); 
	vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
	float shininess = 5.0;

	vec4 spec = vec4(0.0);

	vec3 lightDir[3];
	float dotProduct[3];
	float intensity[3];
	
	lightDir[0] = normalize(vec3(light1 - position)); 
	lightDir[1] = normalize(vec3(light2 - position)); 
	lightDir[2] = normalize(vec3(light3 - position)); 

	vec3 n = normalize(vec3(normal));

	for( int i = 0; i < 3; i++){
		dotProduct[i] = dot(n, lightDir[i]);
		intensity[i] =  max(dotProduct[i], 0.0);
	}

	intensity[2] = max(0.0, dot(vec3(0.0, -1.0, 0.0), -lightDir[2]) - 0.9);

	vec4 amb_int;
	vec4 spec_int;
	vec4 diff_int;

	vec3 eye = normalize( vec3(0.0, 0.0, 1.0) );
	
	for( int i = 0; i < 3; i++){
		if(intensity[i] > 0.0) {
			vec3 h = normalize(lightDir[i] - eye);
			float intSpec = max(dot(h,n), 0.0);	
			// spec += pow(intSpec, shininess);
		}
	} 

	amb_int = ambient * (light1_int + light2_int + light3_int);
	diff_int = diffuse * (intensity[0] * light1_int + intensity[1] * light2_int + intensity[2] * light3_int);
	spec_int = specular * spec;
	
	// Compute specular component only if light falls on vertex
	if (tex[0] < 0.0) {
		frag_colour = max((diff_int + spec_int), amb_int) * color; // All
	}
	else {
		frag_colour = max((diff_int + spec_int), amb_int) * texture(utexture, tex); // All
	}
}

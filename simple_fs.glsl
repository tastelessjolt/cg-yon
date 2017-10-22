#version 400

in vec4 position;
in vec4 color;
in vec3 normal;

out vec4 frag_colour;

uniform vec4 lights;
uniform mat4 viewMatrix;

void main () 
{
	// Defining Materials
	vec4 diffuse = vec4(0.3, 0.0, 0.0, 1.0); 
	vec4 ambient = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 specular = vec4(0.2, 1.0, 0.5, 1.0);
	float shininess = 5.0;
	vec4 spec = vec4(0.0); 
	
	// vec3 lightDir = vec3(viewMatrix * (lights[0])); 
	vec3 lightDir = vec3(lights - position); 
	lightDir = normalize(lightDir);

	vec3 n = normalize(vec3(normal));   
	float dotProduct = dot(n, lightDir);
	float intensity =  max(dotProduct, 0.0);

	// Compute specular component only if light falls on vertex
	if(intensity > 0.0)
	{
		vec3 eye = normalize( vec3(0.0, 0.0, 1.0) );
		vec3 h = normalize(lightDir - eye);
		float intSpec = max(dot(h,n), 0.0);	
		spec = specular * pow(intSpec, shininess);
	}  	

	frag_colour = max((intensity * diffuse  + spec) * color, ambient); // All
}

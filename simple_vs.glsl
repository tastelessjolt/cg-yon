#version 400

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform mat3 normalMatrix;
uniform mat4 uModelViewMatrix;

out vec4 position;
out vec4 color;
out vec3 normal;

void main () 
{
	gl_Position = uModelViewMatrix * vPosition;
	normal = (normalMatrix * normalize(vNormal));
	position = gl_Position;
	color = vColor;
}

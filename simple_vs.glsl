#version 410

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;
in vec2 textCoord;

uniform mat3 normalMatrix;
uniform mat4 vViewMatrix;
uniform mat4 uModelMatrix;

out vec4 position;
out vec4 color;
out vec3 normal;
out vec2 tex;
void main () 
{
	gl_Position = vViewMatrix * uModelMatrix * vPosition;
	normal = (normalMatrix * normalize(vNormal));
	position = uModelMatrix * vPosition;
	color = vColor;
	tex = textCoord;
}

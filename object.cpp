#include "object.hpp"

extern GLuint vPosition;
extern GLuint vColor;
extern GLuint vNormal;
extern GLuint uModelViewMatrix;
extern GLuint normalMatrix;

BaseObject::BaseObject() {

}

Object::Object(){

}

Primitive::Primitive() {

}

Sphere::Sphere() {
	method = GL_TRIANGLE_STRIP;
	tesselation = 50;
}

Cylinder::Cylinder() {
	tesselation = 50;
}

Cube::Cube() {
	tesselation = 50;
}


void Object::init() {
	for (BaseObject* bo : children) {
		bo->init();
	}
}

void Primitive::init() {
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, &vbo);
}

void Object::generate() {
	for (BaseObject* bo : children) {
		bo->generate();
	}
}

void Primitive::generate() {

}

void Sphere::generate() {
	GLdouble radius = 1.0f;
	GLfloat lats, longs;

	GLfloat slices=(180/(GLfloat(tesselation)*10))/2;
	GLfloat sectors=(180/(GLfloat(tesselation)*10))/2;

	GLfloat l;
	for (lats = 0.0; lats <= PI; lats+=sectors) {
		for(longs = 0.0; longs <= 2.0*PI; longs+=slices){
			GLfloat x = radius * sin(lats) * cos(longs);
			GLfloat y = radius * sin(lats) * sin(longs);
			GLfloat z = radius * cos(lats);
			glm::vec4 pt(x, y, z, 1.0);

			colors.push_back(white); vertices.push_back(pt); 
			normals.push_back(pt);

			if(lats+sectors>PI)
				l=PI;
			else
				l=lats+sectors;

			x = radius * sin(l) * cos(longs);
			y = radius * sin(l) * sin(longs);
			z = radius * cos(l);
			pt =glm::vec4(x, y, z, 1.0);
			colors.push_back(white); vertices.push_back(pt); 
			normals.push_back(pt); 


		}
	}

	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);

	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) *(vertices.size() + colors.size() + normals.size()), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0] );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) *(vertices.size()), sizeof(GLfloat) *(colors.size()), &colors[0] );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) *(vertices.size() + colors.size()), sizeof(GLfloat) * (normals.size()), &normals[0] );

	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(GLfloat) *(vertices.size())));

	glEnableVertexAttribArray( vNormal );
	glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(GLfloat) *(vertices.size() + colors.size())) );

}


void Cylinder::generate() {

}

void Cube::generate() {
	
}

void Object::render() {
	render(glm::mat4(1.0f));
}

void Object::render(glm::mat4 transform) {
	for (glm::mat4* tr: transforms) {
		transform = transform * *tr;
	}
	for (BaseObject *bo : children) {
		bo->render(transform);
	}
}

void Primitive::render(glm::mat4 transform) {
	glBindVertexArray (vao);

	glm::mat4 model_matrix;

	glm::mat4 modelview_matrix = transform * model_matrix;
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
	glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
	

	glDrawArrays(method, 0, vertices.size());
}



















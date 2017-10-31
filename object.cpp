#include "object.hpp"
#include "texture.hpp"

extern GLuint vPosition;
extern GLuint vColor;
extern GLuint vNormal;
extern GLuint textCoord;

extern GLuint uModelViewMatrix;
extern GLuint normalMatrix;
extern GLuint viewMatrix;
extern GLuint uLights;
extern GLuint texture;


#define red glm::vec4(1.0, 0.0, 0.0, 1.0)
#define blue glm::vec4(0.0, 0.0, 1.0, 1.0)
#define grey glm::vec4(0.6, 0.6, 0.6, 1.0)
#define white glm::vec4(1.0, 1.0, 1.0, 1.0)

double PI = 3.14159265;

BaseObject::BaseObject() {

}

Object::Object(){

}

void Object::init() {
	for (BaseObject* bo : children) {
		bo->init();
	}
}

void Object::generate() {
	for (BaseObject* bo : children) {
		bo->generate();
	}
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

Primitive::Primitive() {
	tex = -1;
	texture_filename = "";
}

void Primitive::init() {
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, &vbo);
}

void Primitive::generate() {
	loadpoints();
	if (texture_filename == "") {
		texs.clear();
		for (int i = 0; i != vertices.size(); i++) 
			texs.push_back(glm::vec2(-1.0, 0.0));
	}

	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);

	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec4) * (vertices.size() + colors.size()) + sizeof(glm::vec3) * (normals.size()) + sizeof(glm::vec2) * (texs.size()), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * vertices.size(), &vertices[0] );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices.size(), sizeof(glm::vec4) * colors.size(), &colors[0] );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec4) *(vertices.size() + colors.size()), sizeof(glm::vec3) * (normals.size()), &normals[0] );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec4) *(vertices.size() + colors.size()) + sizeof(glm::vec3) * (normals.size()), sizeof(glm::vec2) * (texs.size()), &texs[0] );

	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4) *(vertices.size())));

	glEnableVertexAttribArray( vNormal );
	glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4) *(vertices.size() + colors.size())) );

	glEnableVertexAttribArray( textCoord );
	glVertexAttribPointer( textCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4) *(vertices.size() + colors.size()) + sizeof(glm::vec3) * (normals.size())) );

	if (texture_filename != "") {
		// Load Textures 
		tex=LoadTexture(texture_filename.c_str(), tex_width, tex_height);
		// glBindTexture(GL_TEXTURE_2D, tex);
	}
}

void Primitive::render() {
	render(glm::mat4(1.0f));
}

void Primitive::render(glm::mat4 transform) {

	for (glm::mat4* tr: transforms) {
		transform = transform * *tr;
	}

	glm::mat4 model_matrix = glm::mat4(1.0f);

	glm::mat4 modelview_matrix = transform * model_matrix;
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
	glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

	glBindVertexArray (vao);
	if (tex != -1)
		glBindTexture(GL_TEXTURE_2D, tex);

	glDrawArrays(method, 0, vertices.size());
}

void Primitive::settexture(std::string filename, int tex_width, int tex_height) {
	this->texture_filename = filename;
	this->tex_width = tex_width;
	this->tex_height = tex_height;
}

Sphere::Sphere() {
	method = GL_TRIANGLE_STRIP;
	tesselation = 50;

	lat_start = 0.0;
	long_start = 0.0;

	lat_angle = PI;
	long_angle = 2 * PI;

	closed = 0;
}

Sphere::Sphere(GLfloat lat_start, GLfloat lat_angle, GLfloat long_start, GLfloat long_angle) {
	method = GL_TRIANGLE_STRIP;
	tesselation = 50;

	this->lat_start = lat_start;
	this->lat_angle = lat_angle;
	
	this->long_start = long_start;
	this->long_angle = long_angle;

	closed = 1;
}

void Sphere::loadpoints() {
	GLdouble radius = 0.5f;
	GLfloat lats, longs;

	GLfloat slices=(180/(GLfloat(tesselation)*10))/2;
	GLfloat sectors=(180/(GLfloat(tesselation)*10))/2;

	GLfloat l;
	for (lats = lat_start; lats <= lat_start + lat_angle; lats+=sectors) {
		for(longs = long_start; longs <= long_start + long_angle; longs+=slices){
			GLfloat x = radius * sin(lats) * cos(longs);
			GLfloat y = radius * sin(lats) * sin(longs);
			GLfloat z = radius * cos(lats);
			glm::vec4 pt(x, y, z, 1.0);

			colors.push_back(red); vertices.push_back(pt); 
			normals.push_back(glm::vec3(pt)); texs.push_back(glm::vec2(longs/(2 * PI), lats/(PI)));

			if(lats+sectors > lat_start + lat_angle)
				l=lat_start + lat_angle;
			else
				l=lats+sectors;

			x = radius * sin(l) * cos(longs);
			y = radius * sin(l) * sin(longs);
			z = radius * cos(l);
			pt =glm::vec4(x, y, z, 1.0);

			colors.push_back(red); vertices.push_back(pt); 
			normals.push_back(glm::vec3(pt)); texs.push_back(glm::vec2(longs/(2 * PI), lats/(PI))); 
		}
	}

	// if (closed) {
	// 	printf("Generating closing?\n");
	// 	for (lats = lat_start; lats <= lat_start + lat_angle; lats += lat_angle){
	// 		for (longs = long_start; longs <= long_start + long_angle; longs+= 2 * slices) {
	// 			glm::vec4 pt(0.0, 0.0, 0.0, 1.0);
	// 			colors.push_back(red); vertices.push_back(pt); 
	// 			normals.push_back(glm::vec3(pt));

	// 			GLfloat x = radius * sin(lats) * cos(longs);
	// 			GLfloat y = radius * sin(lats) * sin(longs);
	// 			GLfloat z = radius * cos(lats);
	// 			pt = glm::vec4(x, y, z, 1.0);

	// 			colors.push_back(red); vertices.push_back(pt); 
	// 			normals.push_back(glm::vec3(pt));

	// 			if(longs + slices > long_start + long_angle)
	// 				l=long_start + long_angle;
	// 			else
	// 				l=longs+slices;

	// 			x = radius * sin(lats) * cos(l);
	// 			y = radius * sin(lats) * sin(l);
	// 			z = radius * cos(lats);
	// 			pt =glm::vec4(x, y, z, 1.0);

	// 			colors.push_back(red); vertices.push_back(pt); 
	// 			normals.push_back(glm::vec3(pt)); 

	// 			pt = glm::vec4(0.0, 0.0, 0.0, 1.0);
	// 			colors.push_back(red); vertices.push_back(pt); 
	// 			normals.push_back(glm::vec3(pt));
	// 		}
	// 	}
	// }
}

Cylinder::Cylinder() {
	tesselation = 50;
	method = GL_TRIANGLES;
}

void Cylinder::loadpoints() {

	GLfloat sectors= 2*PI/tesselation;
	GLdouble radius = 0.5f;

	GLfloat top = 0.5f;
	GLfloat bottom = -0.5f;

	GLfloat l;
	glm::vec4 topa(0, 0, top, 1.0);
	glm::vec4 bota(0, 0, bottom, 1.0);
	for (GLfloat lats = 0.0; lats <= 2*PI; lats=lats+sectors)
	{
		GLfloat x = radius * cos(lats);
		GLfloat y = radius * sin(lats);

		glm::vec4 topc(x, y, top, 1.0);
		glm::vec4 botc(x, y, bottom, 1.0);

		if(lats+sectors>2*PI)
			l=2*PI;
		else
			l=lats+sectors;

		x = radius * cos(l);
		y = radius * sin(l);

		glm::vec4 topcn(x, y, top, 1.0);
		glm::vec4 botcn(x, y, bottom, 1.0);

		vertices.push_back(topa); normals.push_back(glm::vec3(topa)); colors.push_back(blue); texs.push_back(glm::vec2(0.0, top + 0.5)); 
		vertices.push_back(topc); normals.push_back(glm::vec3(topc)); colors.push_back(blue); texs.push_back(glm::vec2(0.0, top + 0.5)); 
		vertices.push_back(topcn); normals.push_back(glm::vec3(topcn)); colors.push_back(blue); texs.push_back(glm::vec2(0.0, top + 0.5)); 

		vertices.push_back(topcn); normals.push_back(glm::vec3(topcn)); colors.push_back(blue); texs.push_back(glm::vec2((l)/(2*PI), top + 0.5)); 
		vertices.push_back(topc); normals.push_back(glm::vec3(topc)); colors.push_back(blue); texs.push_back(glm::vec2((lats)/(2*PI), top + 0.5)); 
		vertices.push_back(botc); normals.push_back(glm::vec3(botc)); colors.push_back(blue); texs.push_back(glm::vec2((lats)/(2*PI), bottom + 0.5)); 
		
		vertices.push_back(topcn); normals.push_back(glm::vec3(topcn)); colors.push_back(blue); texs.push_back(glm::vec2((l)/(2*PI), top + 0.5)); 
		vertices.push_back(botc); normals.push_back(glm::vec3(botc)); colors.push_back(blue); texs.push_back(glm::vec2((lats)/(2*PI), bottom + 0.5)); 
		vertices.push_back(botcn); normals.push_back(glm::vec3(botcn)); colors.push_back(blue); texs.push_back(glm::vec2((l)/(2*PI), bottom + 0.5)); 
		
		vertices.push_back(botcn); normals.push_back(glm::vec3(botcn)); colors.push_back(blue); texs.push_back(glm::vec2(0.0, bottom + 0.5)); 
		vertices.push_back(botc); normals.push_back(glm::vec3(botc)); colors.push_back(blue); texs.push_back(glm::vec2(0.0, bottom + 0.5)); 
		vertices.push_back(bota); normals.push_back(glm::vec3(bota)); colors.push_back(blue); texs.push_back(glm::vec2(0.0, bottom + 0.5)); 
		
	}

}

Cube::Cube() {
	method = GL_TRIANGLES;
}

// quad generates two triangles for each face and assigns colors to the vertices
void Cube::quad(int a, int b, int c, int d)
{
  colors.push_back(red); vertices.push_back(positions[a]); normals.push_back(glm::vec3(positions[a])); texs.push_back(glm::vec2(0.0, 0.0));
  colors.push_back(red); vertices.push_back(positions[b]); normals.push_back(glm::vec3(positions[b])); texs.push_back(glm::vec2(1.0, 0.0));
  colors.push_back(red); vertices.push_back(positions[c]); normals.push_back(glm::vec3(positions[c])); texs.push_back(glm::vec2(1.0, 1.0));
  colors.push_back(red); vertices.push_back(positions[a]); normals.push_back(glm::vec3(positions[a])); texs.push_back(glm::vec2(0.0, 0.0));
  colors.push_back(red); vertices.push_back(positions[c]); normals.push_back(glm::vec3(positions[c])); texs.push_back(glm::vec2(1.0, 1.0));
  colors.push_back(red); vertices.push_back(positions[d]); normals.push_back(glm::vec3(positions[d])); texs.push_back(glm::vec2(0.0, 1.0));
 }

// generate 12 triangles: 36 vertices and 36 colors
void Cube::colorcube(void)
{
    quad( 0, 3, 2, 1 );
    quad( 3, 7, 6, 2 );
    quad( 0, 4, 7, 3 );
    quad( 5, 1, 2, 6 );
    quad( 5, 6, 7, 4 );
    quad( 4, 0, 1, 5 );


}

void Cube::loadpoints() {
	colorcube();
}

SectorTorus::SectorTorus(GLfloat inner_radius, GLfloat outer_radius, GLfloat thickness, GLfloat start_angle, GLfloat sector_angle) {
	tesselation = 50;
	method = GL_TRIANGLES;
	this->inner_radius = inner_radius;
	this->outer_radius = outer_radius;
	this->thickness = thickness;
	this->start_angle = start_angle;
	this->sector_angle = sector_angle;
}

void SectorTorus::loadpoints() {
	GLfloat sectors= sector_angle/tesselation;
	GLfloat top = thickness/2;
	GLfloat bottom = -top;

	{
		GLfloat x = inner_radius * cos(start_angle);
		GLfloat y = inner_radius * sin(start_angle);

		glm::vec4 topc_i(x, y, top, 1.0);
		glm::vec4 botc_i(x, y, bottom, 1.0);

		x = outer_radius * cos(start_angle);
		y = outer_radius * sin(start_angle);

		glm::vec4 topc_o(x, y, top, 1.0);
		glm::vec4 botc_o(x, y, bottom, 1.0);

		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(grey); 
		vertices.push_back(topc_i); normals.push_back(glm::vec3(topc_i)); colors.push_back(grey); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(grey); 

		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(grey); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(grey);
		vertices.push_back(botc_o); normals.push_back(glm::vec3(botc_o)); colors.push_back(grey);
	}
	{
		GLfloat x = inner_radius * cos(start_angle + sector_angle);
		GLfloat y = inner_radius * sin(start_angle + sector_angle);

		glm::vec4 topc_i(x, y, top, 1.0);
		glm::vec4 botc_i(x, y, bottom, 1.0);

		x = outer_radius * cos(start_angle + sector_angle);
		y = outer_radius * sin(start_angle + sector_angle);

		glm::vec4 topc_o(x, y, top, 1.0);
		glm::vec4 botc_o(x, y, bottom, 1.0);

		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(grey); 
		vertices.push_back(topc_i); normals.push_back(glm::vec3(topc_i)); colors.push_back(grey); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(grey); 

		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(grey); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(grey);
		vertices.push_back(botc_o); normals.push_back(glm::vec3(botc_o)); colors.push_back(grey);
	}

	GLfloat l;
	for (GLfloat lats = start_angle; lats <= start_angle + sector_angle; lats=lats+sectors)
	{
		GLfloat x = inner_radius * cos(lats);
		GLfloat y = inner_radius * sin(lats);

		glm::vec4 topc_i(x, y, top, 1.0);
		glm::vec4 botc_i(x, y, bottom, 1.0);

		x = outer_radius * cos(lats);
		y = outer_radius * sin(lats);

		glm::vec4 topc_o(x, y, top, 1.0);
		glm::vec4 botc_o(x, y, bottom, 1.0);

		if(lats+sectors>start_angle + sector_angle)
			l=start_angle + sector_angle;
		else
			l=lats+sectors;

		x = inner_radius * cos(l);
		y = inner_radius * sin(l);

		glm::vec4 topcn_i(x, y, top, 1.0);
		glm::vec4 botcn_i(x, y, bottom, 1.0);


		x = outer_radius * cos(l);
		y = outer_radius * sin(l);
		
		glm::vec4 topcn_o(x, y, top, 1.0);
		glm::vec4 botcn_o(x, y, bottom, 1.0);

		vertices.push_back(topcn_i); normals.push_back(glm::vec3(topcn_i)); colors.push_back(grey); 
		vertices.push_back(topc_i); normals.push_back(glm::vec3(topc_i)); colors.push_back(grey); 
		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(grey); 
		
		vertices.push_back(topcn_i); normals.push_back(glm::vec3(topcn_i)); colors.push_back(grey); 
		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(grey); 
		vertices.push_back(botcn_i); normals.push_back(glm::vec3(botcn_i)); colors.push_back(grey); 

		vertices.push_back(topcn_o); normals.push_back(glm::vec3(topcn_o)); colors.push_back(grey); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(grey); 
		vertices.push_back(botc_o); normals.push_back(glm::vec3(botc_o)); colors.push_back(grey); 
		
		vertices.push_back(topcn_o); normals.push_back(glm::vec3(topcn_o)); colors.push_back(grey); 
		vertices.push_back(botc_o); normals.push_back(glm::vec3(botc_o)); colors.push_back(grey); 
		vertices.push_back(botcn_o); normals.push_back(glm::vec3(botcn_o)); colors.push_back(grey); 
		

		vertices.push_back(topcn_i); normals.push_back(glm::vec3(topcn_i)); colors.push_back(blue); 
		vertices.push_back(topc_i); normals.push_back(glm::vec3(topc_i)); colors.push_back(blue); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(blue); 

		vertices.push_back(topcn_i); normals.push_back(glm::vec3(topcn_i)); colors.push_back(blue); 
		vertices.push_back(topc_o); normals.push_back(glm::vec3(topc_o)); colors.push_back(blue);
		vertices.push_back(topcn_o); normals.push_back(glm::vec3(topcn_o)); colors.push_back(blue); 

		vertices.push_back(botcn_i); normals.push_back(glm::vec3(botcn_i)); colors.push_back(blue); 
		vertices.push_back(botc_i); normals.push_back(glm::vec3(botc_i)); colors.push_back(blue); 
		vertices.push_back(botc_o); normals.push_back(glm::vec3(botc_o)); colors.push_back(blue); 

		vertices.push_back(botcn_i); normals.push_back(glm::vec3(botcn_i)); colors.push_back(blue); 
		vertices.push_back(botc_o); normals.push_back(glm::vec3(botc_o)); colors.push_back(blue);
		vertices.push_back(botcn_o); normals.push_back(glm::vec3(botcn_o)); colors.push_back(blue); 

	}
}

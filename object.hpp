#include "gl_framework.hpp"
#include <vector>

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class BaseObject {
protected:
public:
	std::vector<glm::mat4*> transforms;
	BaseObject();
	virtual void init() = 0;		// Generate VAOs and VBOs
	virtual void generate() = 0;	// Generate Points
	virtual void render() = 0;		// Set VAO and draw
	virtual void render(glm::mat4) = 0;		// Set VAO and draw
};

class Object : public BaseObject {
protected:

public:
	std::vector<BaseObject*> children;
	Object();
	void init();	
	void generate();	
	void render();	
	void render(glm::mat4);
};

class Primitive : public BaseObject {
protected:
	int tesselation;
	GLuint method;
	GLuint vbo, vao;
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec4> normals;
public:
	Primitive();
	void init();	
	void generate();
	virtual void loadpoints() = 0;
	void render();
	void render(glm::mat4);
};

class Sphere : public Primitive {
	GLfloat lat_start;
	GLfloat long_start;
	GLfloat lat_angle;
	GLfloat long_angle;
public:
	Sphere();
	Sphere(GLfloat, GLfloat, GLfloat, GLfloat);
	void loadpoints();
};

class Cylinder : public Primitive {
public:
	Cylinder();
	void loadpoints();	
};

class Cube : public Primitive {
	glm::vec4 positions[8] = {
	  glm::vec4(-0.5, -0.5, 0.5, 1.0),
	  glm::vec4(-0.5, 0.5, 0.5, 1.0),
	  glm::vec4(0.5, 0.5, 0.5, 1.0),
	  glm::vec4(0.5, -0.5, 0.5, 1.0),
	  glm::vec4(-0.5, -0.5, -0.5, 1.0),
	  glm::vec4(-0.5, 0.5, -0.5, 1.0),
	  glm::vec4(0.5, 0.5, -0.5, 1.0),
	  glm::vec4(0.5, -0.5, -0.5, 1.0)
	};;
public:
	Cube();
	void quad(int a, int b, int c, int d);
	void colorcube(void);
	void loadpoints();
};

class SectorTorus : public Primitive {
	GLfloat inner_radius;
	GLfloat outer_radius;
	GLfloat thickness;
	GLfloat sector_angle;
	GLfloat start_angle;

public:
	SectorTorus(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void loadpoints();
};



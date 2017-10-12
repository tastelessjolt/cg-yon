#include "gl_framework.hpp"
#include <vector>

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

glm::vec4 color(0.6, 0.6, 0.6, 1.0);
glm::vec4 black(0.2, 0.2, 0.2, 1.0);
glm::vec4 white(1.0, 1.0, 1.0, 1.0);

class BaseObject {
protected:
	std::vector<glm::mat4*> transforms;
public:
	BaseObject();
	virtual void init() = 0;		// Generate VAOs and VBOs
	virtual void generate() = 0;	// Generate Points
	virtual void render() = 0;		// Set VAO and draw
	virtual void render(glm::mat4) = 0;		// Set VAO and draw
};

class Primitive : BaseObject {
protected:
	int tesselation;
	GLuint method;
	GLuint vbo, vao;
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec4> normals;
public:
	Primitive();

	virtual void init() = 0;	
	virtual void generate() = 0;	
	virtual void render() = 0;	
	void render(glm::mat4);
};

class Object : BaseObject {
protected:
	std::vector<BaseObject*> children;

public:
	Object();

	virtual void init();	
	virtual void generate();	
	virtual void render();	
	virtual void render(glm::mat4);
};


class Sphere : Primitive {
public:
	Sphere();

	void init();	
	void generate();	
	void render();	
};

class Cylinder : Primitive {
public:
	Cylinder();

	void init();	
	void generate();	
	void render();	
};

class Cube : Primitive {
public:
	Cube();

	void init();	
	void generate();	
	void render();	
};
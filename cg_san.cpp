#include "gl_framework.hpp"
#include "shader_util.hpp"

#include <unistd.h>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint vPosition;
GLuint vColor;
GLuint vNormal;
GLuint uModelViewMatrix;
GLuint normalMatrix;

std::vector<float> points;
std::vector<float> triangles;

int mode = CI_MODELLING_MODE;

GLuint shaderProgram;
GLuint vbo_points, vbo_triangles, vao_points, vao_triangles;

glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
glm::mat4 look_at;
glm::mat4 translate;
glm::mat4 translate_inv;

GLfloat xrot = 0.0f;
GLfloat yrot = 0.0f;
GLfloat zrot = 0.0f;

GLfloat xpos = 0.0f;
GLfloat ypos = 0.0f;
GLfloat zpos = 0.0f;

GLfloat rcol = 0.0f;
GLfloat gcol = 0.0f;
GLfloat bcol = 0.0f;


int mode_state;
bool mode_printed = false;

GLfloat zpos_state;
bool zpos_printed = false;

GLfloat rcol_state, gcol_state, bcol_state;
bool col_printed = false;

glm::vec3 getCentroid () {
	GLfloat sumx = 0, sumy = 0, sumz = 0;
	for (int i = 0; i < triangles.size()/18; ++i){
	sumx += triangles[18*i];
	sumy += triangles[18*i+1];
	sumz += triangles[18*i+2];
	}

	int p = triangles.size()/18;
	sumx += triangles[18*(p-1) + 0 + 6] + triangles[18*(p-1) + 0 + 12];
	sumy += triangles[18*(p-1) + 1 + 6] + triangles[18*(p-1) + 1 + 12];
	sumz += triangles[18*(p-1) + 2 + 6] + triangles[18*(p-1) + 2 + 12];

	return glm::vec3(sumx/(p + 2.0), sumy/(p + 2.0), sumz/(p + 2.0));
}

void printState()
{
	
}

void initShadersGL(void)
{
	std::string vertex_shader_file("simple_vs.glsl");
	std::string fragment_shader_file("simple_fs.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	
}

void initVertexBufferGL(void)
{
	//Ask GL for a Vertex Buffer Object (vbo)
	glGenBuffers (1, &vbo_points);
	// Set it as the current buffer to be used by binding it
	glBindBuffer (GL_ARRAY_BUFFER, vbo_points);
	//Copy the points into the current buffer - 9 float values, start pointer and static data
	// glBufferData (GL_ARRAY_BUFFER, points.size() * sizeof (float), &points[0], GL_DYNAMIC_DRAW);

	glGenBuffers (1, &vbo_triangles);
	// Set it as the current buffer to be used by binding it
	glBindBuffer (GL_ARRAY_BUFFER, vbo_triangles);
	//Copy the points into the current buffer - 9 float values, start pointer and static data
	// glBufferData (GL_ARRAY_BUFFER, triangles.size() * sizeof (float), &triangles[0], GL_DYNAMIC_DRAW);


	/* 	
	 *	Generates vao, vbo takes args as a tree of "objects"
	 *	character1.init()	
	 * 	character2.init()  
	 */


	/*
	 *	Generate geometric primitives with tesselation params 
	 *	char.generate() 
	 */


	// //Ask GL for a Vertex Attribute Object (vao_points)
	// glGenVertexArrays (1, &vao_points);
	// //Set it as the current array to be used by binding it
	// glBindVertexArray (vao_points);
	// //Enable the vertex attribute
	// glEnableVertexAttribArray (0);
	// //This the layout of our first vertex buffer
	// //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats 
	// glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");

	glPointSize(5.0f);
}

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);

	// Renders takes arguments - transformations 
	// character1.render()
	// character2.render()
}

int main(int argc, char** argv)
{
	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
	return -1;

	//We want OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//This is for MacOSX - can be omitted otherwise
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "CS475/CS675 OpenGL Framework", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	//Turn this on to get Shader based OpenGL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cerr<<"GLEW Init Failed : %s"<<std::endl;
	}

	//Print and see what context got enabled
	std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
	std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
	std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
	std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	// glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);

	//Initialize GL state
	csX75::initGL();
	initShadersGL();
	initVertexBufferGL();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{
		printState();

		// Render here
		renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);
		
		// Poll for and process events
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}


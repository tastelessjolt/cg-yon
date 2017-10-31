#include "gl_framework.hpp"
#include "shader_util.hpp"

#include <unistd.h>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "object.hpp"
#include "character1.hpp"
#include "character2.hpp"
#include "environ.hpp"

GLuint vPosition;
GLuint vColor;
GLuint vNormal;
GLuint uModelViewMatrix;
GLuint normalMatrix;
GLuint viewMatrix;
GLuint uLights;
GLuint texture;
GLuint textCoord;

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 look_at;
glm::mat4 modelview_matrix;
glm::mat4 projection_matrix;
glm::mat4 view_matrix;
GLfloat xrot = 0.0f;
GLfloat yrot = 0.0f;
GLfloat zrot = 0.0f;

GLfloat xpos = 0.0f;
GLfloat ypos = 0.0f;
GLfloat zpos = 0.0f;

BaseObject* sphere;
BaseObject* cube;
BaseObject* cylinder;
BaseObject* torus;

BaseObject* char1;
BaseObject* char2;
BaseObject* environment;

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
	glPointSize(5.0f);

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
	textCoord = glGetAttribLocation( shaderProgram, "textCoord" );

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
	viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

	uLights = glGetUniformLocation( shaderProgram, "lights");
	texture = glGetUniformLocation( shaderProgram, "utexture");


	sphere = new Sphere();
	cube = new Cube();
	cylinder = new Cylinder();
	char1 = new Character1();
	char2 = new Character2();
	environment = new Environment();
	// torus = new SectorTorus(0.8, 1, 0.3, -3.14/3, 3.14/2);

	// sphere->init();
	// cube->init();
	// cylinder->init();
	char1->init();
	// char2->init();
	// environment->init();
	// torus->init();
	// sphere->generate();
	// cube->generate();
	// cylinder->generate();

	char1->generate();
	// char2->generate();
	// environment->generate();
	// torus->generate();

	// glm::mat4* environ_scale = new glm::mat4();
	// environment->transforms.push_back(environ_scale);
	// *environ_scale = glm::scale(glm::mat4(1.0f), glm::vec3(10.0, 10.0, 10.0));

	// glm::mat4* char2_trans = new glm::mat4();
	// char2->transforms.push_back(char2_trans);
	// *char2_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.5, 0.0));

	// glm::mat4* char2_scale = new glm::mat4();
	// char2->transforms.push_back(char2_scale);
	// *char2_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));

}

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);

	look_at = glm::lookAt(glm::vec3(xpos, ypos, zpos), glm::vec3(xpos, ypos, zpos - 1.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 persp_matrix = glm::frustum(0.5, -0.5, -0.5, 0.5, 0.5, 200.0);

	rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));

	glm::mat4 view_matrix = persp_matrix * rotation_matrix * look_at;

	// lighting
	glm::vec4 light = view_matrix * glm::vec4(0.0, 0.0, 1.0, 1.0);
	glUniform4fv(uLights, 1, glm::value_ptr(light));

	glUniformMatrix3fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

	
	// sphere->render(view_matrix);
	// cube->render(view_matrix);
	// cylinder->render(view_matrix);
	// torus->render(view_matrix);
	char1->render(view_matrix);
	// char2->render(view_matrix);
	// environment->render(view_matrix);
	// torus->render(view_matrix);
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
	window = glfwCreateWindow(640, 640, "CS475/CS675 OpenGL Framework", NULL, NULL);
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


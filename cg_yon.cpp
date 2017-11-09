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
GLuint uModelMatrix;
GLuint normalMatrix;
GLuint vViewMatrix;
GLuint viewMatrix;

GLuint uLights1;
GLuint uLights2;
GLuint uLights3;
GLuint uLights1_int;
GLuint uLights2_int;
GLuint uLights3_int;

GLint light1on = 1;
GLint light2on = 1;
GLint light3on = 1;

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
GLfloat ypos = 2.0f;
GLfloat zpos = 5.0f;

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

	uModelMatrix = glGetUniformLocation( shaderProgram, "uModelMatrix");
	normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
	viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
	vViewMatrix = glGetUniformLocation( shaderProgram, "vViewMatrix");

	uLights1 = glGetUniformLocation( shaderProgram, "light1");
	uLights2 = glGetUniformLocation( shaderProgram, "light2");
	uLights3 = glGetUniformLocation( shaderProgram, "light3");

	uLights1_int = glGetUniformLocation( shaderProgram, "light1_int");
	uLights2_int = glGetUniformLocation( shaderProgram, "light2_int");
	uLights3_int = glGetUniformLocation( shaderProgram, "light3_int");

	texture = glGetUniformLocation( shaderProgram, "utexture");

	char1 = new Character1();
	char2 = new Character2();
	environment = new Environment();

	char1->init();
	char2->init();
	environment->init();

	char1->generate();
	char2->generate();
	environment->generate();

	glm::mat4* environ_scale = new glm::mat4();
	environment->transforms.push_back(environ_scale);
	*environ_scale = glm::scale(glm::mat4(1.0f), glm::vec3(10.0, 10.0, 10.0));

	glm::mat4* char2_trans = new glm::mat4();
	char2->transforms.push_back(char2_trans);
	*char2_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.5, 0.0));

	glm::mat4* char2_scale = new glm::mat4();
	char2->transforms.push_back(char2_scale);
	*char2_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
}

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);

	look_at = glm::lookAt(glm::vec3(xpos, ypos, zpos), glm::vec3(xpos, ypos, zpos - 1.0), glm::vec3(0.0, 1.0, 0.0));
	// look_at = glm::lookAt(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 2.0f, 5.0f - 1.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 persp_matrix = glm::frustum(0.5, -0.5, -0.5, 0.5, 0.5, 200.0);

	rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));

	view_matrix = persp_matrix * rotation_matrix * look_at;

	// lighting
	glm::vec4 light1 = glm::vec4(9.0, 0.0, -9.0, 0.0);
	glm::vec4 light2 = glm::vec4(3.0, -3.0, 3.0, 0.0);
	glm::vec4 light3 = glm::vec4(0.0, 9.0, 0.0, 1.0);

	GLfloat light1_int = 2.0 * light1on;
	GLfloat light2_int = 0.5 * light2on;
	GLfloat light3_int = 6.0 * light3on;
	
	glUniform4fv(uLights1, 1, glm::value_ptr(light1));
	glUniform1f(uLights1_int, light1_int);

	glUniform4fv(uLights2, 1, glm::value_ptr(light2));
	glUniform1f(uLights2_int, light2_int);
	
	glUniform4fv(uLights3, 1, glm::value_ptr(light3));
	glUniform1f(uLights3_int, light3_int);


	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(vViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
	
	char1->render(glm::mat4(1.0f));
	char2->render(glm::mat4(1.0f));
	environment->render(glm::mat4(1.0f));
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


#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#define CI_RECORD_MODE 0
#define CI_PLAYBACK_MODE 1
#define CI_SAVE_MODE 2

#define CONS_PI 3.1415926

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GL/glew.h>
#include "glm/vec3.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include <fstream>
#include <sstream>

#include <sys/stat.h>

class bezier
{
  std::vector<glm::vec3> control_points;
  bool updated;
  glm::vec3 decasteljau(GLint, GLint, GLfloat);
public:
  bezier();
  void addControlPoint(glm::vec3);
  void clearControlPoints();
  bool hasChanged();
  glm::vec3 getPoint(GLfloat);
  std::vector<glm::vec3> getControlPoints();
};


namespace csX75
{
  //! Initialize GL State
  void initGL(void);

  //!playback
  void playback(void);

  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  //!GLFW mouse click callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif

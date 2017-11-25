#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#define CI_RECORD_MODE 0
#define CI_PLAYBACK_MODE 1

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GL/glew.h>
#include "glm/vec3.hpp"

#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>


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

#include "gl_framework.hpp"
#include <unistd.h>
#include <sys/stat.h>

extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;

extern GLfloat xpos;
extern GLfloat ypos;
extern GLfloat zpos;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST); 
    //Enable Gourard shading
    glShadeModel(GL_SMOOTH);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }

  void quit (GLFWwindow *window) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      quit(window);
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      yrot -= 0.2;
    } 
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      yrot += 0.2;
    }
    else if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      xrot -= 0.2;
    }
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      xrot += 0.2;
    }
    else if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      zrot -= 0.2;
    }
    else if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      zrot += 0.2;
    }
    else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      ypos += 0.05;
    } 
    else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      xpos -= 0.05; 
    }
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      ypos -= 0.05;
    }
    else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      xpos += 0.05;
    }
    else if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      zpos -= 0.05; 
    }
    else if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      zpos += 0.05;
    }
    else if (key == GLFW_KEY_L && (action == GLFW_PRESS)) {
      // std::string filename;
      // std::cout << "Enter the name of the file to be loaded (without extension): "; std::cin >> filename;
      // filename+=".raw";

      // struct stat buffer;
      // if (stat(filename.c_str(), &buffer) != 0){
      //   std::cerr << "Error: File not found" << std::endl;
      //   return;
      // }

      // std::fstream fs(filename, std::fstream::in);

      // triangles.clear();
      // points.clear();
      
      // float tmp;
      // std::string line;
      // while(!fs.eof()){
      //   std::getline(fs, line);
      //   if (line != ""){
      //     std::stringstream iss(line);
      //     for(int i = 0; i < 6; i++){
      //       iss >> tmp;
      //       triangles.push_back(tmp);
      //     }
      //   }
      // }

      // fs.close();
    }
    else if (key == GLFW_KEY_Q && (action == GLFW_PRESS)) {
      quit(window);
    }
  }

  void convert_to_world(GLFWwindow* window, GLint x, GLint y, GLfloat* xf, GLfloat* yf){
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // ensure camera look at vector is normal to xy plane whenever using this fn
    *xf = -1 * (x - width/2.0)/(width/2.0) + xpos;
    *yf = -1 * (y - height/2.0)/(height/2.0) + ypos;

  }
  //!GLFW mouse click callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
      
    }
  }
};  
  



#include "gl_framework.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>

#include "character1.hpp"
#include "character2.hpp"

extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;

extern GLfloat xpos;
extern GLfloat ypos;
extern GLfloat zpos;

extern GLint light1on;
extern GLint light2on;
extern GLint light3on;

extern GLint expr_state;

extern BaseObject* char1;
extern BaseObject* char2;

std::string filename = "frames.txt";

std::vector<std::string> frames;
int frame_num;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

  std::string getEnvState(){
  	std::stringstream stream;

  	stream << light1on << ",";
  	stream << light2on << ",";
  	stream << light3on << ",";

  	stream << xpos << ",";
  	stream << ypos << ",";
  	stream << zpos << ",";

  	stream << xrot << ",";
  	stream << yrot << ",";
  	stream << zrot;

  	return stream.str();
  }

  void setEnvState(std::string state){
  	std::stringstream sstream(state);
  	std::string token;

  	getline(sstream, token, ',');
  	light1on = stoi(token);
  	getline(sstream, token, ',');
  	light2on = stoi(token);
  	getline(sstream, token, ',');
  	light3on = stoi(token);
  	getline(sstream, token, ',');

  	xpos = stoi(token);
  	getline(sstream, token, ',');
  	ypos = stoi(token);
  	getline(sstream, token, ',');
  	zpos = stoi(token);
  	getline(sstream, token, ',');

  	xrot = stof(token);
  	getline(sstream, token, ',');
  	yrot = stof(token);
  	getline(sstream, token, ',');
  	zrot = stof(token);
  	
  }

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
      quit(window);

    GLfloat delta = 0.05;
    action = glfwGetKey(window, GLFW_KEY_LEFT);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)){
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_ANGLE, glm::vec3(0.0, -delta, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_ANGLE, glm::vec3(0.0, -delta, 0.0));
      else
        yrot -= 0.2;
    } 
    action = glfwGetKey(window, GLFW_KEY_RIGHT);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_ANGLE, glm::vec3(0.0, delta, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_ANGLE, glm::vec3(0.0, delta, 0.0));
      else
        yrot += 0.2;
    }
    action = glfwGetKey(window, GLFW_KEY_UP);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_ANGLE, glm::vec3(-delta, 0.0, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_ANGLE, glm::vec3(-delta, 0.0, 0.0));
      else
        xrot -= 0.2;
    }
    action = glfwGetKey(window, GLFW_KEY_DOWN);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_ANGLE, glm::vec3(delta, 0.0, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_ANGLE, glm::vec3(delta, 0.0, 0.0));
      else
        xrot += 0.2;
    }
    action = glfwGetKey(window, GLFW_KEY_PAGE_UP);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_ANGLE, glm::vec3(0.0, 0.0, -delta));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_ANGLE, glm::vec3(0.0, 0.0, -delta));
      else
        zrot -= 0.2;
    }
    action = glfwGetKey(window, GLFW_KEY_PAGE_DOWN);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_ANGLE, glm::vec3(0.0, 0.0, delta));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_ANGLE, glm::vec3(0.0, 0.0, delta));
      else
        zrot += 0.2;
    }
    action = glfwGetKey(window, GLFW_KEY_W);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)){
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_TRANSLATE, glm::vec3(0.0, delta, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_TRANSLATE, glm::vec3(0.0, delta, 0.0));
      else
        ypos += 0.05;
    } 
    action = glfwGetKey(window, GLFW_KEY_A);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_TRANSLATE, glm::vec3(-delta, 0.0, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_TRANSLATE, glm::vec3(-delta, 0.0, 0.0));
      else
        xpos -= 0.05; 
    }
    action = glfwGetKey(window, GLFW_KEY_S);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_TRANSLATE, glm::vec3(0.0, -delta, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_TRANSLATE, glm::vec3(0.0, -delta, 0.0));
      else
        ypos -= 0.05;
    }
    action = glfwGetKey(window, GLFW_KEY_D);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_TRANSLATE, glm::vec3(delta, 0.0, 0.0));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_TRANSLATE, glm::vec3(delta, 0.0, 0.0));
      else
        xpos += 0.05;
    }
    action = glfwGetKey(window, GLFW_KEY_Z);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_TRANSLATE, glm::vec3(0.0, 0.0, -delta));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_TRANSLATE, glm::vec3(0.0, 0.0, -delta));
      else
        zpos -= 0.05; 
    }
    action = glfwGetKey(window, GLFW_KEY_X);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        ((Character1*)char1)->manoeuvre(Character1::BODY_TRANSLATE, glm::vec3(0.0, 0.0, delta));
      else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        ((Character2*)char2)->manoeuvre(Character2::BODY_TRANSLATE, glm::vec3(0.0, 0.0, delta));
      else
        zpos += 0.05;
    }

    // lights on off
    action = glfwGetKey(window, GLFW_KEY_1);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (light1on == 0)
        light1on = 1;
      else
        light1on = 0;
    }

    action = glfwGetKey(window, GLFW_KEY_2);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (light2on == 0)
        light2on = 1;
      else
        light2on = 0;
    }

    action = glfwGetKey(window, GLFW_KEY_3);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (light3on == 0)
        light3on = 1;
      else
        light3on = 0;
    }

	action = glfwGetKey(window, GLFW_KEY_MINUS);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
    	expr_state = (expr_state + 1) % 3;

    	texture_t tex;
    	if (expr_state == 0)
	    	tex.filename = "textures/face_happy.bmp";
    	else if (expr_state == 1)
	    	tex.filename = "textures/face.bmp";
	    tex.width = 1280;
	    tex.height = 320;

    	((Character1 *)char1)->expression(tex); 
    }
    // left leg char 1
    action = glfwGetKey(window, GLFW_KEY_H);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::LEFT_LEG_ANGLE, glm::vec3(
                      delta * ( glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS ? 1 : 0 )
                      ));
    }
    // right leg char 1
    action = glfwGetKey(window, GLFW_KEY_J);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::RIGHT_LEG_ANGLE, glm::vec3(
                      delta * ( glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS ? 1 : 0 )
                      ));
    }
    // left arm char 1
    action = glfwGetKey(window, GLFW_KEY_K);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::LEFT_ARM_ANGLE, glm::vec3(
                      delta * ( glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS ? 1 : 0 )
                      ));
    }
    action = glfwGetKey(window, GLFW_KEY_L);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::RIGHT_ARM_ANGLE, glm::vec3(
                      delta * ( glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS ? 1 : 0 ), 
                      delta * ( glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS ? 1 : 0 )
                      ));
    }

    // elbows
    action = glfwGetKey(window, GLFW_KEY_U);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::LEFT_ELBOW_ANGLE, glm::vec3(0.0, delta, 0.0));
    }
    action = glfwGetKey(window, GLFW_KEY_I);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::RIGHT_ELBOW_ANGLE, glm::vec3(0.0, delta, 0.0));
    }

    // knees
    action = glfwGetKey(window, GLFW_KEY_O);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::LEFT_KNEE_ANGLE, glm::vec3(delta, 0.0, 0.0));
    }
    action = glfwGetKey(window, GLFW_KEY_P);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::RIGHT_KNEE_ANGLE, glm::vec3(delta, 0.0, 0.0));
    }


    action = glfwGetKey(window, GLFW_KEY_T);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::TORSO_ANGLE, glm::vec3(0.0, delta, 0.0));
    }
    action = glfwGetKey(window, GLFW_KEY_Y);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character1 *)char1)->manoeuvre(Character1::FACE_ANGLE, glm::vec3(0.0, delta, 0.0));
    }

    


    action = glfwGetKey(window, GLFW_KEY_F);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character2 *)char2)->manoeuvre(Character2::HEADBAND_ANGLE, glm::vec3(delta, 0.0, 0.0));
    }


    
    action = glfwGetKey(window, GLFW_KEY_E);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character2 *)char2)->manoeuvre(Character2::LEFT_HOUSING_ANGLE, glm::vec3(0.0, delta, 0.0));
    }

    action = glfwGetKey(window, GLFW_KEY_R);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character2 *)char2)->manoeuvre(Character2::LEFT_HOUSING_ANGLE, glm::vec3(0.0, 0.0, delta));
    }

    action = glfwGetKey(window, GLFW_KEY_G);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character2 *)char2)->manoeuvre(Character2::RIGHT_HOUSING_ANGLE, glm::vec3(0.0, delta, 0.0));
    }

    action = glfwGetKey(window, GLFW_KEY_V);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      GLfloat delta = 0.05 *
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -1 : 1);

      ((Character2 *)char2)->manoeuvre(Character2::RIGHT_HOUSING_ANGLE, glm::vec3(0.0, 0.0, delta));
    }

    action = glfwGetKey(window, GLFW_KEY_C);
    if (action == GLFW_PRESS) {
        std::cout << "Char1 state: " << ( (Character1*)char1)->getState() << std::endl;
        std::cout << "Char2 state: " << ( (Character2*)char2)->getState() << std::endl;

        std::fstream fs;
        fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

        if (!fs ) 
        {
          std::cout << "Cannot open file, file does not exist. Creating new file..";

          fs.open(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
        }
        else   
        {    // use existing file
          std::cout<<"success "<<filename <<" found. \n";
          // cout<<"\nAppending writing and working with existing file"<<"\n---\n";
        }

        fs << getEnvState() << "|";
        fs << ( (Character1*)char1)->getState() << "|" << ( (Character2*)char2)->getState() << std::endl;

        fs.close();
    }

    action = glfwGetKey(window, GLFW_KEY_M);
    if (action == GLFW_PRESS) {
      // std::cout << "Char1 state: " << ( (Character1*)char1)->getState() << std::endl;
      // std::cout << "Char2 state: " << ( (Character2*)char2)->getState() << std::endl;
      std::fstream fs;
      fs.open(filename, std::fstream::in | std::fstream::out);

      if (!fs ) 
      {
        std::cout << "Cannot open file, file does not exist.";
      }
      else   
      {    // use existing file
        std::cout<<"success "<<filename <<" found. \n";
        // cout<<"\nAppending writing and working with existing file"<<"\n---\n";
        std::string buffer;
        frames.clear();
        while (std::getline(fs, buffer, '\n')) {
          // std::cout << "buff" << std::endl;
          frames.push_back(buffer);
        }

        fs.close();
        frame_num = 0;
      }
    }

    action = glfwGetKey(window, GLFW_KEY_N);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (frame_num < frames.size()) {
        std::cout << "Frame " << frame_num << std::endl;
        std::string buf = frames[frame_num++];
        std::stringstream ss(buf);

		getline(ss, buf, '|');
		setEnvState(buf);

        getline(ss, buf, '|');
        ( (Character1*)char1)->setState(buf);
        getline(ss, buf, '|');
        ( (Character2*)char2)->setState(buf);
      }
      else {
        std::cout << "no next frame available" << std::endl;
      }
    }

    action = glfwGetKey(window, GLFW_KEY_B);
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
      if (frame_num > 0) {
        std::cout << "Frame " << frame_num << std::endl;
        std::string buf = frames[--frame_num];
        std::stringstream ss(buf);

        getline(ss, buf, '|');
		setEnvState(buf);

        getline(ss, buf, '|');
        ( (Character1*)char1)->setState(buf);
        getline(ss, buf, '|');
        ( (Character2*)char2)->setState(buf);
      }
      else {
        std::cout << "no previous frame available" << std::endl;
      }
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
  



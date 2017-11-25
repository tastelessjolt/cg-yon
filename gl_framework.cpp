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

extern GLfloat light1on;
extern GLfloat light2on;
extern GLfloat light3on;

extern GLint expr_state;
extern GLint mode;

extern BaseObject* char1;
extern BaseObject* char2;

std::string filename = "frames.txt";
double FPS = 120.0;

std::vector<std::string> frames;
std::vector<int> frames_index;
int kframe_num = 0;
int frame_jump = FPS;

double playback_start_time;

namespace csX75
{

	struct frame_t
	{

		GLfloat light1on;
		GLfloat light2on;
		GLfloat light3on;

		glm::vec3 campos;

		glm::vec3 camrot;

		glm::vec3 lg_left_leg_angle;

		glm::vec3 lg_left_knee_angle;

		glm::vec3 lg_right_leg_angle;

		glm::vec3 lg_right_knee_angle;

		glm::vec3 lg_left_arm_angle;

		glm::vec3 lg_left_elbow_angle;

		glm::vec3 lg_right_arm_angle;

		glm::vec3 lg_right_elbow_angle;

		glm::vec3 lg_torso_angle;

		glm::vec3 lg_face_angle;

		glm::vec3 lg_body_angle;

		glm::vec3 lg_body_translate;

		std::string lg_filename;
		int lg_width;
		int lg_height;

		glm::vec3 hf_body_angle;

		glm::vec3 hf_body_translate;

		glm::vec3 hf_left_angle;

		glm::vec3 hf_left_housing_angle;

		glm::vec3 hf_right_angle;

		glm::vec3 hf_right_housing_angle;
		
	};

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

	frame_t frameStrToFrame(std::string str){
		frame_t ft;

		std::stringstream ss(str);
		std::string buf;

		getline(ss, buf, '|');
		{
			std::stringstream sstream(buf);

			getline(sstream, buf, ',');
			ft.light1on = stof(buf);
			getline(sstream, buf, ',');
			ft.light2on = stof(buf);
			getline(sstream, buf, ',');
			ft.light3on = stof(buf);

			getline(sstream, buf, ',');
			ft.campos[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.campos[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.campos[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.camrot[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.camrot[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.camrot[2] = stof(buf);
		}


		getline(ss, buf, '|');
		{
			std::stringstream sstream(buf);

			getline(sstream, buf, ',');
			ft.lg_left_leg_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_leg_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_leg_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_left_knee_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_knee_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_knee_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_right_leg_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_leg_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_leg_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_right_knee_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_knee_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_knee_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_left_arm_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_arm_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_arm_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_left_elbow_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_elbow_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_left_elbow_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_right_arm_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_arm_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_arm_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_right_elbow_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_elbow_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_right_elbow_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_torso_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_torso_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_torso_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_face_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_face_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_face_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_body_angle[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_body_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_body_angle[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_body_translate[0] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_body_translate[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.lg_body_translate[2] = stof(buf);

			getline(sstream, buf, ',');
			ft.lg_filename = buf;
			getline(sstream, buf, ',');
			ft.lg_width = stoi(buf);
			getline(sstream, buf, ',');
			ft.lg_height = stoi(buf);
		}


		getline(ss, buf, '|');
		{
			std::stringstream sstream(buf);
			
			getline(sstream, buf, ',');
			ft.hf_body_angle[0] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_body_angle[1] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_body_angle[2] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_body_translate[0] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_body_translate[1] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_body_translate[2] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_left_angle[0] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_left_angle[1] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_left_angle[2] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_left_housing_angle[0] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_left_housing_angle[1] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_left_housing_angle[2] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_right_angle[0] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_right_angle[1] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_right_angle[2] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_right_housing_angle[0] = stof(buf);
			getline(sstream, buf, ','); 
			ft.hf_right_housing_angle[1] = stof(buf);
			getline(sstream, buf, ',');
			ft.hf_right_housing_angle[2] = stof(buf);

		}

		return ft;
	}

	std::string frameFrameToStr(frame_t frame){
		std::stringstream stream;

		stream << frame.light1on << ",";
		stream << frame.light2on << ",";
		stream << frame.light3on << ",";

		stream << frame.campos[0] << ",";
		stream << frame.campos[1] << ",";
		stream << frame.campos[2] << ",";

		stream << frame.camrot[0] << ",";
		stream << frame.camrot[1] << ",";
		stream << frame.camrot[2] << "|";

		stream << frame.lg_left_leg_angle[0] << ",";
		stream << frame.lg_left_leg_angle[1] << ",";
		stream << frame.lg_left_leg_angle[2] << ",";

		stream << frame.lg_left_knee_angle[0] << ",";
		stream << frame.lg_left_knee_angle[1] << ",";
		stream << frame.lg_left_knee_angle[2] << ",";

		stream << frame.lg_right_leg_angle[0] << ",";
		stream << frame.lg_right_leg_angle[1] << ",";
		stream << frame.lg_right_leg_angle[2] << ",";

		stream << frame.lg_right_knee_angle[0] << ",";
		stream << frame.lg_right_knee_angle[1] << ",";
		stream << frame.lg_right_knee_angle[2] << ",";

		stream << frame.lg_left_arm_angle[0] << ",";
		stream << frame.lg_left_arm_angle[1] << ",";
		stream << frame.lg_left_arm_angle[2] << ",";

		stream << frame.lg_left_elbow_angle[0] << ",";
		stream << frame.lg_left_elbow_angle[1] << ",";
		stream << frame.lg_left_elbow_angle[2] << ",";

		stream << frame.lg_right_arm_angle[0] << ",";
		stream << frame.lg_right_arm_angle[1] << ",";
		stream << frame.lg_right_arm_angle[2] << ",";

		stream << frame.lg_right_elbow_angle[0] << ",";
		stream << frame.lg_right_elbow_angle[1] << ",";
		stream << frame.lg_right_elbow_angle[2] << ",";

		stream << frame.lg_torso_angle[0] << ",";
		stream << frame.lg_torso_angle[1] << ",";
		stream << frame.lg_torso_angle[2] << ",";

		stream << frame.lg_face_angle[0] << ",";
		stream << frame.lg_face_angle[1] << ",";
		stream << frame.lg_face_angle[2] << ",";

		stream << frame.lg_body_angle[0] << ",";
		stream << frame.lg_body_angle[1] << ",";
		stream << frame.lg_body_angle[2] << ",";

		stream << frame.lg_body_translate[0] << ",";
		stream << frame.lg_body_translate[1] << ",";
		stream << frame.lg_body_translate[2] << ",";

		stream << frame.lg_filename << ",";
		stream << frame.lg_width << ",";
		stream << frame.lg_height << "|";

		stream << frame.hf_body_angle[0] << ",";
		stream << frame.hf_body_angle[1] << ",";
		stream << frame.hf_body_angle[2] << ",";

		stream << frame.hf_body_translate[0] << ",";
		stream << frame.hf_body_translate[1] << ",";
		stream << frame.hf_body_translate[2] << ",";

		stream << frame.hf_left_angle[0] << ",";
		stream << frame.hf_left_angle[1] << ",";
		stream << frame.hf_left_angle[2] << ",";

		stream << frame.hf_left_housing_angle[0] << ",";
		stream << frame.hf_left_housing_angle[1] << ",";
		stream << frame.hf_left_housing_angle[2] << ",";

		stream << frame.hf_right_angle[0] << ",";
		stream << frame.hf_right_angle[1] << ",";
		stream << frame.hf_right_angle[2] << ",";

		stream << frame.hf_right_housing_angle[0] << ",";
		stream << frame.hf_right_housing_angle[1] << ",";
		stream << frame.hf_right_housing_angle[2] << "|";
		
		return stream.str();
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
		light1on = stof(token);
		getline(sstream, token, ',');
		light2on = stof(token);
		getline(sstream, token, ',');
		light3on = stof(token);
		getline(sstream, token, ',');

		xpos = stof(token);
		getline(sstream, token, ',');
		ypos = stof(token);
		getline(sstream, token, ',');
		zpos = stof(token);
		getline(sstream, token, ',');

		xrot = stof(token);
		getline(sstream, token, ',');
		yrot = stof(token);
		getline(sstream, token, ',');
		zrot = stof(token);
		
	}

	void setSceneState(std::string buf){
		std::stringstream ss(buf);

		getline(ss, buf, '|');
		setEnvState(buf);

		getline(ss, buf, '|');
		( (Character1*)char1)->setState(buf);
		getline(ss, buf, '|');
		( (Character2*)char2)->setState(buf);
	}

	GLfloat linearip(GLfloat g1, GLfloat g2, GLfloat frac){
		return g1*(1-frac) + g2*(frac);
	}

	glm::vec3 linearip(glm::vec3 g1, glm::vec3 g2, GLfloat frac){
		return g1*(1-frac) + g2*(frac);
	}

	int linearip(int g1, int g2, GLfloat frac){
		return (frac < 0.01) ? g1 : g2;
	}

	std::string linearip(std::string g1, std::string g2, GLfloat frac){
		return (frac < 0.01) ? g1 : g2;
	}

	frame_t frameip(frame_t f1, frame_t f2, GLfloat frame_fraction){
		frame_t ft;


		ft.light1on = linearip(f1.light1on, f2.light1on, frame_fraction);
		ft.light2on = linearip(f1.light2on, f2.light2on, frame_fraction);
		ft.light3on = linearip(f1.light3on, f2.light3on, frame_fraction);

		ft.campos = linearip(f1.campos, f2.campos, frame_fraction);

		ft.camrot = linearip(f1.camrot, f2.camrot, frame_fraction);

		ft.lg_left_leg_angle = linearip(f1.lg_left_leg_angle, f2.lg_left_leg_angle, frame_fraction);

		ft.lg_left_knee_angle = linearip(f1.lg_left_knee_angle, f2.lg_left_knee_angle, frame_fraction);

		ft.lg_right_leg_angle = linearip(f1.lg_right_leg_angle, f2.lg_right_leg_angle, frame_fraction);

		ft.lg_right_knee_angle = linearip(f1.lg_right_knee_angle, f2.lg_right_knee_angle, frame_fraction);

		ft.lg_left_arm_angle = linearip(f1.lg_left_arm_angle, f2.lg_left_arm_angle, frame_fraction);

		ft.lg_left_elbow_angle = linearip(f1.lg_left_elbow_angle, f2.lg_left_elbow_angle, frame_fraction);

		ft.lg_right_arm_angle = linearip(f1.lg_right_arm_angle, f2.lg_right_arm_angle, frame_fraction);

		ft.lg_right_elbow_angle = linearip(f1.lg_right_elbow_angle, f2.lg_right_elbow_angle, frame_fraction);

		ft.lg_torso_angle = linearip(f1.lg_torso_angle, f2.lg_torso_angle, frame_fraction);

		ft.lg_face_angle = linearip(f1.lg_face_angle, f2.lg_face_angle, frame_fraction);

		ft.lg_body_angle = linearip(f1.lg_body_angle, f2.lg_body_angle, frame_fraction);

		ft.lg_body_translate = linearip(f1.lg_body_translate, f2.lg_body_translate, frame_fraction);

		ft.lg_filename = linearip(f1.lg_filename, f2.lg_filename, frame_fraction);
		ft.lg_width = linearip(f1.lg_width, f2.lg_width, frame_fraction);
		ft.lg_height = linearip(f1.lg_height, f2.lg_height, frame_fraction);

		ft.hf_body_angle = linearip(f1.hf_body_angle, f2.hf_body_angle, frame_fraction);

		ft.hf_body_translate = linearip(f1.hf_body_translate, f2.hf_body_translate, frame_fraction);

		ft.hf_left_angle = linearip(f1.hf_left_angle, f2.hf_left_angle, frame_fraction);

		ft.hf_left_housing_angle = linearip(f1.hf_left_housing_angle, f2.hf_left_housing_angle, frame_fraction);

		ft.hf_right_angle = linearip(f1.hf_right_angle, f2.hf_right_angle, frame_fraction);

		ft.hf_right_housing_angle = linearip(f1.hf_right_housing_angle, f2.hf_right_housing_angle, frame_fraction);

		return ft;
	}

	int interpolator(int frame){

		int i;
		for (i = 0; i < frames_index.size() and frames_index[i] <= frame; ++i);

		if (i == (frames_index.size()))
			return -1;

		frame_t f1 = frameStrToFrame(frames[i-1]);
		frame_t f2 = frameStrToFrame(frames[i]);

		frame_t ff = frameip(f1, f2, (double)(frame - frames_index[i-1]) / (double)(frames_index[i] - frames_index[i-1]));

		setSceneState(frameFrameToStr(ff));
		return 0;
	}

	void startPlayback(){
		mode = CI_PLAYBACK_MODE;
		playback_start_time = glfwGetTime();
		std::cout << "Started Playback" << std::endl; 
	}

	void playback(){

		if (mode == CI_PLAYBACK_MODE)
		{
			int curr_frame = (glfwGetTime() - playback_start_time) * FPS;
			std::cout << "showing frame " << curr_frame << std::endl; 
			if (interpolator(curr_frame) == -1){
				mode = CI_RECORD_MODE;
				std::cout << "Finished Playback" << std::endl; 
			}
		}
	}

	void setFrameJump(int val){
		if (val > 0)
			frame_jump = val;
	}

	int getFrameState(){
		kframe_num += frame_jump;
		return kframe_num - frame_jump;
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

				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {

						std::cout << "Frame Jump: ";
						int tp; std::cin >> tp;
						setFrameJump(tp);
						std::cout << "Frame Jump set to " << frame_jump << std::endl;

				} else {

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
						fs << ( (Character1*)char1)->getState() << "|" << ( (Character2*)char2)->getState() << "|";
						fs << getFrameState() << std::endl;
						fs.close();
				}
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
				std::string buf;
				frames.clear();
				
				while (std::getline(fs, buffer, '\n')) {
					// std::cout << "buff" << std::endl;
					frames.push_back(buffer);

					std::stringstream sstream(buffer);
					
					for (int i = 0; i < 4; ++i)
							getline(sstream, buf, '|');

					frames_index.push_back(stoi(buf));
				}

				fs.close();
				kframe_num =  (frames_index.size() > 0) ? (frames_index[frames_index.size()-1] + frame_jump) : 0;

			}
		}

		action = glfwGetKey(window, GLFW_KEY_N);
		if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
			if (kframe_num < frames.size()) {
				std::string buf = frames[kframe_num];
				int frno = frames_index[kframe_num];
				std::cout << "Key Frame " << kframe_num << " Frame Number " << frno << std::endl;
				
				kframe_num ++;

				setSceneState(buf);
			}
			else {
				std::cout << "no next frame available" << std::endl;
			}
		}

		action = glfwGetKey(window, GLFW_KEY_B);
		if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
			if (kframe_num > 0) {
				kframe_num --;
				
				std::string buf = frames[kframe_num];
				int frno = frames_index[kframe_num];
				std::cout << "Key Frame " << kframe_num << " Frame Number " << frno << std::endl;

				setSceneState(buf);
			}
			else {
				std::cout << "no previous frame available" << std::endl;
			}
		}

		action = glfwGetKey(window, GLFW_KEY_EQUAL);
		if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
				startPlayback();
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
	



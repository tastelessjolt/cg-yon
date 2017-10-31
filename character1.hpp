#ifndef CHAR1_HPP
#define CHAR1_HPP

#include "object.hpp"

class Character1 : public Object {

	GLfloat hipsize_l;
	GLfloat hipsize_w;
	GLfloat hipsize_h;
	GLfloat pelvissize_l;
	GLfloat pelvissize_w;
	GLfloat pelvissize_h;
	GLfloat legsize_l;
	GLfloat legsize_w;
	GLfloat legsize_h;
	GLfloat footsize_l;
	GLfloat footsize_w;
	GLfloat footsize_h;
	GLfloat abdmonesize_l;
	GLfloat abdmonesize_w;
	GLfloat abdmonesize_h;
	GLfloat necksize_l;
	GLfloat necksize_w;
	GLfloat necksize_h;
	GLfloat facesize_l;
	GLfloat facesize_w;
	GLfloat facesize_h;
	GLfloat armsize_l;
	GLfloat armsize_w;
	GLfloat armsize_h;
	GLfloat palmsize;

	glm::vec3 left_leg_angle;
	glm::mat4* left_leg_angle_matrix;
	glm::vec3 left_knee_angle;
	glm::mat4* left_knee_angle_matrix;

	glm::vec3 right_leg_angle;
	glm::mat4* right_leg_angle_matrix;
	glm::vec3 right_knee_angle;
	glm::mat4* right_knee_angle_matrix;

	glm::vec3 left_arm_angle;
	glm::mat4* left_arm_angle_matrix;
	glm::vec3 left_elbow_angle;
	glm::mat4* left_elbow_angle_matrix;

	glm::vec3 right_arm_angle;
	glm::mat4* right_arm_angle_matrix;
	glm::vec3 right_elbow_angle;
	glm::mat4* right_elbow_angle_matrix;

	glm::vec3 torso_angle;
	glm::mat4* torso_angle_matrix;

	glm::vec3 face_angle;
	glm::mat4* face_angle_matrix;

	glm::vec3 body_angle;
	glm::mat4* body_angle_matrix;

	glm::vec3 body_translate;
	glm::mat4* body_translate_matrix;


public:
	enum control_type
	{
		LEFT_LEG_ANGLE,
		LEFT_KNEE_ANGLE,
		RIGHT_LEG_ANGLE,
		RIGHT_KNEE_ANGLE,
		
		LEFT_ARM_ANGLE,
		LEFT_ELBOW_ANGLE,
		RIGHT_ARM_ANGLE,
		RIGHT_ELBOW_ANGLE,
		
		TORSO_ANGLE,
		FACE_ANGLE,

		BODY_ANGLE,
		BODY_TRANSLATE
	};

	Character1();
	void init();
	void manoeuvre(control_type, glm::vec3);
};

#endif /* CHAR1_HPP */
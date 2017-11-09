#ifndef CHAR2_HPP
#define CHAR2_HPP
#include "object.hpp"

class Character2 : public Object {
	GLfloat headband_rad;
	GLfloat headband_thickness;
	GLfloat headband_width;
	GLfloat headband_ang;
	GLfloat housing_rad;
	GLfloat earpads_rad;
	GLfloat earpads_width;
	GLfloat earpads_thickness;

	glm::vec3 body_angle;
	glm::mat4* body_angle_matrix;

	glm::vec3 body_translate;
	glm::mat4* body_translate_matrix;

	glm::vec3 left_angle; 
	glm::mat4* left_rot;

	glm::vec3 left_housing_angle;
	glm::mat4* left_housing_rot;
	
	glm::vec3 right_angle;
	glm::mat4* right_rot;
	
	glm::vec3 right_housing_angle;
	glm::mat4* right_housing_rot;

public:
	enum control_type
	{
		HEADBAND_ANGLE,
		LEFT_HOUSING_ANGLE,
		RIGHT_HOUSING_ANGLE,
		BODY_ANGLE,
		BODY_TRANSLATE
	};
	
	Character2();
	void init();
	void manoeuvre(control_type, glm::vec3);
};
#endif /* CHAR2_HPP */
#ifndef CHAR2_HPP
#define CHAR2_HPP
#include "object.hpp"

class Character2 : public Object {
	glm::vec3 body_angle;
	glm::mat4* body_angle_matrix;

	glm::vec3 body_translate;
	glm::mat4* body_translate_matrix;

	glm::mat4* left_rot;
	glm::mat4* left_housing_rot;
	glm::mat4* right_rot;
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
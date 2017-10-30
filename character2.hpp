#ifndef CHAR2_HPP
#define CHAR2_HPP
#include "object.hpp"

class Character2 : public Object {
	glm::vec3 body_angle;
	glm::mat4* body_angle_matrix;

	glm::vec3 body_translate;
	glm::mat4* body_translate_matrix;

public:
	enum control_type
	{
		LEFT_LEG_ANGLE,
		RIGHT_LEG_ANGLE,
		
		LEFT_ARM_ANGLE,
		RIGHT_ARM_ANGLE,
		
		TORSO_ANGLE,
		FACE_ANGLE,

		BODY_ANGLE,
		BODY_TRANSLATE
	};
	
	Character2();
	void init();
	void manoeuvre(control_type, glm::vec3);
};
#endif /* CHAR2_HPP */
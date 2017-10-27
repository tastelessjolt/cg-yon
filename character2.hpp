#include "object.hpp"

class Character2 : public Object {


	glm::vec3 left_leg_angle;
	glm::mat4* left_leg_angle_matrix;

	glm::vec3 right_leg_angle;
	glm::mat4* right_leg_angle_matrix;

	glm::vec3 left_arm_angle;
	glm::mat4* left_arm_angle_matrix;

	glm::vec3 right_arm_angle;
	glm::mat4* right_arm_angle_matrix;

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
	void manoeuvre(char2_control_type, glm::vec3);
};
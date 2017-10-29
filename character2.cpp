#include "character2.hpp"

extern double PI;
GLfloat pi = PI;

glm::vec3 rotateX = glm::vec3(1.0, 0.0, 0.0);
glm::vec3 rotateY = glm::vec3(0.0, 1.0, 0.0);
glm::vec3 rotateZ = glm::vec3(0.0, 0.0, 1.0);

Character2::Character2(){

}

void Character2::init(){

	// character translations

	// transforms.push_back(fullbodytrans);
	// transforms.push_back(fullbodyrot);

	

	Object::init();
}

void Character2::manoeuvre(Character2::control_type ctrl, glm::vec3 param){

	switch(ctrl){

		case LEFT_LEG_ANGLE: {
			break;
		}
		case RIGHT_LEG_ANGLE: {
			break;
		}
		
		case LEFT_ARM_ANGLE: {
			break;
		}
		case RIGHT_ARM_ANGLE: {
			break;
		}
		
		case TORSO_ANGLE: {
			break;
		}
		case FACE_ANGLE: {
			break;
		}

		case BODY_ANGLE: {
			break;
		}
		case BODY_TRANSLATE: {
			break;
		}

		default:{
			break;
		}

	}
}
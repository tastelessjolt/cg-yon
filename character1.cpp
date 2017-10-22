#include "character1.hpp"

extern double PI;
GLfloat pi = PI;

Character1::Character1(){

}

void Character1::init(){

	// character translations
	// transforms.push_back(/*fullbodytrans*/);
	// transforms.push_back(/*fullbodyrot*/);

	Primitive* hip = new Cube();
	children.push_back(hip);
	glm::mat4* hipmodel = new glm::mat4();
	hip->transforms.push_back(hipmodel);
	*hipmodel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 0.5, 0.5)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5, 0.0));


	Object* lowerbody = new Object();
	children.push_back(lowerbody);
	glm::mat4* lowerbodytrans = new glm::mat4();
	lowerbody->transforms.push_back(lowerbodytrans);

	// pelvis
	Primitive* pelvis = new Cylinder();
	lowerbody->children.push_back(pelvis);
	glm::mat4* pelvismodel = new glm::mat4();
	pelvis->transforms.push_back(pelvismodel);

	*pelvismodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.3, 0.3, 1.25));
	*pelvismodel = glm::rotate(glm::mat4(1.0f), (GLfloat)3.1415/2, glm::vec3(0.0, 1.0, 0.0)) * *pelvismodel;
	*pelvismodel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0)) * *pelvismodel;

	Object* left_leg = new Object();
	lowerbody->children.push_back(left_leg);


	glm::mat4* leftlegrot = new glm::mat4();
	left_leg->transforms.push_back(leftlegrot);
	*leftlegrot = glm::rotate(glm::mat4(1.0f), 0*pi, glm::vec3(1.0, 0.0, 0.0));	

	left_leg_angle_matrix = leftlegrot;

	Object* left_leg_comp = new Object();
	left_leg->children.push_back(left_leg_comp);

	glm::mat4* leftlegcons = new glm::mat4();
	left_leg_comp->transforms.push_back(leftlegcons);
	*leftlegcons = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25, -1.0, 0.0));

	Primitive* left_limb = new Cube();
	left_leg_comp->children.push_back(left_limb);
	
	glm::mat4* leftlimbmodel = new glm::mat4();
	left_limb->transforms.push_back(leftlimbmodel);
	*leftlimbmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 2.0, 0.5));

	Primitive* left_foot = new Cube();
	left_leg_comp->children.push_back(left_foot);

	glm::mat4* leftfootmodel = new glm::mat4();
	left_foot->transforms.push_back(leftfootmodel);
	*leftfootmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.4, 0.25, 0.6));

	glm::mat4* leftfootconstraint = new glm::mat4();
	left_foot->transforms.push_back(leftfootconstraint);
	*leftfootconstraint = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -4.0, 0.25));




	Object* right_leg = new Object();
	lowerbody->children.push_back(right_leg);


	glm::mat4* rightlegrot = new glm::mat4();
	right_leg->transforms.push_back(rightlegrot);
	*rightlegrot = glm::rotate(glm::mat4(1.0f), 0*pi, glm::vec3(1.0, 0.0, 0.0));	

	right_leg_angle_matrix = rightlegrot;

	Object* right_leg_comp = new Object();
	right_leg->children.push_back(right_leg_comp);

	glm::mat4* rightlegcons = new glm::mat4();
	right_leg_comp->transforms.push_back(rightlegcons);
	*rightlegcons = glm::translate(glm::mat4(1.0f), glm::vec3(0.25, -1.0, 0.0));

	Primitive* right_limb = new Cube();
	right_leg_comp->children.push_back(right_limb);
	
	glm::mat4* rightlimbmodel = new glm::mat4();
	right_limb->transforms.push_back(rightlimbmodel);
	*rightlimbmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 2.0, 0.5));

	Primitive* right_foot = new Cube();
	right_leg_comp->children.push_back(right_foot);

	glm::mat4* rightfootmodel = new glm::mat4();
	right_foot->transforms.push_back(rightfootmodel);
	*rightfootmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.4, 0.25, 0.6));

	glm::mat4* rightfootconstraint = new glm::mat4();
	right_foot->transforms.push_back(rightfootconstraint);
	*rightfootconstraint = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -4.0, 0.25));





	// BaseObject* parent;
	// parent = new Object();

	// glm::mat4* rotation_matrix;
	// rotation_matrix = new glm::mat4();
	// *rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));

	// parent->transforms.push_back(rotation_matrix);

	// full_body_rot = rotation_matrix;

	// BaseObject* ch1;
	// ch1 = new Cube();

	// rotation_matrix = new glm::mat4();
	// *rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));

	// ch1->transforms.push_back(rotation_matrix);


	// BaseObject* ch2;
	// ch2 = new Cylinder();

	// rotation_matrix = new glm::mat4();
	// *rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));

	// ch2->transforms.push_back(rotation_matrix);

	// elbow_rot = rotation_matrix;
	// children.push_back(parent);

	// ((Object *)parent)->children.push_back(ch1);
	// ((Object *)parent)->children.push_back(ch2);

	Object::init();
}

void Character1::manoeuvre(control_type ctrl, glm::vec3 param){

	switch(ctrl){

		case LEFT_LEG_ANGLE: {
			left_leg_angle += param;
			*left_leg_angle_matrix = glm::rotate(glm::mat4(1.0f), left_leg_angle[0], glm::vec3(1.0, 0.0, 0.0));
			break;
		}
		case RIGHT_LEG_ANGLE: {
			right_leg_angle += param;
			*right_leg_angle_matrix = glm::rotate(glm::mat4(1.0f), right_leg_angle[0], glm::vec3(1.0, 0.0, 0.0));
			break;
		}
		
		case LEFT_ARM_ANGLE: {
			left_arm_angle += param;
			*left_arm_angle_matrix = glm::rotate(glm::mat4(1.0f), left_arm_angle[0], glm::vec3(1.0, 0.0, 0.0));
			break;
		}
		case RIGHT_ARM_ANGLE: {
			right_arm_angle += param;
			*right_arm_angle_matrix = glm::rotate(glm::mat4(1.0f), right_arm_angle[0], glm::vec3(1.0, 0.0, 0.0));
			break;
		}
		
		case TORSO_ANGLE: {
			torso_angle += param;
			*torso_angle_matrix = glm::rotate(glm::mat4(1.0f), torso_angle[1], glm::vec3(0.0, 1.0, 0.0));
			break;
		}
		case FACE_ANGLE: {
			face_angle += param;
			*face_angle_matrix = glm::rotate(glm::mat4(1.0f), face_angle[1], glm::vec3(0.0, 1.0, 0.0));
			break;
		}

		case BODY_ANGLE: {
			body_angle += param;
			*body_angle_matrix = glm::rotate(glm::mat4(1.0f), body_angle[0], glm::vec3(1.0, 0.0, 0.0));
			*body_angle_matrix = glm::rotate(*body_angle_matrix, body_angle[1], glm::vec3(0.0, 1.0, 0.0));
			*body_angle_matrix = glm::rotate(*body_angle_matrix, body_angle[2], glm::vec3(0.0, 0.0, 1.0));
			break;
		}
		case BODY_TRANSLATE: {
			body_translate += param;
			*body_translate_matrix = glm::translate(glm::mat4(1.0f), body_translate);
			break;
		}

		default:{
			break;
		}

	}
	// *llrot = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0, 0.0, 0.0));	

	// // std::cout << xrot << " " << yrot << " " << zrot << " " << std::endl;
	// glm::mat4* rotation_matrix=elbow_rot;

	// *rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));


	// rotation_matrix=children[0]->transforms[0];
	// std::cout << (*rotation_matrix)[0][0] << std::endl;
}
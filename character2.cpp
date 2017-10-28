#include "character2.hpp"

extern double PI;
GLfloat pi = PI;

Character2::Character2(){

}

void Character2::init(){

	// character translations

	// transforms.push_back(fullbodytrans);
	// transforms.push_back(fullbodyrot);

	// hip primitive
	Primitive* hip = new Cube();
	children.push_back(hip);
	glm::mat4* hipmodel = new glm::mat4();
	hip->transforms.push_back(hipmodel);
	*hipmodel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 0.25, 0.5));

	//lower body
	Object* lowerbody = new Object();
	children.push_back(lowerbody);
	glm::mat4* lowerbodytrans = new glm::mat4();
	*lowerbodytrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -0.25, 0.0));
	lowerbody->transforms.push_back(lowerbodytrans);
	

	Object* pelvis_legs = new Object();
	lowerbody->children.push_back(pelvis_legs);

	// pelvis
	Primitive* pelvis = new Cylinder();
	pelvis_legs->children.push_back(pelvis);
	glm::mat4* pelvismodel = new glm::mat4();
	pelvis->transforms.push_back(pelvismodel);

	*pelvismodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.3, 0.3, 1.25));
	*pelvismodel = glm::rotate(glm::mat4(1.0f), pi/2, glm::vec3(0.0, 1.0, 0.0)) * *pelvismodel;


	// left leg
	Object* left_leg = new Object();
	pelvis_legs->children.push_back(left_leg);

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


	// right leg
	Object* right_leg = new Object();
	pelvis_legs->children.push_back(right_leg);

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


	// upper body
	Object* upperbody = new Object();
	children.push_back(upperbody);

	glm::mat4* upperbodyrot = new glm::mat4();
	upperbody->transforms.push_back(upperbodyrot);
	*upperbodyrot = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0, 1.0, 0.0));

	torso_angle_matrix = upperbodyrot;

	glm::mat4* upperbodytrans = new glm::mat4();
	upperbody->transforms.push_back(upperbodytrans);
	*upperbodytrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.75, 0.0));

	// abdomen
	Primitive* abdomen = new Cube();
	upperbody->children.push_back(abdomen);

	glm::mat4* abdomenmodel = new glm::mat4();
	abdomen->transforms.push_back(abdomenmodel);
	*abdomenmodel = glm::scale(glm::mat4(1.0f), glm::vec3(1.10, 1.5, 0.60));

	// head
	Object* head = new Object();
	upperbody->children.push_back(head);

	glm::mat4* headtranslate = new glm::mat4();
	head->transforms.push_back(headtranslate);
	*headtranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.10, 0.0));

	Primitive* neck = new Cylinder();
	head->children.push_back(neck);
	glm::mat4* neckmodel = new glm::mat4();
	neck->transforms.push_back(neckmodel);
	*neckmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.75));
	*neckmodel = glm::rotate(glm::mat4(1.0f), pi/2, glm::vec3(1.0, 0.0, 0.0)) * *neckmodel;

	Primitive* face = new Cylinder();
	head->children.push_back(face);

	glm::mat4* facerotate = new glm::mat4();
	face->transforms.push_back(facerotate);
	*facerotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0, 1.0, 0.0));

	face_angle_matrix = facerotate;

	glm::mat4* facemodel = new glm::mat4();
	face->transforms.push_back(facemodel);
	*facemodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.35, 0.35, 0.65));
	*facemodel = glm::rotate(glm::mat4(1.0f), pi/2, glm::vec3(1.0, 0.0, 0.0)) * *facemodel;


	// shoulders left
	Object* leftshoulder = new Object();
	upperbody->children.push_back(leftshoulder);
	glm::mat4* leftshouldertrans = new glm::mat4();
	leftshoulder->transforms.push_back(leftshouldertrans);
	*leftshouldertrans = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5, 0.5, 0.0));

	glm::mat4* leftshoulderrot = new glm::mat4();
	leftshoulder->transforms.push_back(leftshoulderrot);
	*leftshoulderrot = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0, 0.0, 0.0));

	left_arm_angle_matrix = leftshoulderrot;

	glm::mat4* leftshoulderrot1 = new glm::mat4();
	leftshoulder->transforms.push_back(leftshoulderrot1);
	*leftshoulderrot1 = 	glm::rotate(glm::mat4(1.0f), -pi/8, glm::vec3(0.0, 0.0, 1.0))
						* 	glm::rotate(glm::mat4(1.0f), pi/2, glm::vec3(1.0, 0.0, 0.0));

	glm::mat4* leftshouldertrans1 = new glm::mat4();
	leftshoulder->transforms.push_back(leftshouldertrans1);
	*leftshouldertrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.75));

	Primitive* leftpalm = new Sphere();
	leftshoulder->children.push_back(leftpalm);
	glm::mat4* leftpalmmodel = new glm::mat4();
	leftpalm->transforms.push_back(leftpalmmodel);
	*leftpalmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.20, 0.20, 0.20));
	*leftpalmmodel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.8)) * *leftpalmmodel;

	Primitive* leftarm = new Cylinder();
	leftshoulder->children.push_back(leftarm);
	glm::mat4* leftarmmodel = new glm::mat4();
	leftarm->transforms.push_back(leftarmmodel);
	*leftarmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.15, 0.15, 1.5));


	// shoulders right
	Object* rightshoulder = new Object();
	upperbody->children.push_back(rightshoulder);
	glm::mat4* rightshouldertrans = new glm::mat4();
	rightshoulder->transforms.push_back(rightshouldertrans);
	*rightshouldertrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.0));

	glm::mat4* rightshoulderrot = new glm::mat4();
	rightshoulder->transforms.push_back(rightshoulderrot);
	*rightshoulderrot = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0, 0.0, 0.0));

	right_arm_angle_matrix = rightshoulderrot;

	glm::mat4* rightshoulderrot1 = new glm::mat4();
	rightshoulder->transforms.push_back(rightshoulderrot1);
	*rightshoulderrot1 = 	glm::rotate(glm::mat4(1.0f), pi/8, glm::vec3(0.0, 0.0, 1.0))
						* 	glm::rotate(glm::mat4(1.0f), pi/2, glm::vec3(1.0, 0.0, 0.0));

	glm::mat4* rightshouldertrans1 = new glm::mat4();
	rightshoulder->transforms.push_back(rightshouldertrans1);
	*rightshouldertrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.75));

	Primitive* rightpalm = new Sphere();
	rightshoulder->children.push_back(rightpalm);
	glm::mat4* rightpalmmodel = new glm::mat4();
	rightpalm->transforms.push_back(rightpalmmodel);
	*rightpalmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.20, 0.20, 0.20));
	*rightpalmmodel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.8)) * *rightpalmmodel;

	Primitive* rightarm = new Cylinder();
	rightshoulder->children.push_back(rightarm);
	glm::mat4* rightarmmodel = new glm::mat4();
	rightarm->transforms.push_back(rightarmmodel);
	*rightarmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(0.15, 0.15, 1.5));




	Object::init();
}

void Character2::manoeuvre(Character2::control_type ctrl, glm::vec3 param){

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
#include "character1.hpp"

extern double PI;
GLfloat pi = PI;

glm::vec3 rotateX = glm::vec3(1.0, 0.0, 0.0);
glm::vec3 rotateY = glm::vec3(0.0, 1.0, 0.0);
glm::vec3 rotateZ = glm::vec3(0.0, 0.0, 1.0);

Character1::Character1(){
	// sizes 
	hipsize_l = 0.5;
	hipsize_w = 1.0;
	hipsize_h = 0.25;

	pelvissize_l = 0.6;
	pelvissize_w = 1.25;
	pelvissize_h = 0.6;

	legsize_l = 0.5;
	legsize_w = 0.5;
	legsize_h = 2.0;

	footsize_l = 0.6;
	footsize_w = 0.4;
	footsize_h = 0.25;

	abdmonesize_l = 0.60;
	abdmonesize_w = 1.10;
	abdmonesize_h = 1.5;

	necksize_l = 0.5;
	necksize_w = 0.5;
	necksize_h = 0.75;

	facesize_l = 0.7;
	facesize_w = 0.7;
	facesize_h = 0.65;

	armsize_l = 0.3;
	armsize_w = 0.3;
	armsize_h = 1.5;

	palmsize = 0.4;

	left_leg_angle = glm::vec3(0.0, 0.0, 0.0);
	left_knee_angle = glm::vec3(0.0, 0.0, 0.0);

	right_leg_angle = glm::vec3(0.0, 0.0, 0.0);
	right_knee_angle = glm::vec3(0.0, 0.0, 0.0);

	left_arm_angle = glm::vec3(0.0, 0.0, 0.0);
	left_elbow_angle = glm::vec3(0.0, 0.0, 0.0);

	right_arm_angle = glm::vec3(0.0, 0.0, 0.0);
	right_elbow_angle = glm::vec3(0.0, 0.0, 0.0);

	torso_angle = glm::vec3(0.0, 0.0, 0.0);

	face_angle = glm::vec3(0.0, 0.0, 0.0);

	body_angle = glm::vec3(0.0, 0.0, 0.0);

	body_translate = glm::vec3(0.0, 0.0, 0.0);

}

void Character1::init(){

	// character translations
	glm::mat4* fullbodytrans = new glm::mat4(1.0f);
	transforms.push_back(fullbodytrans);
	body_translate_matrix = fullbodytrans;

	glm::mat4* fullbodyrot = new glm::mat4(1.0f);
	transforms.push_back(fullbodyrot);
	body_angle_matrix = fullbodyrot;

	// hip primitive
	Primitive* hip = new Cube();
	children.push_back(hip);
	glm::mat4* hipmodel = new glm::mat4();
	hip->transforms.push_back(hipmodel);
	*hipmodel = glm::scale(glm::mat4(1.0f), glm::vec3(hipsize_w, hipsize_h, hipsize_l));

	//lower body
	Object* lowerbody = new Object();
	children.push_back(lowerbody);
	glm::mat4* lowerbodytrans = new glm::mat4();
	*lowerbodytrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -hipsize_h, 0.0));
	lowerbody->transforms.push_back(lowerbodytrans);
	

	Object* pelvis_legs = new Object();
	lowerbody->children.push_back(pelvis_legs);

	// pelvis
	Primitive* pelvis = new Cylinder();
	pelvis_legs->children.push_back(pelvis);
	glm::mat4* pelvismodel = new glm::mat4();
	pelvis->transforms.push_back(pelvismodel);

	*pelvismodel = glm::scale(glm::mat4(1.0f), glm::vec3(pelvissize_h, pelvissize_l, pelvissize_w));
	*pelvismodel = glm::rotate(glm::mat4(1.0f), pi/2, rotateY) * *pelvismodel;


	// left leg
	Object* left_leg = new Object();
	pelvis_legs->children.push_back(left_leg);

	Object* left_leg_comp = new Object();
	left_leg->children.push_back(left_leg_comp);

	glm::mat4* leftlegcons = new glm::mat4();
	left_leg_comp->transforms.push_back(leftlegcons);
	*leftlegcons = glm::translate(glm::mat4(1.0f), glm::vec3(-pelvissize_w/4, 0.0, 0.0));

	glm::mat4* leftlegrot = new glm::mat4();
	left_leg_comp->transforms.push_back(leftlegrot);
	*leftlegrot = glm::rotate(glm::mat4(1.0f), (GLfloat)0.0, rotateX);

	glm::mat4* leftlegcons1 = new glm::mat4();
	left_leg_comp->transforms.push_back(leftlegcons1);
	*leftlegcons1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, 0.0));

	left_leg_angle_matrix = leftlegrot;

	// left thigh
	Primitive* left_thigh = new Cube();
	left_leg_comp->children.push_back(left_thigh);

	left_thigh->settexture("textures/thigh.bmp", 115, 116);
	
	glm::mat4* leftthighmodel = new glm::mat4();
	left_thigh->transforms.push_back(leftthighmodel);
	*leftthighmodel = glm::scale(glm::mat4(1.0f), glm::vec3(legsize_w, legsize_h/2, legsize_l));

	// left knee
	Object* left_knee = new Object();
	left_leg_comp->children.push_back(left_knee);

	glm::mat4* leftkneerot_trans = new glm::mat4();
	left_knee->transforms.push_back(leftkneerot_trans);
	*leftkneerot_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, 0.0));

	glm::mat4* leftkneerot = new glm::mat4();
	left_knee->transforms.push_back(leftkneerot);
	*leftkneerot = glm::rotate(glm::mat4(1.0f), (GLfloat)0.0, rotateX);
	left_knee_angle_matrix = leftkneerot;

	glm::mat4* leftkneeconstraint = new glm::mat4();
	left_knee->transforms.push_back(leftkneeconstraint);
	*leftkneeconstraint = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, 0.0));

	Primitive* lknee = new Sphere();
	left_knee->children.push_back(lknee);

	lknee->settexture("textures/knee.bmp", 80, 80);

	glm::mat4* lknee_model = new glm::mat4();
	lknee->transforms.push_back(lknee_model);
	*lknee_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, legsize_h/4, 0.0)) * 
					glm::scale(glm::mat4(1.0f), glm::vec3(legsize_w * 1.2, legsize_w * 1.2, legsize_w * 1.2));

	// left limb
	Primitive* left_limb = new Cube();
	left_knee->children.push_back(left_limb);

	left_limb->settexture("textures/leg.bmp", 118, 124);
	
	glm::mat4* leftlimbmodel = new glm::mat4();
	left_limb->transforms.push_back(leftlimbmodel);
	*leftlimbmodel = glm::scale(glm::mat4(1.0f), glm::vec3(legsize_w, legsize_h/2, legsize_l));

	// left foot
	Primitive* left_foot = new Cube();
	left_knee->children.push_back(left_foot);

	glm::mat4* leftfootconstraint = new glm::mat4();
	left_foot->transforms.push_back(leftfootconstraint);
	*leftfootconstraint = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, legsize_h/16));

	glm::mat4* leftfootmodel = new glm::mat4();
	left_foot->transforms.push_back(leftfootmodel);
	*leftfootmodel = glm::scale(glm::mat4(1.0f), glm::vec3(footsize_w, footsize_h, footsize_l));


	// right leg
	Object* right_leg = new Object();
	pelvis_legs->children.push_back(right_leg);

	Object* right_leg_comp = new Object();
	right_leg->children.push_back(right_leg_comp);

	glm::mat4* rightlegcons = new glm::mat4();
	right_leg_comp->transforms.push_back(rightlegcons);
	*rightlegcons = glm::translate(glm::mat4(1.0f), glm::vec3(pelvissize_w/4, 0.0, 0.0));

	glm::mat4* rightlegrot = new glm::mat4();
	right_leg_comp->transforms.push_back(rightlegrot);
	*rightlegrot = glm::rotate(glm::mat4(1.0f), (GLfloat)0.0, rotateX);

	glm::mat4* rightlegcons1 = new glm::mat4();
	right_leg_comp->transforms.push_back(rightlegcons1);
	*rightlegcons1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, 0.0));	

	right_leg_angle_matrix = rightlegrot;

	// right thigh
	Primitive* right_thigh = new Cube();
	right_leg_comp->children.push_back(right_thigh);
	
	right_thigh->settexture("textures/thigh.bmp", 115, 116);

	glm::mat4* rightthighmodel = new glm::mat4();
	right_thigh->transforms.push_back(rightthighmodel);
	*rightthighmodel = glm::scale(glm::mat4(1.0f), glm::vec3(legsize_w, legsize_h/2, legsize_l));

	// right knee
	Object* right_knee = new Object();
	right_leg_comp->children.push_back(right_knee);

	glm::mat4* rightkneerot_trans = new glm::mat4();
	right_knee->transforms.push_back(rightkneerot_trans);
	*rightkneerot_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, 0.0));

	glm::mat4* rightkneerot = new glm::mat4();
	right_knee->transforms.push_back(rightkneerot);
	*rightkneerot = glm::rotate(glm::mat4(1.0f), (GLfloat)0.0, rotateX);
	right_knee_angle_matrix = rightkneerot;

	glm::mat4* rightkneeconstraint = new glm::mat4();
	right_knee->transforms.push_back(rightkneeconstraint);
	*rightkneeconstraint = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, 0.0));

	Primitive* rknee = new Sphere();
	right_knee->children.push_back(rknee);

	rknee->settexture("textures/knee.bmp", 80, 80);

	glm::mat4* rknee_model = new glm::mat4();
	rknee->transforms.push_back(rknee_model);
	*rknee_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, legsize_h/4, 0.0)) * 
					glm::scale(glm::mat4(1.0f), glm::vec3(legsize_w * 1.2, legsize_w * 1.2, legsize_w * 1.2));

	// right limb
	Primitive* right_limb = new Cube();
	right_knee->children.push_back(right_limb);

	right_limb->settexture("textures/leg.bmp", 118, 124);

	glm::mat4* rightlimbmodel = new glm::mat4();
	right_limb->transforms.push_back(rightlimbmodel);
	*rightlimbmodel = glm::scale(glm::mat4(1.0f), glm::vec3(legsize_w, legsize_h/2, legsize_l));

	// right foot
	Primitive* right_foot = new Cube();
	right_knee->children.push_back(right_foot);

	glm::mat4* rightfootconstraint = new glm::mat4();
	right_foot->transforms.push_back(rightfootconstraint);
	*rightfootconstraint = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -legsize_h/4, legsize_h/16));

	glm::mat4* rightfootmodel = new glm::mat4();
	right_foot->transforms.push_back(rightfootmodel);
	*rightfootmodel = glm::scale(glm::mat4(1.0f), glm::vec3(footsize_w, footsize_h, footsize_l));


	// upper body
	Object* upperbody = new Object();
	children.push_back(upperbody);

	glm::mat4* upperbodyrot = new glm::mat4();
	upperbody->transforms.push_back(upperbodyrot);
	*upperbodyrot = glm::rotate(glm::mat4(1.0f), 0.0f, rotateY);

	torso_angle_matrix = upperbodyrot;

	glm::mat4* upperbodytrans = new glm::mat4();
	upperbody->transforms.push_back(upperbodytrans);
	*upperbodytrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, abdmonesize_h/2, 0.0));

	// abdomen
	Primitive* abdomen = new Cube();
	upperbody->children.push_back(abdomen);
	abdomen->settexture("textures/shirt.bmp", 274, 223);

	glm::mat4* abdomenmodel = new glm::mat4();
	abdomen->transforms.push_back(abdomenmodel);
	*abdomenmodel = glm::scale(glm::mat4(1.0f), glm::vec3(abdmonesize_w, abdmonesize_h, abdmonesize_l));

	// head
	Object* head = new Object();
	upperbody->children.push_back(head);

	glm::mat4* headtranslate = new glm::mat4();
	head->transforms.push_back(headtranslate);
	*headtranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, abdmonesize_h/2 + necksize_h/2, 0.0));

	Primitive* neck = new Cylinder();
	head->children.push_back(neck);

	glm::mat4* neckmodel = new glm::mat4();
	neck->transforms.push_back(neckmodel);
	*neckmodel = glm::rotate(glm::mat4(1.0f), -pi/2, rotateX);
	*neckmodel = glm::scale(glm::mat4(1.0f), glm::vec3(necksize_w, necksize_h, necksize_l)) * *neckmodel;

	Primitive* face = new Cylinder();
	head->children.push_back(face);
	face->settexture("textures/face.bmp", 640, 320);

	glm::mat4* facerotate = new glm::mat4();
	face->transforms.push_back(facerotate);
	*facerotate = glm::rotate(glm::mat4(1.0f), pi/2, rotateY);

	face_angle_matrix = facerotate;

	glm::mat4* facemodel = new glm::mat4();
	face->transforms.push_back(facemodel);
	*facemodel = glm::rotate(glm::mat4(1.0f), -pi/2, rotateX);
	*facemodel = glm::scale(glm::mat4(1.0f), glm::vec3(facesize_w, facesize_h, facesize_l)) * *facemodel;


	// shoulders left
	Object* leftshoulder = new Object();
	upperbody->children.push_back(leftshoulder);
	glm::mat4* leftshouldertrans = new glm::mat4();
	leftshoulder->transforms.push_back(leftshouldertrans);
	*leftshouldertrans = glm::translate(glm::mat4(1.0f), glm::vec3(-abdmonesize_w/2, abdmonesize_h/2 - 0.25, 0.0));

	glm::mat4* leftshoulderrot = new glm::mat4();
	leftshoulder->transforms.push_back(leftshoulderrot);
	*leftshoulderrot = glm::rotate(glm::mat4(1.0f), 0.0f, rotateX);

	left_arm_angle_matrix = leftshoulderrot;

	glm::mat4* leftshoulderrot1 = new glm::mat4();
	leftshoulder->transforms.push_back(leftshoulderrot1);
	*leftshoulderrot1 = 	glm::rotate(glm::mat4(1.0f), -pi/8, rotateZ)
						* 	glm::rotate(glm::mat4(1.0f), pi/2, rotateX);

	glm::mat4* leftshouldertrans1 = new glm::mat4();
	leftshoulder->transforms.push_back(leftshouldertrans1);
	*leftshouldertrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4));
	
	Object* leftarm = new Object();
	leftshoulder->children.push_back(leftarm);

	Primitive* leftarmthigh = new Cylinder();
	leftarm->children.push_back(leftarmthigh);
	glm::mat4* leftarmthighmodel = new glm::mat4();
	leftarmthigh->transforms.push_back(leftarmthighmodel);
	*leftarmthighmodel = glm::scale(glm::mat4(1.0f), glm::vec3(armsize_w, armsize_l, armsize_h/2));

	Object* leftelbow = new Object();
	leftarm->children.push_back(leftelbow);
	glm::mat4* leftarm_elbow_rot_trans = new glm::mat4();
	leftelbow->transforms.push_back(leftarm_elbow_rot_trans);
	*leftarm_elbow_rot_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4));

	glm::mat4* leftarm_elbow_rot = new glm::mat4();
	leftelbow->transforms.push_back(leftarm_elbow_rot);
	*leftarm_elbow_rot = glm::rotate(glm::mat4(1.0f), (GLfloat)0.0, rotateY);
	left_elbow_angle_matrix = leftarm_elbow_rot;

	glm::mat4* leftarm_elbow_trans = new glm::mat4();
	leftelbow->transforms.push_back(leftarm_elbow_trans);
	*leftarm_elbow_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4));
	
	Primitive* left_elbow = new Sphere();
	leftelbow->children.push_back(left_elbow);

	glm::mat4* leftelbowscale = new glm::mat4();
	left_elbow->transforms.push_back(leftelbowscale);
	*leftelbowscale = glm::scale(glm::mat4(1.0f), glm::vec3(armsize_w * 1.2, armsize_w * 1.2, armsize_w * 1.2)) * 
						glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3 * armsize_h/4));

	Primitive* leftarm_elbow = new Cylinder();
	leftelbow->children.push_back(leftarm_elbow);
	glm::mat4* leftarmmodel = new glm::mat4();
	leftarm_elbow->transforms.push_back(leftarmmodel);
	*leftarmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(armsize_w, armsize_l, armsize_h/2));

	Primitive* leftpalm = new Sphere();
	leftelbow->children.push_back(leftpalm);
	glm::mat4* leftpalmmodel = new glm::mat4();
	leftpalm->transforms.push_back(leftpalmmodel);
	*leftpalmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(palmsize, palmsize, palmsize));
	*leftpalmmodel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4 + palmsize/8)) * *leftpalmmodel;



	// shoulders right
	Object* rightshoulder = new Object();
	upperbody->children.push_back(rightshoulder);
	glm::mat4* rightshouldertrans = new glm::mat4();
	rightshoulder->transforms.push_back(rightshouldertrans);
	*rightshouldertrans = glm::translate(glm::mat4(1.0f), glm::vec3(abdmonesize_w/2, abdmonesize_h/2 - 0.25, 0.0));

	glm::mat4* rightshoulderrot = new glm::mat4();
	rightshoulder->transforms.push_back(rightshoulderrot);
	*rightshoulderrot = glm::rotate(glm::mat4(1.0f), 0.0f, rotateX);

	right_arm_angle_matrix = rightshoulderrot;

	glm::mat4* rightshoulderrot1 = new glm::mat4();
	rightshoulder->transforms.push_back(rightshoulderrot1);
	*rightshoulderrot1 = 	glm::rotate(glm::mat4(1.0f), pi/8, rotateZ)
						* 	glm::rotate(glm::mat4(1.0f), pi/2, rotateX);

	glm::mat4* rightshouldertrans1 = new glm::mat4();
	rightshoulder->transforms.push_back(rightshouldertrans1);
	*rightshouldertrans1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4));

	Object* rightarm = new Object();
	rightshoulder->children.push_back(rightarm);

	Primitive* rightarmthigh = new Cylinder();
	rightarm->children.push_back(rightarmthigh);
	glm::mat4* rightarmthighmodel = new glm::mat4();
	rightarmthigh->transforms.push_back(rightarmthighmodel);
	*rightarmthighmodel = glm::scale(glm::mat4(1.0f), glm::vec3(armsize_w, armsize_l, armsize_h/2));

	Object* rightelbow = new Object();
	rightarm->children.push_back(rightelbow);
	glm::mat4* rightarm_elbow_rot_trans = new glm::mat4();
	rightelbow->transforms.push_back(rightarm_elbow_rot_trans);
	*rightarm_elbow_rot_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4));

	glm::mat4* rightarm_elbow_rot = new glm::mat4();
	rightelbow->transforms.push_back(rightarm_elbow_rot);
	*rightarm_elbow_rot = glm::rotate(glm::mat4(1.0f), (GLfloat)0.0, rotateY);
	right_elbow_angle_matrix = rightarm_elbow_rot;

	glm::mat4* rightarm_elbow_trans = new glm::mat4();
	rightelbow->transforms.push_back(rightarm_elbow_trans);
	*rightarm_elbow_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4));
	
	Primitive* right_elbow = new Sphere();
	rightelbow->children.push_back(right_elbow);

	glm::mat4* rightelbowscale = new glm::mat4();
	right_elbow->transforms.push_back(rightelbowscale);
	*rightelbowscale = glm::scale(glm::mat4(1.0f), glm::vec3(armsize_w * 1.2, armsize_w * 1.2, armsize_w * 1.2)) * 
						glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3 * armsize_h/4));

	Primitive* rightarm_elbow = new Cylinder();
	rightelbow->children.push_back(rightarm_elbow);
	glm::mat4* rightarmmodel = new glm::mat4();
	rightarm_elbow->transforms.push_back(rightarmmodel);
	*rightarmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(armsize_w, armsize_l, armsize_h/2));

	Primitive* rightpalm = new Sphere();
	rightelbow->children.push_back(rightpalm);
	glm::mat4* rightpalmmodel = new glm::mat4();
	rightpalm->transforms.push_back(rightpalmmodel);
	*rightpalmmodel = glm::scale(glm::mat4(1.0f), glm::vec3(palmsize, palmsize, palmsize));
	*rightpalmmodel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, armsize_h/4 + palmsize/8)) * *rightpalmmodel;

	Object::init();
}

void Character1::manoeuvre(Character1::control_type ctrl, glm::vec3 param){

	switch(ctrl){

		case LEFT_LEG_ANGLE: {
			left_leg_angle += param;
			*left_leg_angle_matrix = glm::rotate(glm::mat4(1.0f), left_leg_angle[0], rotateX);
			*left_leg_angle_matrix = glm::rotate(*left_leg_angle_matrix, left_leg_angle[1], rotateY);
			*left_leg_angle_matrix = glm::rotate(*left_leg_angle_matrix, left_leg_angle[2], rotateZ);
			break;
		}
		case RIGHT_LEG_ANGLE: {
			right_leg_angle += param;
			*right_leg_angle_matrix = glm::rotate(glm::mat4(1.0f), right_leg_angle[0], rotateX);
			*right_leg_angle_matrix = glm::rotate(*right_leg_angle_matrix, right_leg_angle[1], rotateY);
			*right_leg_angle_matrix = glm::rotate(*right_leg_angle_matrix, right_leg_angle[2], rotateZ);
			break;
		}

		
		case LEFT_KNEE_ANGLE: {
			left_knee_angle += param;
			*left_knee_angle_matrix = glm::rotate(glm::mat4(1.0f), left_knee_angle[0], rotateX);
			break;
		}
		case RIGHT_KNEE_ANGLE: {
			right_knee_angle += param;
			*right_knee_angle_matrix = glm::rotate(glm::mat4(1.0f), right_knee_angle[0], rotateX);
			break;
		}

		
		case LEFT_ARM_ANGLE: {
			left_arm_angle += param;
			*left_arm_angle_matrix = glm::rotate(glm::mat4(1.0f), left_arm_angle[0], rotateX);
			*left_arm_angle_matrix = glm::rotate(*left_arm_angle_matrix, left_arm_angle[1], rotateY);
			*left_arm_angle_matrix = glm::rotate(*left_arm_angle_matrix, left_arm_angle[2], rotateZ);
			break;
		}
		case RIGHT_ARM_ANGLE: {
			right_arm_angle += param;
			*right_arm_angle_matrix = glm::rotate(glm::mat4(1.0f), right_arm_angle[0], rotateX);
			*right_arm_angle_matrix = glm::rotate(*right_arm_angle_matrix, right_arm_angle[1], rotateY);
			*right_arm_angle_matrix = glm::rotate(*right_arm_angle_matrix, right_arm_angle[2], rotateZ);
			break;
		}

		case LEFT_ELBOW_ANGLE: {
			left_elbow_angle += param;
			*left_elbow_angle_matrix = glm::rotate(glm::mat4(1.0f), left_elbow_angle[1], rotateY);
			break;
		}
		case RIGHT_ELBOW_ANGLE: {
			right_elbow_angle += param;
			*right_elbow_angle_matrix = glm::rotate(glm::mat4(1.0f), right_elbow_angle[1], rotateY);
			break;
		}

		case TORSO_ANGLE: {
			torso_angle += param;
			*torso_angle_matrix = glm::rotate(glm::mat4(1.0f), torso_angle[1], rotateY);
			break;
		}
		case FACE_ANGLE: {
			face_angle += param;
			*face_angle_matrix = glm::rotate(glm::mat4(1.0f), face_angle[1], rotateY);
			break;
		}

		case BODY_ANGLE: {
			body_angle += param;
			*body_angle_matrix = glm::rotate(glm::mat4(1.0f), body_angle[0], rotateX);
			*body_angle_matrix = glm::rotate(*body_angle_matrix, body_angle[1], rotateY);
			*body_angle_matrix = glm::rotate(*body_angle_matrix, body_angle[2], rotateZ);
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
	// *llrot = glm::rotate(glm::mat4(1.0f), rot[0], rotateX);	

	// // std::cout << xrot << " " << yrot << " " << zrot << " " << std::endl;
	// glm::mat4* rotation_matrix=elbow_rot;

	// *rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	// *rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));


	// rotation_matrix=children[0]->transforms[0];
	// std::cout << (*rotation_matrix)[0][0] << std::endl;
}

std::string Character1::getState() {
	std::stringstream stream;
	stream << left_leg_angle[0] << "," << left_leg_angle[1] << "," << left_leg_angle[2] << ",";
	stream << left_knee_angle[0] << "," << left_knee_angle[1] << "," << left_knee_angle[2] << ",";
	stream << right_leg_angle[0] << "," << right_leg_angle[1] << "," << right_leg_angle[2] << ",";
	stream << right_knee_angle[0] << "," << right_knee_angle[1] << "," << right_knee_angle[2] << ",";
	stream << left_arm_angle[0] << "," << left_arm_angle[1] << "," << left_arm_angle[2] << ",";
	stream << left_elbow_angle[0] << "," << left_elbow_angle[1] << "," << left_elbow_angle[2] << ",";
	stream << right_arm_angle[0] << "," << right_arm_angle[1] << "," << right_arm_angle[2] << ",";
	stream << right_elbow_angle[0] << "," << right_elbow_angle[1] << "," << right_elbow_angle[2] << ",";
	stream << torso_angle[0] << "," << torso_angle[1] << "," << torso_angle[2] << ",";
	stream << face_angle[0] << "," << face_angle[1] << "," << face_angle[2] << ",";
	stream << body_angle[0] << "," << body_angle[1] << "," << body_angle[2] << ",";
	stream << body_translate[0] << "," << body_translate[1] << "," << body_translate[2];

	return stream.str();
}

void Character1::setState(std::string state) {
	std::stringstream sstream(state);
	std::string token;

	getline(sstream, token, ',');
	left_leg_angle[0] = stof(token);
	getline(sstream, token, ',');
	left_leg_angle[1] = stof(token);
	getline(sstream, token, ',');
	left_leg_angle[2] = stof(token);

	getline(sstream, token, ',');
	left_knee_angle[0] = stof(token);
	getline(sstream, token, ',');
	left_knee_angle[1] = stof(token);
	getline(sstream, token, ',');
	left_knee_angle[2] = stof(token);

	getline(sstream, token, ',');
	right_leg_angle[0] = stof(token);
	getline(sstream, token, ',');
	right_leg_angle[1] = stof(token);
	getline(sstream, token, ',');
	right_leg_angle[2] = stof(token);

	getline(sstream, token, ',');
	right_knee_angle[0] = stof(token);
	getline(sstream, token, ',');
	right_knee_angle[1] = stof(token);
	getline(sstream, token, ',');
	right_knee_angle[2] = stof(token);

	getline(sstream, token, ',');
	left_arm_angle[0] = stof(token);
	getline(sstream, token, ',');
	left_arm_angle[1] = stof(token);
	getline(sstream, token, ',');
	left_arm_angle[2] = stof(token);

	getline(sstream, token, ',');
	left_elbow_angle[0] = stof(token);
	getline(sstream, token, ',');
	left_elbow_angle[1] = stof(token);
	getline(sstream, token, ',');
	left_elbow_angle[2] = stof(token);

	getline(sstream, token, ',');
	right_arm_angle[0] = stof(token);
	getline(sstream, token, ',');
	right_arm_angle[1] = stof(token);
	getline(sstream, token, ',');
	right_arm_angle[2] = stof(token);

	getline(sstream, token, ',');
	right_elbow_angle[0] = stof(token);
	getline(sstream, token, ',');
	right_elbow_angle[1] = stof(token);
	getline(sstream, token, ',');
	right_elbow_angle[2] = stof(token);

	getline(sstream, token, ',');
	torso_angle[0] = stof(token);
	getline(sstream, token, ',');
	torso_angle[1] = stof(token);
	getline(sstream, token, ',');
	torso_angle[2] = stof(token);

	getline(sstream, token, ',');
	face_angle[0] = stof(token);
	getline(sstream, token, ',');
	face_angle[1] = stof(token);
	getline(sstream, token, ',');
	face_angle[2] = stof(token);

	getline(sstream, token, ',');
	body_angle[0] = stof(token);
	getline(sstream, token, ',');
	body_angle[1] = stof(token);
	getline(sstream, token, ',');
	body_angle[2] = stof(token);

	getline(sstream, token, ',');
	body_translate[0] = stof(token);
	getline(sstream, token, ',');
	body_translate[1] = stof(token);
	getline(sstream, token, ',');
	body_translate[2] = stof(token);

	manoeuvre(LEFT_LEG_ANGLE, glm::vec3(0.0f));
	manoeuvre(RIGHT_LEG_ANGLE, glm::vec3(0.0f));
	manoeuvre(LEFT_KNEE_ANGLE, glm::vec3(0.0f));
	manoeuvre(RIGHT_KNEE_ANGLE, glm::vec3(0.0f));
	manoeuvre(LEFT_ARM_ANGLE, glm::vec3(0.0f));
	manoeuvre(RIGHT_ARM_ANGLE, glm::vec3(0.0f));
	manoeuvre(LEFT_ELBOW_ANGLE, glm::vec3(0.0f));
	manoeuvre(RIGHT_ELBOW_ANGLE, glm::vec3(0.0f));
	manoeuvre(TORSO_ANGLE, glm::vec3(0.0f));
	manoeuvre(FACE_ANGLE, glm::vec3(0.0f));
	manoeuvre(BODY_ANGLE, glm::vec3(0.0f));
	manoeuvre(BODY_TRANSLATE, glm::vec3(0.0f));
}
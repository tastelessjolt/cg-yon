#include "character2.hpp"

extern GLfloat pi;

extern glm::vec3 rotateX;
extern glm::vec3 rotateY;
extern glm::vec3 rotateZ;

Character2::Character2(){

}

void Character2::init(){

	// character translations

	// transforms.push_back(fullbodytrans);
	// transforms.push_back(fullbodyrot);

	// headband
	GLfloat headband_rad = 1.0;
	GLfloat headband_thickness = 0.2;
	GLfloat headband_width = 0.5;

	GLfloat headband_ang = 230.0 * (pi / 180.0);

	// housing
	GLfloat housing_rad = 0.5;

	// earpads
	GLfloat earpads_rad = 0.3;
	GLfloat earpads_width = 0.25;
	GLfloat earpads_thickness = 0.1;
	/*
	 *	headband
	*/
	// left part
	Object* left_part = new Object();
	children.push_back(left_part);


	left_rot = new glm::mat4();
	left_part->transforms.push_back(left_rot);
	*left_rot = glm::mat4(1.0f);

	glm::mat4* left_translate = new glm::mat4();
	left_part->transforms.push_back(left_translate);
	*left_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -headband_rad, 0.0));

	// left headband
	Primitive* left_headband = new SectorTorus(headband_rad, headband_rad + headband_thickness, headband_width, pi/2 - headband_ang/2, headband_ang/2);
	left_part->children.push_back(left_headband);

	// left ear
	Object* left_ear = new Object();
	left_part->children.push_back(left_ear);

	glm::mat4* left_ear_constraint = new glm::mat4();
	left_ear->transforms.push_back(left_ear_constraint);
	*left_ear_constraint = glm::translate(glm::mat4(1.0f), glm::vec3(headband_rad * cos(pi/2 - headband_ang/2), headband_rad * sin(pi/2 - headband_ang/2), 0.0));

	left_housing_rot = new glm::mat4();
	left_ear->transforms.push_back(left_housing_rot);
	*left_housing_rot = glm::rotate(glm::mat4(1.0f), -pi/2 - pi/16, rotateZ);

	Primitive* left_housing = new Sphere(0.0, pi, 0.0, pi);
	left_ear->children.push_back(left_housing);

	Primitive* left_earpad = new SectorTorus(earpads_rad, earpads_rad + earpads_width, earpads_thickness, 0.0, 2 * pi);
	left_ear->children.push_back(left_earpad);

	glm::mat4* left_earpad_model = new glm::mat4();
	left_earpad->transforms.push_back(left_earpad_model);
	*left_earpad_model = glm::rotate(glm::mat4(1.0f), pi/2, rotateX);
	*left_earpad_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -earpads_thickness/2, 0.0)) * *left_earpad_model;

	// right part
	Object* right_part = new Object();
	children.push_back(right_part);

	right_rot = new glm::mat4();
	right_part->transforms.push_back(right_rot);
	*right_rot = glm::mat4(1.0f);

	glm::mat4* right_translate = new glm::mat4();
	right_part->transforms.push_back(right_translate);
	*right_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -headband_rad, 0.0));

	// right headband
	Primitive* right_headband = new SectorTorus(headband_rad, headband_rad + headband_thickness, headband_width, pi/2, headband_ang/2);
	right_part->children.push_back(right_headband);

	// right ear
	Object* right_ear = new Object();
	right_part->children.push_back(right_ear);

	glm::mat4* right_ear_constraint = new glm::mat4();
	right_ear->transforms.push_back(right_ear_constraint);
	*right_ear_constraint = glm::translate(glm::mat4(1.0f), glm::vec3(headband_rad * cos(pi/2 + headband_ang/2), headband_rad * sin(pi/2 + headband_ang/2), 0.0));

	right_housing_rot = new glm::mat4();
	right_ear->transforms.push_back(right_housing_rot);
	*right_housing_rot = glm::rotate(glm::mat4(1.0f), pi/2 + pi/16, rotateZ);

	Primitive* right_housing = new Sphere(0.0, pi, 0.0, pi);
	right_ear->children.push_back(right_housing);

	Primitive* right_earpad = new SectorTorus(earpads_rad, earpads_rad + earpads_width, earpads_thickness, 0.0, 2 * pi);
	right_ear->children.push_back(right_earpad);

	glm::mat4* right_earpad_model = new glm::mat4();
	right_earpad->transforms.push_back(right_earpad_model);
	*right_earpad_model = glm::rotate(glm::mat4(1.0f), -pi/2, rotateX);
	*right_earpad_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, earpads_thickness/2, 0.0)) * *right_earpad_model;

	Object::init();
}

void Character2::manoeuvre(Character2::control_type ctrl, glm::vec3 param){

	switch(ctrl){

		case HEADBAND_ANGLE: {
			*left_rot = glm::rotate(*left_rot, param[0]/2, rotateX);
			*left_rot = glm::rotate(*left_rot, param[1]/2, rotateY);
			*left_rot = glm::rotate(*left_rot, param[2]/2, rotateZ);

			*right_rot = glm::rotate(*right_rot, -param[0]/2, rotateX);
			*right_rot = glm::rotate(*right_rot, -param[1]/2, rotateY);
			*right_rot = glm::rotate(*right_rot, -param[2]/2, rotateZ);
			break;
		}

		case LEFT_HOUSING_ANGLE: {
			*left_housing_rot = glm::rotate(*left_housing_rot, param[0], rotateX);
			*left_housing_rot = glm::rotate(*left_housing_rot, param[1], rotateY);
			*left_housing_rot = glm::rotate(*left_housing_rot, param[2], rotateZ);
			break;
		}

		case RIGHT_HOUSING_ANGLE: {
			*right_housing_rot = glm::rotate(*right_housing_rot, param[0], rotateX);
			*right_housing_rot = glm::rotate(*right_housing_rot, param[1], rotateY);
			*right_housing_rot = glm::rotate(*right_housing_rot, param[2], rotateZ);
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
#include "character2.hpp"

extern GLfloat pi;

extern glm::vec3 rotateX;
extern glm::vec3 rotateY;
extern glm::vec3 rotateZ;

Character2::Character2(){
	// headband
	headband_rad = 1.0;
	headband_thickness = 0.2;
	headband_width = 0.5;

	headband_ang = 230.0 * (pi / 180.0);

	// housing
	housing_rad = 0.5;

	// earpads
	earpads_rad = 0.3;
	earpads_width = 0.25;
	earpads_thickness = 0.1;


	left_housing_angle = glm::vec3(0.0, 0.0, -pi/2 - pi/16);
	right_housing_angle = glm::vec3(0.0, 0.0, pi/2 + pi/16);
}

void Character2::init(){

	// character translations

	glm::mat4* fullbodytrans = new glm::mat4(1.0f);
	transforms.push_back(fullbodytrans);
	body_translate_matrix = fullbodytrans;

	glm::mat4* fullbodyrot = new glm::mat4(1.0f);
	transforms.push_back(fullbodyrot);
	body_angle_matrix = fullbodyrot;

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
	*left_housing_rot = glm::rotate(glm::mat4(1.0f), left_housing_angle[2], rotateZ);

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
	*right_housing_rot = glm::rotate(glm::mat4(1.0f), right_housing_angle[2], rotateZ);

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
			left_angle += param/(float)2.0;
			*left_rot = glm::rotate(glm::mat4(1.0f), left_angle[0], rotateX);
			*left_rot = glm::rotate(*left_rot, left_angle[1], rotateY);
			*left_rot = glm::rotate(*left_rot, left_angle[2], rotateZ);

			right_angle -= param/(float)2.0;
			*right_rot = glm::rotate(glm::mat4(1.0f), right_angle[0], rotateX);
			*right_rot = glm::rotate(*right_rot, right_angle[1], rotateY);
			*right_rot = glm::rotate(*right_rot, right_angle[2], rotateZ);
			break;
		}

		case LEFT_HOUSING_ANGLE: {
			left_housing_angle += param;
			*left_housing_rot = glm::rotate(glm::mat4(1.0f), left_housing_angle[0], rotateX);
			*left_housing_rot = glm::rotate(*left_housing_rot, left_housing_angle[1], rotateY);
			*left_housing_rot = glm::rotate(*left_housing_rot, left_housing_angle[2], rotateZ);
			break;
		}

		case RIGHT_HOUSING_ANGLE: {
			right_housing_angle += param;
			*right_housing_rot = glm::rotate(glm::mat4(1.0f), right_housing_angle[0], rotateX);
			*right_housing_rot = glm::rotate(*right_housing_rot, right_housing_angle[1], rotateY);
			*right_housing_rot = glm::rotate(*right_housing_rot, right_housing_angle[2], rotateZ);
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
}

std::string Character2::getState() {
	std::stringstream sstream; 
	sstream << body_angle[0] << "," << body_angle[1] << "," << body_angle[2] << ",";
	sstream << body_translate[0] << "," << body_translate[1] << "," << body_translate[2] << ",";
	sstream << left_angle[0] << "," << left_angle[1] << "," << left_angle[2] << ",";
	sstream << left_housing_angle[0] << "," << left_housing_angle[1] << "," << left_housing_angle[2] << ",";
	sstream << right_angle[0] << "," << right_angle[1] << "," << right_angle[2] << ",";
	sstream << right_housing_angle[0] << "," << right_housing_angle[1] << "," << right_housing_angle[2];

	return sstream.str();
}

void Character2::setState(std::string state) {
	std::stringstream sstream(state);
	std::string token;

	std::getline(sstream, token, ',');
	body_angle[0] = stof(token);
	std::getline(sstream, token, ','); 
	body_angle[1] = stof(token);
	std::getline(sstream, token, ','); 
	body_angle[2] = stof(token);
	std::getline(sstream, token, ','); 
	body_translate[0] = stof(token);
	std::getline(sstream, token, ','); 
	body_translate[1] = stof(token);
	std::getline(sstream, token, ','); 
	body_translate[2] = stof(token);
	std::getline(sstream, token, ','); 
	left_angle[0] = stof(token);
	std::getline(sstream, token, ','); 
	left_angle[1] = stof(token);
	std::getline(sstream, token, ','); 
	left_angle[2] = stof(token);
	std::getline(sstream, token, ','); 
	left_housing_angle[0] = stof(token);
	std::getline(sstream, token, ','); 
	left_housing_angle[1] = stof(token);
	std::getline(sstream, token, ','); 
	left_housing_angle[2] = stof(token);
	std::getline(sstream, token, ','); 
	right_angle[0] = stof(token);
	std::getline(sstream, token, ','); 
	right_angle[1] = stof(token);
	std::getline(sstream, token, ','); 
	right_angle[2] = stof(token);
	std::getline(sstream, token, ','); 
	right_housing_angle[0] = stof(token);
	std::getline(sstream, token, ','); 
	right_housing_angle[1] = stof(token);
	std::getline(sstream, token, ',');
	right_housing_angle[2] = stof(token);

	manoeuvre(HEADBAND_ANGLE, glm::vec3(0.0f));
	manoeuvre(LEFT_HOUSING_ANGLE, glm::vec3(0.0f));
	manoeuvre(RIGHT_HOUSING_ANGLE, glm::vec3(0.0f));
	manoeuvre(BODY_ANGLE, glm::vec3(0.0f));
	manoeuvre(BODY_TRANSLATE, glm::vec3(0.0f));
}
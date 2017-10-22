#include "character1.hpp"

Character1::Character1(){

}

void Character1::init(){

	BaseObject* parent;
	parent = new Object();

	glm::mat4* rotation_matrix;
	rotation_matrix = new glm::mat4();
	*rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));

	parent->transforms.push_back(rotation_matrix);

	full_body_rot = rotation_matrix;

	BaseObject* ch1;
	ch1 = new Cube();

	rotation_matrix = new glm::mat4();
	*rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));

	ch1->transforms.push_back(rotation_matrix);


	BaseObject* ch2;
	ch2 = new Cylinder();

	rotation_matrix = new glm::mat4();
	*rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));

	ch2->transforms.push_back(rotation_matrix);

	elbow_rot = rotation_matrix;
	children.push_back(parent);

	((Object *)parent)->children.push_back(ch1);
	((Object *)parent)->children.push_back(ch2);

	Object::init();
}

void Character1::manoeuvre(glm::vec3 drot){

	rot+=drot;

	// std::cout << xrot << " " << yrot << " " << zrot << " " << std::endl;
	glm::mat4* rotation_matrix=elbow_rot;

	*rotation_matrix = glm::rotate(glm::mat4(1.0f), rot[0], glm::vec3(1.0f,0.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[1], glm::vec3(0.0f,1.0f,0.0f));
	*rotation_matrix = glm::rotate(*rotation_matrix, rot[2], glm::vec3(0.0f,0.0f,1.0f));


	// rotation_matrix=children[0]->transforms[0];
	// std::cout << (*rotation_matrix)[0][0] << std::endl;
}
#include "environ.hpp"

extern double PI;

Environment::Environment(){
	room_width = 1.0;
	room_length = 1.0;
	room_height = 1.0;
}

void Environment::init(){

	Primitive* room = new Cube();
	children.push_back(room);

	glm::mat4* bound_dim = new glm::mat4();
	room->transforms.push_back(bound_dim);
	*bound_dim = glm::scale(glm::mat4(1.0f), glm::vec3(room_length, room_width, room_height));

	Object::init();
}
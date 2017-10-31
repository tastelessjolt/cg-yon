#include "environ.hpp"

extern double PI;

Environment::Environment(){
	room_width = 4.0;
	room_length = 4.0;
	room_height = 4.0;
	wall_thickness = 0.01;
}

void Environment::init(){

	Primitive* room0 = new Cube();
	children.push_back(room0);
	room0->settexture("textures/wall.bmp", 626, 417);

	glm::mat4* bound_dim0 = new glm::mat4();
	room0->transforms.push_back(bound_dim0);
	*bound_dim0 = 	glm::translate(glm::mat4(1.0f), glm::vec3(room_length/2, 0.0, 0.0))
					* glm::scale(glm::mat4(1.0f), glm::vec3(wall_thickness, room_width, room_height));


	Primitive* room1 = new Cube();
	children.push_back(room1);
	room1->settexture("textures/wall.bmp", 626, 417);

	glm::mat4* bound_dim1 = new glm::mat4();
	room1->transforms.push_back(bound_dim1);
	*bound_dim1 = 	glm::translate(glm::mat4(1.0f), glm::vec3(-room_length/2, 0.0, 0.0))
					* glm::scale(glm::mat4(1.0f), glm::vec3(wall_thickness, room_width, room_height));


	Primitive* room2 = new Cube();
	children.push_back(room2);
	room2->settexture("textures/ceiling.bmp", 300, 300);

	glm::mat4* bound_dim2 = new glm::mat4();
	room2->transforms.push_back(bound_dim2);
	*bound_dim2 = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.0, room_width/2, 0.0))
					* glm::scale(glm::mat4(1.0f), glm::vec3(room_length, wall_thickness, room_height));


	Primitive* room3 = new Cube();
	children.push_back(room3);
	room3->settexture("textures/flooring.bmp", 960, 870);

	glm::mat4* bound_dim3 = new glm::mat4();
	room3->transforms.push_back(bound_dim3);
	*bound_dim3 = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.0, -room_width/2, 0.0))
					* glm::scale(glm::mat4(1.0f), glm::vec3(room_length, wall_thickness, room_height));


	Primitive* room4 = new Cube();
	children.push_back(room4);
	room4->settexture("textures/wall.bmp", 626, 417);

	glm::mat4* bound_dim4 = new glm::mat4();
	room4->transforms.push_back(bound_dim4);
	*bound_dim4 = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, room_height/2))
					* glm::scale(glm::mat4(1.0f), glm::vec3(room_length, room_width, wall_thickness));


	Primitive* room5 = new Cube();
	children.push_back(room5);
	room5->settexture("textures/wall.bmp", 626, 417);

	glm::mat4* bound_dim5 = new glm::mat4();
	room5->transforms.push_back(bound_dim5);
	*bound_dim5 = 	glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -room_height/2))
					* glm::scale(glm::mat4(1.0f), glm::vec3(room_length, room_width, wall_thickness));


	Object::init();
}
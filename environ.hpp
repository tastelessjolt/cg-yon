#ifndef ENVIRON_HPP
#define ENVIRON_HPP

#include "object.hpp"

class Environment : public Object {

	GLfloat room_length;
	GLfloat room_width;
	GLfloat room_height;

public:
	Environment();
	void init();
};

#endif /* ENVIRON_HPP */
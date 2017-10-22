#include "object.hpp"
#include <unordered_map>

class Character1 : public Object {

	glm::vec3 rot;
	glm::mat4* elbow_rot;
	glm::mat4* full_body_rot;

public:
	Character1();
	void init();
	void manoeuvre(glm::vec3);
};
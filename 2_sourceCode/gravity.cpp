#include "gravity.h"

void Falling(GameObject &bounceObject) {
	bounceObject.position.y += bounceObject.velocity.y;
	bounceObject.velocity.y += bounceObject.acceleration.y;
}

void Gravity(GameObject& bounceObject, float& bounceTime, float repulsion, float objectHight, float FallPosition){

	Falling(bounceObject);
	if (bounceObject.position.y + objectHight >= FallPosition) {
		if (bounceTime > 0) {
			bounceTime--;
			bounceObject.velocity.y = -bounceObject.velocity.y * repulsion;
		}
		bounceObject.position.y = FallPosition - objectHight;
	}
}

#include "hit.h"
bool Hit(GameObject player, GameObject object) {

	bool shotXleEnemyXW = player.position.x <= object.position.x + object.size.width;
	bool enemyXleShotXW = object.position.x <= player.position.x + player.size.width;
	bool shotYleEnemyYH = player.position.y <= object.position.y + object.size.hight;
	bool enemyYleShotYH = object.position.y <= player.position.y + player.size.hight;

	return shotXleEnemyXW && enemyXleShotXW && shotYleEnemyYH&& enemyYleShotYH;

}


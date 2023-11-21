#include "mapTip.h"

void MovePlayer(char keys[], Vector2 &leftTop, Vector2 &leftBottom, Vector2 &rightTop, Vector2 &rightBottom, GameObject& player, float radius, Vector2 tempSpeed, int mapTile[][50]){
	
	leftTop.x = (player.position.x  - radius) / BLOCK_SIZE;
	leftTop.y = (player.position.y - radius) / BLOCK_SIZE;

	leftBottom.x = (player.position.x  - radius) / BLOCK_SIZE;
	leftBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;

	rightTop.x = (player.position.x  + radius - 1) / BLOCK_SIZE;
	rightTop.y = (player.position.y - radius) / BLOCK_SIZE;

	rightBottom.x = (player.position.x + radius - 1) / BLOCK_SIZE;
	rightBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;

	if (keys[DIK_A]) {
		
		leftTop.x = (player.position.x - tempSpeed.x- radius) / BLOCK_SIZE;
		leftTop.y = (player.position.y - radius) / BLOCK_SIZE;

		leftBottom.x = (player.position.x - tempSpeed.x - radius) / BLOCK_SIZE;
		leftBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;
		if (mapTile[(int)leftTop.y][(int)leftTop.x] == 0 && mapTile[(int)leftBottom.y][(int)leftBottom.x] == 0) {
			player.velocity.x = -4;
		}
		else {
			player.velocity.x = 0;
		}
	}
	else if (keys[DIK_D]) {
		
		rightTop.x = (player.position.x + tempSpeed.x + radius - 1) / BLOCK_SIZE;
		rightTop.y = (player.position.y - radius) / BLOCK_SIZE;

		rightBottom.x = (player.position.x + tempSpeed.x + radius - 1) / BLOCK_SIZE;
		rightBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;

		if (mapTile[(int)rightTop.y][(int)rightTop.x] == 0 && mapTile[(int)rightBottom.y][(int)rightBottom.x] == 0) {
			player.velocity.x = 4;
		}
		else {
			player.velocity.x = 0;
		}
	}
	else {
		player.velocity.x = 0;
	}
	if (keys[DIK_W]) {
		leftTop.x = (player.position.x - radius) / BLOCK_SIZE;
		leftTop.y = (player.position.y - tempSpeed.y - radius) / BLOCK_SIZE;

		rightTop.x = (player.position.x + radius - 1) / BLOCK_SIZE;
		rightTop.y = (player.position.y - tempSpeed.y - radius) / BLOCK_SIZE;

		if (mapTile[(int)leftTop.y][(int)leftTop.x] == 0 && mapTile[(int)rightTop.y][(int)rightTop.x] == 0) {
			player.velocity.y = -4;
		}
		else {
			player.velocity.y = 0;
		}
	}
	else if (keys[DIK_S]) {
		leftBottom.x = (player.position.x  - radius) / BLOCK_SIZE;
		leftBottom.y = (player.position.y + tempSpeed.y + radius - 1) / BLOCK_SIZE;

		rightBottom.x = (player.position.x + radius - 1) / BLOCK_SIZE;
		rightBottom.y = (player.position.y + tempSpeed.y + radius - 1) / BLOCK_SIZE;

		if (mapTile[(int)leftBottom.y][(int)leftBottom.x] == 0 && mapTile[(int)rightBottom.y][(int)rightBottom.x] == 0) {
			player.velocity.y = 4;
		}
		else {
			player.velocity.y = 0;
		}
	}
	else {
		player.velocity.y = 0;
	}
}

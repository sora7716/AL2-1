#include "mapTip.h"

void MovePlayer(char keys[], char preKeys[], bool& isJump, Vector2& leftTop, Vector2& leftBottom, Vector2& rightTop, Vector2& rightBottom, GameObject& player, float radius, Vector2 tempSpeed, int mapTile[][50], float& bgSpeed) {


	

	
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
				player.velocity.x = -tempSpeed.x;
				bgSpeed = tempSpeed.x;
		}
		else {
			player.velocity.x = 0;
			bgSpeed = 0;
		}
	}
	else if (keys[DIK_D]) {

		rightTop.x = (player.position.x + tempSpeed.x + radius - 1) / BLOCK_SIZE;
		rightTop.y = (player.position.y - radius) / BLOCK_SIZE;

		rightBottom.x = (player.position.x + tempSpeed.x + radius - 1) / BLOCK_SIZE;
		rightBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;

		if (mapTile[(int)rightTop.y][(int)rightTop.x] == 0 && mapTile[(int)rightBottom.y][(int)rightBottom.x] == 0) {
				player.velocity.x = tempSpeed.x;
				bgSpeed = -tempSpeed.x;
		}
		else {
			player.velocity.x = 0;
			bgSpeed = 0;
		}
	}
	else {
		player.velocity.x = 0;
		bgSpeed = 0;
	}

	if (keys[DIK_SPACE]&&!preKeys[DIK_SPACE]&&isJump) {
		leftTop.x = (player.position.x - radius) / BLOCK_SIZE;
		leftTop.y = (player.position.y - player.velocity.y - radius) / BLOCK_SIZE;

		rightTop.x = (player.position.x + radius - 1) / BLOCK_SIZE;
		rightTop.y = (player.position.y - player.velocity.y - radius) / BLOCK_SIZE;

		if (mapTile[(int)leftTop.y][(int)leftTop.x] == 0 && mapTile[(int)rightTop.y][(int)rightTop.x] == 0) {
			player.velocity.y = -14;
			isJump = false;
		}

	}
	

}

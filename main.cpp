#include <Novice.h>

#include "myStruct.h"
const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	float radius = 16;

	int mapTile[27][50] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	GameObject player = {
		{48+32,48+32},
		{0,0},
		{0,0},
		WHITE,
		true,
	};
	Vector2 leftTop = { 0 };
	Vector2 leftBottom = { 0 };
	Vector2 rightTop = { 0 };
	Vector2 rightBottom = { 0 };
	Vector2 tempSpeed = { 4,4 };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		leftTop.x = (player.position.x  - radius) / BLOCK_SIZE;
		leftTop.y = (player.position.y  - radius) / BLOCK_SIZE;

		leftBottom.x = (player.position.x  - radius) / BLOCK_SIZE;
		leftBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;

		rightTop.x = (player.position.x + radius - 1) / BLOCK_SIZE;
		rightTop.y = (player.position.y - radius )/ BLOCK_SIZE;

		rightBottom.x = (player.position.x + radius - 1) / BLOCK_SIZE;
		rightBottom.y = (player.position.y + radius - 1 ) / BLOCK_SIZE;

		if (keys[DIK_A]) {
			leftTop.x = (player.position.x - tempSpeed.x - radius) / BLOCK_SIZE;
			leftTop.y = (player.position.y - radius) / BLOCK_SIZE;

			leftBottom.x = (player.position.x - tempSpeed.x - radius) / BLOCK_SIZE;
			leftBottom.y = (player.position.y + radius - 1) / BLOCK_SIZE;
			if (mapTile[(int)leftTop.y][(int)leftTop.x] == 0 &&  mapTile[(int)leftBottom.y][(int)leftBottom.x] == 0) {
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
			leftBottom.x = (player.position.x - radius) / BLOCK_SIZE;
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
		player.position.x += player.velocity.x;
		player.position.y += player.velocity.y;

		Novice::ScreenPrintf(0, 0,"map[%d][%d] = %d", (int)leftTop.y, (int)leftTop.x,mapTile[(int)leftTop.y][(int)leftTop.x]);
		Novice::ScreenPrintf(0, 20,"map[%d][%d] = %d", (int)leftBottom.y, (int)leftBottom.x, mapTile[(int)leftBottom.y][(int)leftBottom.x]);

		Novice::ScreenPrintf(150, 0, "map[%d][%d] = %d", (int)rightTop.y, (int)rightTop.x, mapTile[(int)rightTop.y][(int)rightTop.x]);
		Novice::ScreenPrintf(150, 20, "map[%d][%d] = %d", (int)rightBottom.y, (int)rightBottom.x, mapTile[(int)rightBottom.y][(int)rightBottom.x]);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int x = 0; x < 50; x++) {
			for (int y = 0; y < 27; y++) {
				if (mapTile[y][x] == 1) {
					Novice::DrawBox((int)x * (int)BLOCK_SIZE, (int)y * (int)BLOCK_SIZE, (int)BLOCK_SIZE, (int)BLOCK_SIZE, 0.0f, BLACK, kFillModeSolid);
				}
			}
		}

		Novice::DrawEllipse((int)player.position.x, (int)player.position.y, (int)radius, (int)radius, 0.0f, RED, kFillModeSolid);
		Novice::DrawBox((int)player.position.x - (int)radius, (int)player.position.y - (int)radius,(int)BLOCK_SIZE, (int)BLOCK_SIZE, 0.0f, WHITE, kFillModeWireFrame);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

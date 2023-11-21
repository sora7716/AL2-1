#include <Novice.h>

#include "myStruct.h"
#include "mapTip.h"
#include "fullScreen.h"
#include "hit.h"
#include "gravity.h"
const char kWindowTitle[] = "GC1A_01_イイヅカ_ソラ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	float radius = 16;

	int playerGH = Novice::LoadTexture("./resource/player.png");
	int blockGH = Novice::LoadTexture("./resource/block.png");
	int enemyGH[2] = {
		Novice::LoadTexture("./resource/enemy1.png"),
		Novice::LoadTexture("./resource/enemy2.png"),
	};
	int clearGH = Novice::LoadTexture("./resource/parfectGame.png");
	int badEndGH = Novice::LoadTexture("./resource/badEnd.png");

	int BGM = Novice::LoadAudio("./resource/start.mp3");
	int enemyType = 0;
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
		{48,48},
		{0,0},
		{0,0.8f},
		{32,32},
		WHITE,
		true,
	};
	GameObject enemy = {
		{32,32 * 23},
	    {5,0,},
		{0,0},
		{32,32},
		WHITE,
		true
	};
	Vector2 leftTop = { 0 };
	Vector2 leftBottom = { 0 };
	Vector2 rightTop = { 0 };
	Vector2 rightBottom = { 0 };
	Vector2 tempSpeed = { 4,4 };
	Vector2 blockPos = { 0 };
	float bgSpeed = 0;

	float sceneChage = 0;
	Scene scene = game;

	GameObject endMojiPos{
		{0,0},
		{0,0},
		{0,0.8f},
		{0,0},
		WHITE,
		true,
	};
	float repulsion = 0.8f;
	float bounceTime = 5;

	int soundHandle = 0;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		if (Novice::IsPlayingAudio(soundHandle)==0) {
			soundHandle = Novice::PlayAudio(BGM, true, 0.5f);
		}
		///
		/// ↓更新処理ここから
		///
		
#pragma region FULLScreen
		FullScreen(keys, preKeys);
#pragma endregion


#pragma region Game 
		if (scene == game) {
			MovePlayer(keys, leftTop, leftBottom, rightTop, rightBottom, player, radius, tempSpeed, mapTile);

			player.position.x += player.velocity.x;
			player.position.y += player.velocity.y;

			enemy.position.x += enemy.velocity.x;
			if (enemyType == 1) {
				enemy.velocity.x = 0;
			}
				if (enemy.position.x < 32) {
					enemy.velocity.x = 5;
				}
				if (enemy.position.x > 800 - 32) {
					enemy.velocity.x = -5;
				}
			
			if (Hit(player, enemy)&&enemyType==0) {
				if (player.position.y <= enemy.position.y) {
					enemyType = 1;
					sceneChage = 30;
				}
				else {
					scene = badEnd;
				}
			}
			else {
				enemy.color = BLUE;
			}

			if (sceneChage > 0) {
				sceneChage--;
			}if (enemyType == 1 && sceneChage <= 0) {
				scene = clear;
			}
#pragma region ScreenPrintf
			Novice::ScreenPrintf(0, 0, "map[%d][%d] = %d", (int)leftTop.y, (int)leftTop.x, mapTile[(int)leftTop.y][(int)leftTop.x]);
			Novice::ScreenPrintf(0, 20, "map[%d][%d] = %d", (int)leftBottom.y, (int)leftBottom.x, mapTile[(int)leftBottom.y][(int)leftBottom.x]);

			Novice::ScreenPrintf(150, 0, "map[%d][%d] = %d", (int)rightTop.y, (int)rightTop.x, mapTile[(int)rightTop.y][(int)rightTop.x]);
			Novice::ScreenPrintf(150, 20, "map[%d][%d] = %d", (int)rightBottom.y, (int)rightBottom.x, mapTile[(int)rightBottom.y][(int)rightBottom.x]);
#pragma endregion

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///

			for (int x = 0; x < 50; x++) {
				for (int y = 0; y < 27; y++) {
					if (mapTile[y][x] == 1) {
						blockPos.x = (float)x * BLOCK_SIZE;
						blockPos.y = (float)y * BLOCK_SIZE;
						Novice::DrawSprite((int)blockPos.x + (int)bgSpeed, (int)blockPos.y, blockGH, 1, 1, 0.0f, WHITE);
						//Novice::DrawBox((int)blockPos.x, (int)blockPos.y, 32, 32, 0.0f, WHITE, kFillModeWireFrame);
					}
				}
			}
			Novice::DrawSprite((int)enemy.position.x, (int)enemy.position.y, enemyGH[enemyType], 1, 1, 0.0f, enemy.color);
			Novice::DrawSprite((int)player.position.x - (int)radius, (int)player.position.y - (int)radius, playerGH, 1, 1, 0.0f, WHITE);
			///
			/// ↑描画処理ここまで
			///
		}
#pragma endregion


#pragma region BadEnd
		if (scene == badEnd) {
			//
			//更新処理:ここから
			//
			Gravity(endMojiPos, bounceTime, repulsion, 96, 400);
			//
			//更新処理:ここまで
			//

			//
			//描画処理:ここから
			//
			Novice::DrawSprite((int)endMojiPos.position.x, (int)endMojiPos.position.y, badEndGH, 1, 1, 0.0f, WHITE);
			//
			//描画処理:ここまで
			//
		}
#pragma endregion


#pragma region Clear
		if (scene == clear) {
			//
			//更新処理:ここから
			//
			Gravity(endMojiPos, bounceTime, repulsion, 96, 400);
			//
			//更新処理:ここまで
			//

			//
			//描画処理:ここから
			//
			Novice::DrawSprite((int)endMojiPos.position.x, (int)endMojiPos.position.y, clearGH, 1, 1, 0.0f, WHITE);
			//
			//描画処理:ここまで
			//
		}
#pragma endregion


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

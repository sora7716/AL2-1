#include <Novice.h>
#include <math.h>
#include "myStruct.h"
#include "mapTip.h"
#include "fullScreen.h"
#include "hit.h"
#include "gravity.h"
const char kWindowTitle[] = "Block";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)SCREEN_WIDTH, (int)SCREEN_HIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	//プレイヤーの半径
	float radius = 16;
	//リソースのロード
	int playerGH = Novice::LoadTexture("./resource/player.png");
	int blockGH = Novice::LoadTexture("./resource/block.png");
	int enemyGH[2] = {
		Novice::LoadTexture("./resource/enemy1.png"),
		Novice::LoadTexture("./resource/enemy2.png"),
	};
	int clearGH = Novice::LoadTexture("./resource/perfectGame.png");
	int badEndGH = Novice::LoadTexture("./resource/badEnd.png");

	int BGM = Novice::LoadAudio("./resource/start.mp3");
	
	//エネミーの状態変更用
	int enemyType = 0;
	//マップチップ
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

	//プレイヤー
	GameObject player = {
		{48,48},
		{0,0},
		{0,0.8f},
		{32,32},
		WHITE,
		true,
	};
	//エネミー
	GameObject enemy = {
		{32+16,32 * 23+16},
	    {2,0,},
		{0,0.8f},
		{32,32},
		WHITE,
		true
	};
	

	//プレイヤーの頂点
	Vector2 leftTop = { 0 };
	Vector2 leftBottom = { 0 };
	Vector2 rightTop = { 0 };
	Vector2 rightBottom = { 0 };
	//プレイヤーのスピード
	Vector2 tempSpeed = { 4,4 };
	//マップチップ
	Vector2 blockPos = { 0 };
	float bgSpeed = 0;
	//シーン変える用
	float sceneChargeTime = 0;
	Scene scene = game;

	//エンド画面の文字用
	GameObject endMojiPos{
		{0,0},
		{0,0},
		{0,0.8f},
		{0,0},
		WHITE,
		true,
	};
	float repulsion = 0.8f;//反発係数
	float bounceTime = 5;
	//BGM用
	int soundHandle = 0;

	//ジャンプ
	bool isJump = true;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		//BGM流している
		if (Novice::IsPlayingAudio(soundHandle)==0) {
			soundHandle = Novice::PlayAudio(BGM, true, 0.5f);
		}
		///
		/// ↓更新処理ここから
		///
		
#pragma region FULLScreen
		FullScreen(keys, preKeys);
#pragma endregion

			player.position.y += player.velocity.y;
			player.velocity.y += player.acceleration.y;
		if (!isJump) {

		}

#pragma region Game 
		if (scene == game) {
			//マップチップの当たり判定とプレイヤーの動き
			MovePlayer(keys,preKeys,isJump,leftTop, leftBottom, rightTop, rightBottom, player, radius, tempSpeed, mapTile,bgSpeed);
			
			blockPos.x += bgSpeed;
			player.position.x += player.velocity.x;
			if (player.position.x <= 400) {
				blockPos.x = 0;
			}
			if (player.position.x >= 1200) {
				blockPos.x = -800;
			}
			
			leftBottom.x = (player.position.x - radius) / BLOCK_SIZE;
			leftBottom.y = (player.position.y + player.velocity.y + radius - 1) / BLOCK_SIZE;

			rightBottom.x = (player.position.x + radius - 1) / BLOCK_SIZE;
			rightBottom.y = (player.position.y  + player.velocity.y + radius - 1) / BLOCK_SIZE;
			
			if (mapTile[(int)leftBottom.y][(int)leftBottom.x] == 1 || mapTile[(int)rightBottom.y][(int)rightBottom.x] == 1) {
				player.velocity.y = 0; 
				player.position.y = floorf(leftBottom.y)* BLOCK_SIZE-radius;
				isJump = true;
			}
				 

		 
			leftTop.x = (player.position.x - radius) / BLOCK_SIZE;
			leftTop.y = (player.position.y + player.velocity.y - radius) / BLOCK_SIZE;

			rightTop.x = (player.position.x + radius - 1) / BLOCK_SIZE;
			rightTop.y = (player.position.y + player.velocity.y - radius) / BLOCK_SIZE;

			if (!isJump) {
				if (mapTile[(int)leftTop.y][(int)leftTop.x] == 1 || mapTile[(int)rightTop.y][(int)rightTop.x] == 1) {
					player.velocity.y = 0;
					player.position.y = (leftTop.y + 1) * BLOCK_SIZE - radius / 2;
				}
			}


			//エネミーの動き
			enemy.position.x += enemy.velocity.x;
			if (enemyType == 1) {
				enemy.velocity.x = 0;
			}
			if (enemy.position.x >= 1600-32) {
				enemy.velocity.x = -2;
			}
			else if (enemy.position.x <= 0+32) {
				enemy.velocity.x = 2;
			}
			

			//エネミーとプレイヤーの当たり判定
			if (Hit(player, enemy)&&enemyType==0) {
				if (player.position.y< enemy.position.y) {
					enemyType = 1;
					sceneChargeTime = 30;
					player.velocity.y = -8;
				}
				else {
					scene = badEnd;
				}
			}
			//エネミーを倒した時のシーン切り替わるまでの時間
			if (sceneChargeTime > 0) {
				sceneChargeTime--;
			}if (enemyType == 1 && sceneChargeTime <= 0) {
				scene = clear;
			}
#pragma region ScreenPrintf
			/*Novice::ScreenPrintf(0, 0, "map[%d][%d] = %d", (int)leftTop.y, (int)leftTop.x, mapTile[(int)leftTop.y][(int)leftTop.x]);
			Novice::ScreenPrintf(0, 20, "map[%d][%d] = %d", (int)leftBottom.y, (int)leftBottom.x, mapTile[(int)leftBottom.y][(int)leftBottom.x]);

			Novice::ScreenPrintf(150, 0, "map[%d][%d] = %d", (int)rightTop.y, (int)rightTop.x, mapTile[(int)rightTop.y][(int)rightTop.x]);
			Novice::ScreenPrintf(150, 20, "map[%d][%d] = %d", (int)rightBottom.y, (int)rightBottom.x, mapTile[(int)rightBottom.y][(int)rightBottom.x]);*/
#pragma endregion

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			//マップチップ
			for (int x = 0; x < 50; x++) {
				for (int y = 0; y < 27; y++) {
					if (mapTile[y][x] == 1) {
				
						Novice::DrawSprite(x* (int)BLOCK_SIZE + (int)blockPos.x, y * (int)BLOCK_SIZE, blockGH, 1, 1, 0.0f, WHITE);
						//Novice::DrawBox((int)blockPos.x, (int)blockPos.y, 32, 32, 0.0f, WHITE, kFillModeWireFrame);
					}
					
				}
			}
			//エネミー
			Novice::DrawSprite((int)enemy.position.x + (int)blockPos.x, (int)enemy.position.y - (int)radius, enemyGH[enemyType], 1, 1, 0.0f, enemy.color);
			//プレイヤー
			Novice::DrawSprite((int)player.position.x - (int)radius+ (int)blockPos.x, (int)player.position.y - (int)radius, playerGH, 1, 1, 0.0f, WHITE);
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
			//文字のバウンド
			Gravity(endMojiPos, bounceTime, repulsion, 96, 400);
			//
			//更新処理:ここまで
			//

			//
			//描画処理:ここから
			//
			//文字
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
		    //文字のバウンド
			Gravity(endMojiPos, bounceTime, repulsion, 96, 400);
			//
			//更新処理:ここまで
			//

			//
			//描画処理:ここから
			//
			//文字
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

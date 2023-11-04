#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HIGHT = 800;

const float BLOCK_SIZE = 32;

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct GameObject {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	unsigned int color;
	bool isAlive;
}GameObject;
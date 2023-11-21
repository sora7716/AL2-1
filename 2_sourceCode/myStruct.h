#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HIGHT = 800;

const float BLOCK_SIZE = 32;

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Size {
	float width;
	float hight;
}Size;

typedef struct GameObject {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Size size;
	unsigned int color;
	bool isAlive;
}GameObject;

enum Scene {
	game,
	badEnd, 
	clear,
};
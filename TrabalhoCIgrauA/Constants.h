#pragma once

namespace Constants {

	//definig contants to the game elements' size
	const float PLAYER_HEIGHT = 0.3;
	const float PLAYER_WIDTH = 0.25;

	const float ENEMY_HEIGHT = 0.3;
	const float ENEMY_WIDTH = 0.25;
	
	const float POWERUP_HEIGHT = 0.3;
	const float POWERUP_WIDTH = POWERUP_HEIGHT;

	const float ENEMY_FOV_HEIGHT = 0.5;
	const float ENEMY_FOV_WIDTH = 0.4;

	const float HOSTAGE_HEIGHT = 0.1;
	const float HOSTAGE_WIDTH = 0.1;

	const float BULLET_HEIGHT = 0.01;
	const float BULLET_WIDTH = BULLET_HEIGHT;

	//define player and enemies health
	const float PLAYER_HEALTH = 3;
	const float ENEMY_HEALTH = 1;
	const float HOSTAGE_HEALTH = 1;

	//setting game element colors contants
	std::vector<float> WALL_COLOR = { 0.0f , 0.3f , 0.0f };
	std::vector<float> PLAYER_COLOR_FULL = { 0.1f , 1.0f , 1.0f };
	std::vector<float> PLAYER_COLOR_MEDIUM = { 0.1f, 0.7f, 0.7f };
	std::vector<float> PLAYER_COLOR_LOW = { 0.1f, 0.5f, 0.5f };
	std::vector<float> PLAYER_COLOR_DEAD = { 0.0f, 0.0f, 0.0f };
	std::vector<float> ENEMY_COLOR = { 0.8f , 0.0f , 0.0f };
	std::vector<float> ENEMY_FOV_COLOR = { 1.0f , 0.5f , 0.5f };
	std::vector<float> HOSTAGE_COLOR = { 1.0f , 0.0f , 1.0f };
	std::vector<float> BULLET_COLOR = { 0.0f , 0.0f , 0.0f };
	std::vector<float> POWERUP_COLOR = { 255.0f, 246.0f, 0.0f };

	enum Object_Type
	{
		WALL,
		PLAYER,
		ENEMY,
		ENEMY_FOV,
		HOSTAGE,
		BULLET,
		POWERUP
	};
	
}
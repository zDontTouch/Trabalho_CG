#pragma once

namespace Constants {

	//definig contants to the game elements' size
	const float PLAYER_HEIGHT = 0.2;
	const float PLAYER_WIDTH = 0.15;

	const float ENEMY_HEIGHT = 0.1;
	const float ENEMY_WIDTH = 0.05;
	
	const float POWERUP_HEIGHT = 0.1;
	const float POWERUP_WIDTH = POWERUP_HEIGHT;

	const float ENEMY_FOV_HEIGHT = 0.3;
	const float ENEMY_FOV_WIDTH = 0.25;

	const float HOSTAGE_HEIGHT = 0.1;
	const float HOSTAGE_WIDTH = 0.1;

	const float BULLET_HEIGHT = 0.01;
	const float BULLET_WIDTH = BULLET_HEIGHT;

	//setting game element colors contants
	std::vector<float> WALL_COLOR = { 0.0f , 0.3f , 0.0f };
	std::vector<float> PLAYER_COLOR = { 0.1f , 7.0f , 7.0f };
	std::vector<float> ENEMY_COLOR = { 0.8f , 0.0f , 0.0f };
	std::vector<float> ENEMY_FOV_COLOR = { 1.0f , 0.5f , 0.5f };
	std::vector<float> HOSTAGE_COLOR = { 1.0f , 0.0f , 1.0f };
	std::vector<float> BULLET_COLOR = { 0.0f , 0.0f , 0.0f };
	std::vector<float> POWERUP_COLOR = { 0.0f , 0.0f , 0.0f };

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
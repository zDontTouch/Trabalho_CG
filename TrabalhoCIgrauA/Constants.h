#pragma once

namespace Constants {

	//definig contants to the game elements' size
	const float PLAYER_HEIGHT = 0.4;
	const float PLAYER_WIDTH = 0.35;

	const float ENEMY_HEIGHT = 0.4;
	const float ENEMY_WIDTH = 0.35;
	
	const float POWERUP_HEIGHT = 0.3;
	const float POWERUP_WIDTH = POWERUP_HEIGHT;

	const float ENEMY_FOV_HEIGHT = 2.0;
	const float ENEMY_FOV_WIDTH = 3.0;

	const float HOSTAGE_HEIGHT = 0.1;
	const float HOSTAGE_WIDTH = 0.1;

	const float BULLET_HEIGHT = 0.05;
	const float BULLET_WIDTH = BULLET_HEIGHT;

	const float BLAST_BULLET_RADIUS = 1;

	//setting some game constants
	const float PLAYER_MOVEMENT_TIC = 0.1;
	const float ENEMY_MOVEMENT_TIC = 0.1;
	const float BULLET_MOVEMENT_TIC = 0.15;

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
	std::vector<float> BULLET_COLOR = { 1.0f , 1.0f , 0.5f };
	std::vector<float> POWERUP_COLOR = { 255.0f, 246.0f, 0.0f };

	std::vector<float> DRILL_BULLET_COLOR = { 0.6f, 0.6f, 0.6f };
	std::vector<float> EXPANSIVE_BULLET_COLOR = { 0.3f, 0.9f, 0.9f };
	std::vector<float> BLAST_BULLET_COLOR = { 0.2f, 0.8f, 0.2f };

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

	enum Powerup_type
	{
		NONE,
		DRILL,
		EXPANSIVE,
		BLAST
	};
	
}
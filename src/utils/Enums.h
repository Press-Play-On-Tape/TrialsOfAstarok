#pragma once

enum GameState {
	Title,
	Seed_Init,
	Seed,
	Game_Init,
	Game_Play,
	HighScore_Check,
	HighScore_Enter,
	HighScore_DisplayAll,
};

enum TitleScreenMode {
	Play,
	HighScore
};

enum MapLevel {
	BelowGround,
	AboveGround,
};

enum Hearts {
	FilledIn,
	Outline,
};

enum SpriteDataLayout {
	SpriteType,
	SpriteFlags,
	SpriteSpeed,
	SpriteIntelligence,
};

enum Direction { Up, Down, Left, Right };







enum ObjectTypes {
  STSquario = 0,  // Sprites
  STTriangleo,
  STStarmano,
  STSmileo,
  STBolt,
  STMushroom = 5,
  STQBlock,  // Interactive Tiles
  STBQBlock,
  STMushBlock,
  STBricks = 9,
  STAboveGroundExit,
  STUnderGroundExit,
  STSign,
  STFireball,
  STCoin,
};

enum EventType {
  Off = 0,
  Playing,
  Death_Init,
  Death,
  LevelExit,
  StartLevel
};
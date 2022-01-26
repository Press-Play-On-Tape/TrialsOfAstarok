#pragma once

enum GameState {
	Title_Init,
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
  Player = 0,  // Sprites
  Triangleo,
  Starmano,
  Smileo,
  Bolt,
  Mushroom = 5,
  QBlock,  // Interactive Tiles
  BQBlock,
  MushBlock,
  Bricks = 9,
  AboveGroundExit,
  UnderGroundExit,
  Sign,
  Fireball,
  Coin,
  Chest_Closed,
  Chest_Open,
};

enum EventType {
  Off = 0,
  Playing,
  Death_Init,
  Death,
  LevelExit,
  StartLevel
};
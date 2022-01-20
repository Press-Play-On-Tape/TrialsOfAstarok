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
  STBigSquario,
  STTriangleo,
  STStarmano,
  STSmileo,
  STBolt,
  STMushroom = 6,
  STQBlock,  // Interactive Tiles
  STBQBlock,
  STMushBlock,
  STBricks = 10,
  STPipeCapLeft,
  STPipeCapRight,
  STTopPipeCapLeft,
  STTopPipeCapRight,
  STPipeLeft,
  STPipeRight,
  STAboveGroundExit,
  STUnderGroundExit,
  NumObjectTypes = 18,
  STSign,
};

enum EventType {
  Off = 0,
  Playing,
  Death_Init,
  Death,
  PipeDrop,
  PipeRise,
  LevelExit,
  StartLevel
};
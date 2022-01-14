#pragma once

enum GameState {
  Title,
  Game_Init,
  Game_Play,
  HighScore_Check,
  HighScore_Enter,
  HighScore_DisplayAll,
};

enum SpriteDataLayout {
  SpriteWidth = 0,
  SpriteHeight,
  SpriteMaxFrame,
  SpritegetCyclesPerFrame,
  SpriteFlags,
  SpriteSpeed,
  SpriteIntelligence,
  SpriteMasks,
  SpriteImageData
};

enum SquarioButtons {
  ButtonLeft = 0,
  ButtonUp,
  ButtonRight,
  ButtonDown,
  ButtonJump,
  ButtonRun,
  NumButtons
};

enum Direction { Up, Down, Left, Right };

enum ObjectTypes {
  STSquario = 0,  // Sprites
  STBigSquario,
  STTriangleo,
  STStarmano,
  STSmileo,
  STBolt,

  STMushroom,

  STQBlock,  // Interactive Tiles
  STBQBlock,
  STMushBlock,
  STBricks,
  STPipeCapLeft,
  STPipeCapRight,
  STTopPipeCapLeft,
  STTopPipeCapRight,
  STPipeLeft,
  STPipeRight,

  NumObjectTypes
};

enum EventType {
  Off = 0,
  Playing,
  Death_Init,
  Death,
  PipeDrop,
  PipeRise,
};
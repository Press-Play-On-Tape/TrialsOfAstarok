#include "src/utils/Arduboy2Ext.h"
#include "SquarioGame.h"


void SquarioGame::drawScorePanel(Arduboy2 &arduboy) {

    arduboy.drawRect(16,8,96,48, WHITE); // Box border
    arduboy.fillRect(17,9,94,46, BLACK); // Black out the inside
    Sprites::drawSelfMasked(30, 12, Images::GameOver, 0);
    
    arduboy.setCursor(26,29); arduboy.print(F("Score"));
    arduboy.setCursor(20,37); arduboy.print(F("+Dist."));
    arduboy.setCursor(26,45); arduboy.print(F("Total"));

    arduboy.setCursor(76, 29);
    arduboy.print(this->score);
    arduboy.setCursor(76, 37);
    arduboy.print(this->distancePoints);
    arduboy.setCursor(76, 45);
    arduboy.print(this->totalScore);

}

void SquarioGame::drawMobs() {
//  Serial.println("drawMobs() start");
  for (uint8_t a = 0; a < Constants::SpriteCap; a++) {
    if (this->mobs[a].getActive()) {
//  Serial.print("drawMobs() 1 : ");
//  Serial.print(this->cameraX);
//  Serial.print(", AI:");
//  Serial.println(this->mobs[a].getRightX() - this->cameraX);
      if (this->mobs[a].getRightX() - this->cameraX > 0 && this->mobs[a].x - this->cameraX < 128) {
        this->mobs[a].draw();
      }
    }
  }
//  Serial.println("drawMobs() end");
}

void SquarioGame::drawHUD(Arduboy2 &arduboy) {

  uint16_t tmpScore = this->score + this->distancePoints + this->player.x / Constants::TileSize; 
  uint8_t digits[6] = {};
  extractDigits(digits, tmpScore);
// Serial.println(this->lives);
  if (this->mapNumber % 2 == MapLevel::AboveGround) {

    // arduboy.fillRect(0, 0, 58, 8, WHITE);
    for(size_t index = 0; index < 58; ++index) arduboy.sBuffer[index] = 0xFF;

    Sprites::drawErase(1, 1, Images::Heart, this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline);
    Sprites::drawErase(9, 1, Images::Heart, this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline);
    Sprites::drawErase(17, 1, Images::Heart, this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline);

    for (uint8_t x = 6; x > 0; x--) {
      Sprites::drawErase(27 + ((6 - x) * 5), 1, Images::Numbers, digits[x - 1]);
    }

  }
  else {

    for(size_t index = 0; index < 58; ++index) arduboy.sBuffer[index] = 0x00;

    Sprites::drawSelfMasked(1, 1, Images::Heart, this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline);
    Sprites::drawSelfMasked(9, 1, Images::Heart, this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline);
    Sprites::drawSelfMasked(17, 1, Images::Heart, this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline);

    for (uint8_t x = 6; x > 0; x--) {
      Sprites::drawSelfMasked(27 + ((6 - x) * 5), 1, Images::Numbers, digits[x - 1]);
    }

  }

}

void SquarioGame::drawMap_Background(Arduboy2 &arduboy) {

  #ifdef ORIG_GAME_TILESIZE_8

  int mountainOffset = (this->cameraX / 4) % 64;
  int mountainYOffset = (this->cameraY / 12) - 4;
  
  if (this->mapNumber % 2) {
    arduboy.drawBitmap( 0 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
    arduboy.drawBitmap(64 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
    arduboy.drawBitmap(128 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
  }
  else {
    for (uint8_t a = 0; a < 196; a += 96) {
    arduboy.drawBitmap( a - (this->cameraX / 4) % 96, mountainYOffset+20, UndergroundBricks, 37, 24, 1);
    }

  }
  #else

  int16_t backgroundXOffset = (this->cameraX / 4) % 64;
  int16_t backgroundYOffset = (this->cameraY / 12) - 8;

  if (this->mapNumber % 2 == MapLevel::AboveGround) {

    Sprites::drawOverwrite(0 - backgroundXOffset, backgroundYOffset, Images::Sky, 0);
    Sprites::drawOverwrite(64 - backgroundXOffset, backgroundYOffset, Images::Sky, 0);
    Sprites::drawOverwrite(128 - backgroundXOffset, backgroundYOffset, Images::Sky, 0);

  }
  else {

    for (uint8_t a = 0; a <= 128; a += 64) {
      Sprites::drawOverwrite(a + 2 - backgroundXOffset, backgroundYOffset, Images::Underground_Chain, 0);
      Sprites::drawOverwrite(a + 22 - backgroundXOffset, backgroundYOffset + 6, Images::Underground_Brick, 0);
      Sprites::drawOverwrite(a + 42 - backgroundXOffset, backgroundYOffset + 11, Images::Underground_Brick, 0);
    }

  }
  #endif

  for (int x = this->cameraX / Constants::TileSize; x < (this->cameraX / Constants::TileSize) + 17; x++) {
    for (int y = this->cameraY / Constants::TileSize; y < (this->cameraY / Constants::TileSize) + 9; y++) {

      
      // if (this->level.isTile(x, y)) {
      //   #ifdef ORIG_GAME_TILESIZE_8
      //     Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, Images::SpriteImages[ObjectTypes::STBricks], Images::SpriteMasks[ObjectTypes::STBricks], 0, 0);
      //   #else
      //     if (this->mapNumber % 2 == MapLevel::AboveGround) {   
      //       Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]),  pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), MapLevel::AboveGround, 0);
      //     }
      //     else {
      //       Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]), pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), 0, 0);
      //     }
      //   #endif
      // }
      // else {
        
      //   uint8_t i = this->level.checkObject(x, y);

      //   if (i != 0) {
      //     Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[i]), pgm_read_word_near(&Images::SpriteMasks[i]), 0, 0);
      //   }

      // }

      if (this->level.isTile(x, y)) {

        if (this->mapNumber % 2 == MapLevel::AboveGround) {   
          Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]),  pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), MapLevel::AboveGround, 0);
        }
        else {
          Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]), pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), 0, 0);
        }

      }
      else {

        ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

        switch (tile) {

          case ObjectTypes::STQBlock ... ObjectTypes::STPipeRight:
              Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[tile]), pgm_read_word_near(&Images::SpriteMasks[tile]), 0, 0);
              break;

          case ObjectTypes::STAboveGroundExit:
              Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX - 36, y * Constants::TileSize - this->cameraY - 24, Images::Outside_Exit_00, Images::Outside_Exit_00_Mask, 0, 0);
            break;

          case ObjectTypes::STUnderGroundExit:
              Sprites::drawOverwrite(x * Constants::TileSize - this->cameraX - 13, y * Constants::TileSize - this->cameraY - 4, Images::Underground_Exit_00, 0);
            break;

          default: break;
        }

      }
    }
  }
}

void SquarioGame::drawMap_Foreground(Arduboy2 &arduboy) {

  for (int x = this->cameraX / Constants::TileSize; x < (this->cameraX / Constants::TileSize) + 17; x++) {

    for (int y = this->cameraY / Constants::TileSize; y < (this->cameraY / Constants::TileSize) + 9; y++) {

      if (!this->level.isTile(x, y)) {

        ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

        switch (tile) {

          case ObjectTypes::STAboveGroundExit:
            Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX - 10, y * Constants::TileSize - this->cameraY - 24, Images::Outside_Exit_01, Images::Outside_Exit_01_Mask, 0, 0);
            break;

          case ObjectTypes::STUnderGroundExit:
            Sprites::drawOverwrite(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY - 4, Images::Underground_Exit_01, 0);
            break;

          default: break;

        }

      }
    }
  }
}

void SquarioGame::drawPlayer(Arduboy2 &arduboy) {
  this->player.draw();
  if (this->health) {
    for (uint8_t a = 0; a < this->health; a++) {
      arduboy.drawFastHLine(this->player.x + 1 - this->cameraX, this->player.y+11-(a*2)-this->cameraY, 6, WHITE);
      arduboy.drawFastHLine(this->player.x + 1 - this->cameraX, this->player.y+10-(a*2)-this->cameraY, 6, WHITE);
    }
  }  
}

void SquarioGame::draw(Arduboy2 &arduboy) {

  switch (this->event) {

    case EventType::Death_Init:
    case EventType::Death:
    case EventType::Playing:   
      drawMap_Background(arduboy); 
      #ifndef ORIG_GAME_TILESIZE_8
      drawHUD(arduboy);
      #endif
      drawMobs(); 
      if (!(this->eventCounter % 2)) drawPlayer(arduboy);
      drawMap_Foreground(arduboy); 
      break;

    case EventType::PipeDrop:
    case EventType::PipeRise:  
      drawPlayer(arduboy); 
      drawMap_Background(arduboy); 
      #ifndef ORIG_GAME_TILESIZE_8
      drawHUD(arduboy);
      #endif
      drawMobs(); 
      drawMap_Foreground(arduboy); 
      break;

    default: break;

  }

}

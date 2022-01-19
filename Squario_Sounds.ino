void SoundEngine() {
//   if (!SoundOn) return;
//   if (!display.tunes.playing()) {
//     if      (SoundCounter < 8) /* display.tunes.playScore(Verse) */;
//     else if (SoundCounter < 12) /* display.tunes.playScore(PreChorus) */;
//     else if (SoundCounter < 16) /* display.tunes.playScore(Chorus) */;
//     SoundCounter++;
//     if (SoundCounter == 16) SoundCounter = 0;
//   }
//   if (game.SFX) {
//     SFXNoteSet = SFXFrequencies;
//     SFX = game.SFX;
//     game.SFX = NULL;
//     SFX_Counter = 2;
//     lastNote = 0;
//   }
//   if (SFX) {
//     if (currTime < lastNote + duration) return;
//     byte Packet = pgm_read_byte(SFX + SFX_Counter++);
//     if (Packet == 0xFF) {
//       SFX = NULL;
//       SFX_Counter = -1;
//       return;
//     }
//     byte note = (Packet >> 4) & 0x0F;
//     byte dMultiplier = Packet & 0x0F;
//     duration = pgm_read_byte(SFX) + (pgm_read_byte(SFX + 1) * dMultiplier);
//     unsigned long freq = (pgm_read_word(SFXNoteSet + note - 1)) / 2;
//     display.tunes.tone(freq, duration);
//     lastNote = currTime;
//   }
}
#include <Arduboy2.h>
#include "src/Images.h"
// Add frames to the keyframes array to create your animation
// The values are:
// frames since last frame, the first frame should always be 1 here.
// Left shoulder angle
// Left elbow angle
// Right shoulder angle
// Right elbow angle
// Left thigh angle
// Left knee angle
// Right thigh angle
// Right knee angle
// Head X position
// Head Y position
// Torso X position, shoulders and thighs are connected to the torso
// Torso Y position
int keyframes[][13] = {{1, 27, 0, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24}, {120, 0, 9, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24},
                       {20, 1, 4, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24},{60, 1, 9, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24},
                       {60, 1, 4, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24},{60, 1, 9, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24},
                       {120, 27, 0, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24}, {20, 27, 0, 27, 0, 30, 23, 24, 6, 64, 18, 62, 26},
                       {20, 27, 0, 27, 0, 27, 0, 27, 0, 64, 16, 62, 24}};

template <typename type>
type sign(type value) { 
 return type((value>0)-(value<0)); 
}

Arduboy2 arduboy;

const int rots[36] = {1,1,2,3,4,5,6,7,8,
                      26,25,24,23,22,21,20,19,19,
                      27,28,29,30,31,32,33,34,35,
                      17,16,15,14,13,12,11,10,9};
                
const int nextoffset[36][2] = { {-7,0},  {-6,-1}, {-6,-2}, {-6,-3}, {-5,-4}, {-4,-5}, {-3,-6}, {-2,-6}, {-1,-6}, 
                                {0,-7},  {1,-6},  {2,-6},  {3,-6},  {4,-5},  {5,-4},  {6,-3},  {6,-2},  {6,-1},  
                                {7,0},   {6,1},   {6,2},   {6,3},   {5,4},   {4,5},   {3,6},   {2,6},   {1,6},   
                                {0,7},   {-1,6},  {-2,6},  {-3,6},  {-4,5},  {-5,4},  {-6,3},  {-6,2},  {-6,1}};

float framedat[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int currentframe = 0;
float LShoulder = keyframes[0][1];
float LElbow = keyframes[0][2];
float RShoulder = keyframes[0][3];
float RElbow = keyframes[0][4];
float LThigh = keyframes[0][5];
float LKnee = keyframes[0][6];
float RThigh = keyframes[0][7];
float RKnee = keyframes[0][8];
float headX = 64;
float headY = 16;
float torsoX = 62;
float torsoY = 24;

void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.initRandomSeed();

}

int clampRot(int rot) {
  while (rot < 0) rot += 35;
  rot = rot % 36;
  return rot;
}

void drawLimb(int x, int y, int rot) {
  int offsetX = -5;
  int offsetY = -5;
  if (rot > 8) {
    offsetX = -5+4;
    offsetY = -5;
  }
  if (rot > 17) {
    offsetY = -5+3;
  }
  if (rot > 26) {
    offsetX = -5;
  }
  Sprites::drawSelfMasked(x + offsetX, y + offsetY, Images::Bones, rots[rot]);
}

void loop() {

  if (!(arduboy.nextFrame())) return;
  
  arduboy.pollButtons();
  arduboy.setCursor(0,0);

  if (framedat[0] >= keyframes[currentframe][0]) {
    framedat[0] = 0;
    for(int i = 1; i<9; i++) {
      framedat[i] = keyframes[currentframe][i] - keyframes[currentframe+1][i];
      if (framedat[i] < -18) framedat[i] = keyframes[currentframe+1][i] - keyframes[currentframe][i] - 18;
      if (framedat[i] > 18) framedat[i] = keyframes[currentframe+1][i] - keyframes[currentframe][i] + 18;
      framedat[i] = framedat[i] / keyframes[currentframe+1][0];
    }
    for(int i = 9; i<13; i++) {
      framedat[i] = keyframes[currentframe][i] - keyframes[currentframe+1][i];
      framedat[i] = framedat[i] / keyframes[currentframe+1][0];
    }
    LShoulder = keyframes[currentframe][1];
    LElbow = keyframes[currentframe][2];
    RShoulder = keyframes[currentframe][3];
    RElbow = keyframes[currentframe][4];
    LThigh = keyframes[currentframe][5];
    LKnee = keyframes[currentframe][6];
    RThigh = keyframes[currentframe][7];
    RKnee = keyframes[currentframe][8];
    headX = keyframes[currentframe][9];
    headY = keyframes[currentframe][10];
    torsoX = keyframes[currentframe][11];
    torsoY = keyframes[currentframe][12];
    currentframe ++;
    if (currentframe >= sizeof(keyframes)/sizeof(keyframes[0])) {
      currentframe = 0;
      LShoulder = keyframes[currentframe][1];
      LElbow = keyframes[currentframe][2];
      RShoulder = keyframes[currentframe][3];
      RElbow = keyframes[currentframe][4];
      LThigh = keyframes[currentframe][5];
      LKnee = keyframes[currentframe][6];
      RThigh = keyframes[currentframe][7];
      RKnee = keyframes[currentframe][8];
      headX = keyframes[currentframe][9];
      headY = keyframes[currentframe][10];
      torsoX = keyframes[currentframe][11];
      torsoY = keyframes[currentframe][12];
      for(int i = 1; i < 13; i++) {
        framedat[i] = 0;
      }
    }
  }
  //arduboy.print(framedat[9]);
  LShoulder -= framedat[1];
  LElbow -= framedat[2];
  RShoulder -= framedat[3];
  RElbow -= framedat[4];
  LThigh -= framedat[5];
  LKnee -= framedat[6];
  RThigh -= framedat[7];
  RKnee -= framedat[8];
  headX -= framedat[9];
  headY -= framedat[10];
  torsoX -= framedat[11];
  torsoY -= framedat[12];
  framedat[0] ++;


  Sprites::drawSelfMasked(headX, headY, Images::Head, 0);
  Sprites::drawSelfMasked(torsoX, torsoY, Images::Torso, 0);

  int angleLShoulder = clampRot(LShoulder);
  int angleRShoulder = clampRot(RShoulder);
  int angleLElbow = clampRot(angleLShoulder + LElbow);
  int angleRElbow = clampRot(angleRShoulder + RElbow);
  int angleLThigh = clampRot(LThigh);
  int angleRThigh = clampRot(RThigh);
  int angleLKnee = clampRot(angleLThigh + LKnee);
  int angleRKnee = clampRot(angleRThigh + RKnee);

  drawLimb(torsoX - 2, torsoY + 1, angleLShoulder);
  drawLimb(torsoX - 2 + nextoffset[angleLShoulder][0], torsoY + 1 + nextoffset[angleLShoulder][1], angleLElbow);
  drawLimb(torsoX + 13, torsoY + 1, angleRShoulder);
  drawLimb(torsoX + 13 + nextoffset[angleRShoulder][0], torsoY + 1 + nextoffset[angleRShoulder][1], angleRElbow);
  drawLimb(torsoX + 2, torsoY + 13, angleLThigh);
  drawLimb(torsoX + 2 + nextoffset[angleLThigh][0], torsoY + 13 + nextoffset[angleLThigh][1], angleLKnee);
  drawLimb(torsoX + 9, torsoY + 13, angleRThigh);
  drawLimb(torsoX + 9 + nextoffset[angleRThigh][0], torsoY + 13 + nextoffset[angleRThigh][1], angleRKnee);
  
  arduboy.display(true);

}

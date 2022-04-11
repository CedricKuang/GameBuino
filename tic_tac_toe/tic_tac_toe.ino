#include <TicTacToeDisplay.h>

#define VRX A0
#define VRY A1
#define SW 2
#define UP_THRESHOLD 900
#define DOWN_THRESHOLD 100
#define RIGHT_THRESHOLD 900
#define LEFT_THRESHOLD 100

float vrx_value = 0;
float vry_value = 0;
int sw_value = 0;
int selected_block = -1;
int current_block = 0;
bool is_O = true;
// 0: empty, 1: O, 2: X
int current_game[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

TicTacToeDisplay display; 

void setup() {
  // set up control reading  
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // set up display
  display.begin();
  display.drawBoard();
  delay(500);
}

void loop() {
  // check victory
  check_victory();
  
  while(selected_block == -1)
  {
    display.selectSquare(current_block);
    // read in joystick value
    vrx_value = analogRead(VRX);
    vry_value = analogRead(VRY);
    sw_value = digitalRead(SW);
    delay(100);

    if(vrx_value > UP_THRESHOLD && current_block != 0 && 
      current_block != 1 && current_block != 2)
    {
      display.deselectSquare(current_block);
      current_block -= 3;
    }
    if(vrx_value < DOWN_THRESHOLD && current_block != 6 && 
      current_block != 7 && current_block != 8)
    {
      display.deselectSquare(current_block);
      current_block += 3;
    }
    if(vry_value > RIGHT_THRESHOLD && current_block != 2 && 
      current_block != 5 && current_block != 8)
    {
      display.deselectSquare(current_block);
      current_block += 1;
    }
    if(vry_value < LEFT_THRESHOLD && current_block != 0 && 
      current_block != 3 && current_block != 6)
    {
      display.deselectSquare(current_block);
      current_block -= 1;
    }
    if(sw_value == 0 && current_game[current_block] == 0)
    {
      selected_block = current_block; 
    }
  }
  display.deselectSquare(selected_block);
  if (is_O)
  {
    display.drawO(selected_block);
    current_game[selected_block] = 1;
  }
  else
  {
    display.drawX(selected_block);
    current_game[selected_block] = 2;
  }
  current_block = 0;
  selected_block = -1;
  is_O = !is_O;
}

void declare_victory(char side)
{
  while(true) 
  {
    display.flashScreen();
    if (side == 'o')
    {
      display.drawSmallText("Congratulations Player O! You win!");
    }
    else if (side == 'x')
    {
      display.drawSmallText("Congratulations Player X! You win!");
    }
    else if (side == 't')
    {
      display.drawSmallText("Ties");
    }
  }
}

void check_victory() 
{
  int t = 0;
  // check horizontal
  while (t <= 6)
  {
    if (current_game[t] == current_game[t+1] && current_game[t+1] == current_game[t+2])
    {
      if (current_game[t] == 1)
      {
        display.drawVictoryLine(t,t+2);
        declare_victory('o');
      }
      else if (current_game[t] == 2)
      {
        display.drawVictoryLine(t,t+2);
        declare_victory('x');
      }
    }
    t += 3;
  }

  // check vertical
  t = 0;
  while (t <= 2)
  {
    if (current_game[t] == current_game[t+3] && current_game[t+3] == current_game[t+6])
    {
      if (current_game[t] == 1)
      {
        display.drawVictoryLine(t,t+6);
        declare_victory('o');
      }
      else if (current_game[t] == 2)
      {
        display.drawVictoryLine(t,t+6);
        declare_victory('x'); 
      }
    }
    t++;
  }

  // check diagonal
  if ((current_game[0] == current_game[4] && current_game[4] == current_game[8]) || 
      (current_game[2] == current_game[4] && current_game[4] == current_game[6]) )
  {
      if (current_game[0] == 1)
      {
        display.drawVictoryLine(0,8);
        declare_victory('o');
      }
      else if (current_game[0] == 2)
      {
        display.drawVictoryLine(2,6);
        declare_victory('x'); 
      }
  }

  // check if the board is full
  for (t = 0; t <= 8; t++) 
  {
    if (current_game[t] == 0)
      return;
  }

  declare_victory('t');
}

#include <TicTacToeDisplay.h>

TicTacToeDisplay display;

void setup() {
  display.begin();
  display.drawBoard();
  delay(500);
}

void loop() {
  display.selectSquare(0);
  delay(200);
  display.deselectSquare(0);
  display.drawX(0); //this draws an X at square 0, which is the top left
  delay(500);
  display.selectSquare(4);
  delay(200);
  display.deselectSquare(4);
  display.drawO(4); //this draws an O at square 4, which is the middle
  delay(500);
  display.selectSquare(1);
  delay(200);
  display.deselectSquare(1);
  display.drawX(1); //this draws an X at square 1, which is the top center
  delay(500);
  display.selectSquare(6);
  delay(200);
  display.deselectSquare(6);
  display.drawO(6); //this draws an O at square 6, which is the bottom left
  delay(500);
  display.selectSquare(2);
  delay(200);
  display.deselectSquare(2);
  display.drawX(2); //this draws an X at square 2, which is the top right
  delay(500);

  display.drawVictoryLine(0,2);
  delay(500);
  display.flashScreen();
  delay(500);

  display.drawSmallText("Congrats              Player X!             You Win!");
  delay(2000);
  display.drawBoard();
}

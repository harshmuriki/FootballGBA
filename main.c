#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
#include "images/garbage.h"
#include "images/footballpost.h"
#include "images/field.h"
#include "images/football.h"
#include "images/winimg.h"
#include "images/lose.h"
#include "images/welcome.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state
{
  START,
  PLAY,
  WIN,
  LOSE,
};

int main(void)
{
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  // initialize the ball
  struct ball currball, pastball;
  currball.row = HEIGHT / 2;
  currball.col = WIDTH / 2;
  pastball.row = HEIGHT / 2;
  pastball.col = WIDTH / 2;

  int curr_time = 0;
  while (1)
  {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    // Add timer here:
    waitForVBlank();
    switch (state)
    {
    case START:
      waitForVBlank();
      curr_time = 0;
      // setPixel(15, 5, 0x7fef);
      // drawImageDMA(0, 0, FOOTBALL_POST_HEIGHT, FOOTBALL_POST_LENGTH, football_post);
      drawFullScreenImageDMA(field);
      state = PLAY;
      // undrawImageDMA(10, 10, FOOTBALL_WIDTH, FOOTBALL_HEIGHT, football);
      // if (KEY_DOWN(BUTTON_START, currentButtons))
      // {
      //   curr_time = 0;
      //   state = PLAY;
      //   currball.row = HEIGHT / 2;
      //   currball.col = WIDTH / 2;
      // }
      break;

    case PLAY:
      curr_time++;
      // drawFullScreenImageDMA(field);
      drawImageDMA(currball.row, currball.col, FOOTBALL_WIDTH, FOOTBALL_HEIGHT, football);
      // Add a timer that starts here
      char time_remain[100];
      sprintf(time_remain, "Time remaining: %d", 10 - curr_time / 60);
      undrawImageDMA(130, 100, 30, 30, field);
      drawString(130, 5, time_remain, BLACK);
      // undrawImageDMA(130, 100, 30, 30, field);
      if (KEY_DOWN(BUTTON_SELECT, currentButtons))
      {
        curr_time = 0;
        state = START;
        currball.row = HEIGHT / 2;
        currball.col = WIDTH / 2;
      }
      if ((10 - curr_time / 60) <= 0)
      {
        state = LOSE;
      }

      if ((currball.row + FOOTBALL_HEIGHT + 1 >= 160) || (currball.col + FOOTBALL_WIDTH + 1 >= 240) || (currball.col - 1 < 240 && currball.col < 0) || (currball.row - 1 < 160 && currball.row < 0))
      {
        state = LOSE;
      }

      if (KEY_DOWN(BUTTON_DOWN, currentButtons)) // Go Down
      {
        // currball.row = pastball.row + 10;
        if (currball.row + FOOTBALL_HEIGHT + 1 < 160)
        {
          currball.row += 1;
        }
      }
      if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) // Go Right
      {
        // currball.row = pastball.row + 10;
        if (currball.col + FOOTBALL_WIDTH + 1 < 240)
        {
          currball.col += 1;
        }
      }
      if (KEY_DOWN(BUTTON_LEFT, currentButtons)) // Go Left
      {
        // currball.row = pastball.row + 10;
        if (currball.col - 1 < 240 && currball.col >= 0)
        {
          currball.col -= 1;
        }
      }
      if (KEY_DOWN(BUTTON_UP, currentButtons)) // Go Up
      {
        // currball.row = pastball.row + 10;
        if (currball.row - 1 < 160 && currball.row >= 0)
        {
          currball.row -= 1;
        }
      }

      if (((currball.col + FOOTBALL_WIDTH) >= 190) && ((currball.row + FOOTBALL_HEIGHT) >= 15) && ((currball.row + FOOTBALL_HEIGHT) <= 145))
      {
        state = WIN;
      }
      waitForVBlank();
      // Undraw the last football and draw the new one
      // drawRectDMA(pastball.row, pastball.col, FOOTBALL_WIDTH, FOOTBALL_HEIGHT, BLACK);
      undrawImageDMA(pastball.row, pastball.col, FOOTBALL_WIDTH, FOOTBALL_HEIGHT, field);
      drawImageDMA(currball.row, currball.col, FOOTBALL_WIDTH, FOOTBALL_HEIGHT, football);

      pastball.row = currball.row;
      pastball.col = currball.col;
      // state = WIN;
      break;

    case WIN:
      drawFullScreenImageDMA(winimg);
      if (KEY_DOWN(BUTTON_SELECT, currentButtons))
      {
        state = START;
        currball.row = HEIGHT / 2;
        currball.col = WIDTH / 2;
      }
      break;

    case LOSE:
      drawFullScreenImageDMA(lose);
      // drawCenteredString(10, 10, HEIGHT / 2, WIDTH / 2, "You Lost:(. Game Over.", WHITE);
      if (KEY_DOWN(BUTTON_SELECT, currentButtons))
      {
        state = START;
        currball.row = HEIGHT / 2;
        currball.col = WIDTH / 2;
      }
      // state = ?
      break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}

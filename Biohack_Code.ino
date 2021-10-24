#include "LedControl.h"

LedControl lc=LedControl(11,13,10,4);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime= 5000;  // Delay between Frames

void setup()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.setIntensity(2,5);
  lc.setIntensity(3,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  Serial.begin(9600);
}

int dispArray[3][2] = { 
  {0, 0 }, 
  {0, 0 }, 
  {0, 0 }
  };

void loop()
{
   Serial.println("Please enter your text input");
   while(Serial.available() == 0) {}
   String input = Serial.readString();
   input.toLowerCase();

   clearDisplays();
   int offset = 0; /* COLUMN OFFSET; Value to offset the matrix by so that way the characters show up in proper order */ 
   int row_offset = 0; /* ROW OFFSET; Value to offset the rows so we can display 32 characters instead of 16 */
   int displayNum = -1;
   for (int len = 0; len < input.length() - 1; len++) { /* Loop through the length of the word */

          /* Sets the display number for the appropriate length so there is no overflow */
          /* Sets the row offset to fit 32 characters in two rows rather than only 16 characters in 1 row */
          if (len % 32 <= 3) {
              displayNum = 3;
              row_offset = 0;
           }
           else if (len % 32 <= 7) {
              displayNum = 2;
              row_offset = 0;
           }
           else if (len % 32 <= 11) {
              displayNum = 1;
              row_offset = 0;
           }
           else if (len  % 32 <= 15) {
              displayNum = 0;
              row_offset = 0;
           }
           else if (len % 32 <= 19) {
              displayNum = 3;
              row_offset = 5;
           }
           else if (len % 32 <= 23) {
              displayNum = 2;
              row_offset = 5;
           }
           else if (len % 32 <= 27) {
              displayNum = 1;
              row_offset = 5;
           }
           else if (len % 32 <= 31) {
              displayNum = 0;
              row_offset = 5;
           }

           /* Provides a delay for all of the characters to print if there are more than 32 characters in the input */
           if (len != 0 && len % 32 == 0) {
              delay(delayTime);
              clearDisplays();
           }
           
           if (len % 4 == 0) { /* Fits the characters on the properly display (3, 2, 1, 0) */
              offset = 0;
           }

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {

           modifyArray(dispArray, input[len]); /* Modify the sent array based on the character */
           lc.setLed(displayNum, i + row_offset, j + offset, dispArray[i][j]);   /* Set the LED with the appropriate display */
        }
      }

      offset = offset + 2;
   }
}

void clearDisplays() {
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

void modifyArray( int arr[][2], char val) {

  /* Switch case to determine the braille makup of the character */
  switch (val) {
    case 'a':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'b':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'c':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'd':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'e':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'f':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'g':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'h':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'i':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'j':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case 'k':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'l':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'm':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'n':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'o':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'p':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
     case 'q':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'r':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 's':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 't':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 0;
      break;
    case 'u':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 1;
      break;
    case 'v':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 1;
      break;
    case 'w':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 1;
      break;
    case 'x':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 1;
      arr[2][1] = 1;
      break;
    case 'y':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 1;
      break;
     case 'z':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 1;
      arr[2][1] = 1;
      break;
    case '1':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case '2':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break; 
    case '3':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    case '4':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
     case '5':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
     case '6':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    case '7':
      arr[0][0] = 1;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    case '8':
      arr[0][0] = 1;
      arr[0][1] = 0;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    case '9':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    case '0':
      arr[0][0] = 0;
      arr[0][1] = 1;
      arr[1][0] = 1;
      arr[1][1] = 1;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    case ' ':
      arr[0][0] = 0;
      arr[0][1] = 0;
      arr[1][0] = 0;
      arr[1][1] = 0;
      arr[2][0] = 0;
      arr[2][1] = 0;
      break;
    default:
     arr[0][0] = 0;
  }
} 

//Solitaire_v15.
#define DisplaySerial Serial1                    
#include <Diablo_Const4D.h>
#include <Diablo_Serial_4DLib.h>

//use Serial1 to communicate with the display.
Diablo_Serial_4DLib Display(&DisplaySerial);
int state, x, y ;  // Touch state
int Selected = 0;

struct TP{                       // Scratch pad struct for storing tiles in play.
          int Locxy[4]; // x,y
          char* TileX[2];
         };
            
       TP Tx = {{0, 0, 0, 0}, "   " , "   " };
       
struct Tiles{
             char* text[4];
            };
            
       Tiles T = { " A " , " A " , " B " , " B " };

struct Button{
             int Location[2]; // x,y
             int Tag;
             }; 
                    
//       ___Name       
//      |        _Location x, y
//      |       |       _________ Tag
//      |       |      |
 Button A = {{0, 0 },  0};
 Button B = {{0, 40},  0};
 Button C = {{0, 80},  0};
 Button D = {{0, 120}, 0};

void setup() {DisplaySerial.begin(9600);SerialUSB.begin(9600);

   do{
     for (int i = 0; i < 4; i++)
       {   
       randomSeed(analogRead(5));  // Randomize using noise from pin 5.
       int NewNum = random(1, 5);
             if (A.Tag == NewNum)
             break;
         else if (A.Tag == 0){ A.Tag = NewNum;break; }
                   
         else
             if (B.Tag == NewNum)
             break;
             else if (B.Tag == 0){ B.Tag = NewNum;break; }
                 
         else
             if (C.Tag == NewNum)
             break;
             else if (C.Tag == 0){ C.Tag = NewNum;break; }
                 
         else
             if (D.Tag == NewNum)
             break;
             else if (D.Tag == 0) { D.Tag = NewNum;break; }
        }
    }while (D.Tag == 0);
      
//For handling errors
  Display.Callback4D = mycallback ;
  pinMode(4, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(4, 0);  // Reset the Display via D4     Demo code = digitalWrite(4, 1);
  delay(100);          // HIGH/LOW RESET REVERSED from Demo programs because I'm not using the shield, but rather direct to RBT wiring.
  digitalWrite(4, 1);  // unReset the Display via D4   Demo code = digitalWrite(4, 0);
  delay (5000);        // let the display start up  
  setbaudWait(BAUD_115200);
  Display.gfx_Contrast(4);
  Display.gfx_ScreenMode(LANDSCAPE); 
  Display.touch_Set(TOUCH_ENABLE);
  Display.touch_Set(TOUCH_REGIONDEFAULT);
  Display.gfx_Cls();  //clear the screen
    Display.txt_Height(2);
    Display.txt_Width(2);
    Display.gfx_MoveTo(100, 0);      
    Display.print(A.Tag);
    Display.gfx_MoveTo(100, 40);      
    Display.print(B.Tag);
    Display.gfx_MoveTo(100, 80);      
    Display.print(C.Tag);
    Display.gfx_MoveTo(100, 120);      
    Display.print(D.Tag);
  Display.gfx_Button(ON, A.Location[0], A.Location[1],DARKGRAY, RED, FONT2, 2, 2, "...");
  Display.gfx_Button(ON, B.Location[0], B.Location[1],DARKGRAY, RED, FONT2, 2, 2, "...");
  Display.gfx_Button(ON, C.Location[0], C.Location[1],DARKGRAY, RED, FONT2, 2, 2, "...");   
  Display.gfx_Button(ON, D.Location[0], D.Location[1],DARKGRAY, RED, FONT2, 2, 2, "...");   
}

void loop()
{  
 
 state = Display.touch_Get(TOUCH_STATUS);                  // get touchscreen status
     if (state == TOUCH_PRESSED)                           // if there"s a touch
         {
         x = Display.touch_Get(TOUCH_GETX);                // 480 x 272
         y = Display.touch_Get(TOUCH_GETY);
            
         if (( x > 0 && x < 70) && ( y > 0 && y < 30))  // Button A    
            {
             Display.gfx_Button(ON, 0, 0  ,  DARKGRAY, RED, FONT2, 2, 2, T.text[A.Tag-1]);
delay(1000);
             Selected = Selected + 1;
              if (Selected == 1)
                 {
                  Tx.TileX[0] = T.text[A.Tag-1];
                  Tx.Locxy[0] = 0;
                  Tx.Locxy[1] = 0;
                 }
              else
                 {
                  Tx.TileX[1] = T.text[A.Tag-1];
                  Tx.Locxy[2] = 0;
                  Tx.Locxy[3] = 0;
                 }
            }
         else
         if (( x > 0 && x < 70) && ( y > 40 && y < 70))  // Button B  
            {
             Display.gfx_Button(ON, 0, 40  ,  DARKGRAY, RED, FONT2, 2, 2, T.text[B.Tag-1]);
delay(1000);
             Selected = Selected + 1;
              if (Selected == 1)
                 {
                  Tx.TileX[0] = T.text[B.Tag-1];
                  Tx.Locxy[0] = 0;
                  Tx.Locxy[1] = 40;
                 }
              else
                 { 
                  Tx.TileX[1] = T.text[B.Tag-1];
                  Tx.Locxy[2] = 0;
                  Tx.Locxy[3] = 40;
                 }
           }
         else
         if (( x > 0 && x < 70) && ( y > 80 && y < 110))  // Button C  
            {
             Display.gfx_Button(ON, 0, 80  ,  DARKGRAY, RED, FONT2, 2, 2, T.text[C.Tag-1]);
delay(1000);
             Selected = Selected + 1;
              if (Selected == 1)
                 {
                  Tx.TileX[0] = T.text[C.Tag-1];
                  Tx.Locxy[0] = 0;
                  Tx.Locxy[1] = 80;
                 }
              else 
                 {
                  Tx.TileX[1] = T.text[C.Tag-1];
                  Tx.Locxy[2] = 0;
                  Tx.Locxy[3] = 80;
                 }
           }                                               
         else
         if (( x > 0 && x < 70) && ( y > 120 && y < 150))  // Button D  
            {
             Display.gfx_Button(ON, 0, 120  ,  DARKGRAY, RED, FONT2, 2, 2, T.text[D.Tag-1]);
delay(1000);
             Selected = Selected + 1;
              if (Selected == 1)
                 {
                  Tx.TileX[0] = T.text[D.Tag-1];
                  Tx.Locxy[0] = 0;
                  Tx.Locxy[1] = 120;
                 }
              else
                 { 
                  Tx.TileX[1] = T.text[D.Tag-1];
                  Tx.Locxy[2] = 0;
                  Tx.Locxy[3] = 120;
                 }
           }
    }  // End of Display.touch_Get
    
  switch (Selected){
      case 2: // If two tiles are selected.
             if ((Tx.TileX[0]) == (Tx.TileX[1]))  // If two tiles match. Black them out.
                {
                Display.gfx_Button(ON, Tx.Locxy[0], Tx.Locxy[1],  BLACK, BLACK, FONT2, 2, 2, "...");
                Display.gfx_Button(ON, Tx.Locxy[2], Tx.Locxy[3],  BLACK, BLACK, FONT2, 2, 2, "...");
                Selected = 0;
                }
             if ((Tx.TileX[0]) != (Tx.TileX[1]))  // If two tiles don't match. Redraw backside.
                {
                Display.gfx_Button(ON, Tx.Locxy[0], Tx.Locxy[1],  DARKGRAY, BLUE, FONT2, 2, 2, "...");
                Display.gfx_Button(ON, Tx.Locxy[2], Tx.Locxy[3],  DARKGRAY, BLUE, FONT2, 2, 2, "...");
                Selected = 0;
                }                
             break;                
  }
}

void mycallback(int ErrCode, unsigned char Errorbyte)
{
  pinMode(LED_BUILTIN, OUTPUT);
  while(1)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                        // wait for 200 ms
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                        // wait for 200 ms
  }
}

void SetThisBaudrate(int Newrate)
{
  int br ;
  DisplaySerial.flush() ;
  DisplaySerial.end() ;
  switch(Newrate)
  {
    case BAUD_115200 : br = 115200 ;
      break ;
  }
  DisplaySerial.begin(br) ;
  delay(100) ; // Display sleeps for 100
  DisplaySerial.flush() ;
}

void setbaudWait(word  Newrate)
{
  DisplaySerial.print((char)(F_setbaudWait >> 8));
  DisplaySerial.print((char)(F_setbaudWait));
  DisplaySerial.print((char)(Newrate >> 8));
  DisplaySerial.print((char)(Newrate));
  SetThisBaudrate(Newrate); // change this systems baud rate to match new display rate, ACK is 100ms away
  Display.GetAck() ;
}
//or just print char for char from a start position
void printPart(char* txt, byte start, byte len){
//  for(byte i = 0; i < len; i++){
//    SerialUSB.write(txt[start + i]);
    //same as
    SerialUSB.print(*(txt + start + 0));
  } 

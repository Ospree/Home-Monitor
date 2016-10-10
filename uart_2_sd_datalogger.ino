// Datalogger by M. Ray Burnette (c) 20130315 Commercial rights reserved
// Open Source release: http://opensource.org/licenses/GPL-3.0
// Review license in entirety and note particularly sections 15 & 16.
// Arduino 1.0.1 or higher

#include <SD.h>


#define BUFFSIZE 512
#define chipSelect 4


char buffer[BUFFSIZE];
char c;
File logfile;
int bufferidx;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {

  pinMode(chipSelect, OUTPUT);       // standard convention required for SD library
  digitalWrite(chipSelect, HIGH);    // HIGH meaning SD not selected!
  
  Serial.begin(57600);    // Open Serial 0 to be used as debug port, 57600 baud
  Serial1.begin(9600);    // Open Serial 1 to be used for SD card datalog
  
  delay(100);
  
  Serial.print(F("Serial init at 57600 BAUD\r\n"));
  Serial.print(F("(c) 2013 SofKinetics: Serial Data Logger\n\r"));

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    
    Serial.println(F("Card initialization failed!"));
 
    int i = millis() + 2000; // 5 seconds
    
    Serial.println(F("Insert card or reseat card now.  Reset pending..."));
    
    do {
        delay(250);
     } while(  i > millis() );
     
    Serial.println("Reset!");
    delay(250);
    
    resetFunc();  //call reset function to reboot Arduino code
  }

  // Open the SD card logfile by name, either Create, Open, Append
  logfile = SD.open("logfile.txt", O_CREAT | O_WRITE | O_APPEND);
  
  // Test to ensure the file pointer was correctly set
  if( ! logfile ) {
    int i = millis() + 2000; // 1 seconds
    
    Serial.print(F("Could not open logfile \n\r"));
    
    do {
        delay(250);
     } while( i > millis() ); // stay in error loop for 5 seconds
    
    Serial.println(F("Card write failed!  Halted..."));
    
    do; while(true); // halt
  
  } else {
      Serial.println(F("Writing to: logfile.txt")); 
      Serial.println(F("Ready to accept serial data..."));
  }

  // discard any random input
  while (Serial1.read() >= 0) {}
  
} // setup

void loop() {
  
  
  // read into program buffer, increment index
  if (Serial1.available()) {
      
      c = Serial1.read();
      buffer[bufferidx++] = c;  // Store character in array and increment index
      
      Serial.print(c);
      
      // CR record termination or buffer full? (CR+LF is common, so don't check both)
      // See notes section regarding this implementation:
      if (c == '\r' || (bufferidx >= BUFFSIZE-1)) {
        buffer[bufferidx] = 0;                               // terminate it with null at current index
        logfile.write((uint8_t *) buffer, (bufferidx + 1));  //write the program buffer to SD lib backend buffer
        logfile.flush();
        bufferidx = 0;     // reset buffer pointer
      }
  }                                                          //if serial available

}



#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


//set up pins for relay
const int relayPin = 2;
 
void setup() 
{
  digitalWrite(relayPin, LOW);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  //screen
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 32, WHITE);
  display.drawPixel(127, 32, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,14);
  display.print("clue reader");

  // update display with all of the above graphics
  display.display();

  delay(1500);
  
  display.clearDisplay();
  display.display();

}
void loop(){

  //clear deisplay
  display.clearDisplay();
  display.display();
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "75 14 B0 2C") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("Access Granted");
    display.display();
    
    
  }
  else if (content.substring(1) == "DA FE AC 80")//"look where you build towers"
  {
    //Serial.println("Authorized access");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("Look where you   build towers");
    display.display();
    delay(30000);
    
  }
  else if (content.substring(1) == "5A 29 A4 80")//"its all fun and games"
  {
    //Serial.println("Authorized access");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("its all fun      and games");
    display.display();
    delay(30000);
   
  }
  else if (content.substring(1) == "E7 DC 3B B3")//"piece together   this clue"
  {
    //Serial.println("Authorized access");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("piece together     this clue");
    display.display();
    delay(30000);
    
  }
  else if (content.substring(1) == "DC 77 59 57")//"OG's favorite     activity"
  {
    //Serial.println("Authorized access");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("OG's favorite      activity");
    display.display();
    delay(30000);
    
  }
  else if (content.substring(1) == "D7 57 30 B2")//"time to get       clean"
  {
    //Serial.println("Authorized access");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("time to get       clean");
    display.display();
    delay(30000);
   
  }
  else   
  {
    Serial.println(" Access denied");
    //turn off relay

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,14);
    display.print("Access Denied");
    display.display();
    
    delay(3000);
  }
  digitalWrite(relayPin, LOW);
} 

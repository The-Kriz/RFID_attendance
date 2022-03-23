// libraries used
#include <SPI.h>
#include <MFRC522.h>

//pins & attribute values
#define SS_PIN 10
#define RST_PIN 9
#define DELAY 5000
#define Students 3 // enter number of people who has access

// User Tag Id and User name 
const char* verified_rfid[] = 
{
"70 82 7A 89",
"1B 6F B3 73",
} ;// Enter UID of the cards that need the access to the room
const char* employ[]=
{
"Akashy antony",
"Nived k",
};

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{
  Serial.begin(9600);  
  SPI.begin();          
  mfrc522.PCD_Init();  

  Serial.println("Put your card to the reader...");
  Serial.println();
}
void loop() 
{
  // Look for new card on the RFID reader 
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
  bool foundTag = false ;
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
  
  for(int j = 0;j < Students ;j++)
    {
    if (content.substring(1) == verified_rfid[j])
      {
        Serial.println(employ[j]);
        Serial.println("Attendance Marked");
        foundTag = true;
        Serial.println();
        delay(DELAY);
      }}
    if (!foundTag)
        {
          Serial.println("Student Details not found!");
          delay(DELAY);
        }
      
    }

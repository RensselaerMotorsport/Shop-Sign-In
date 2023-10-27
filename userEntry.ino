//get user ID from card then add card to database

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // make MFRC522
 
void setup() 
{
    Serial.begin(9600);   // start serial monitor
    SPI.begin();          // start SPI 
    mfrc522.PCD_Init();   // Initialize MFRC522
    Serial.println("Put card on scanner to enter into database");

    String names[10]; //create array to store names
    int i = 0; //create counter for array
    //create array to store card IDs
    String cardIDs[10];

  Serial.println();

}
/*
    Convert card number(0005880248) to hex - 0x59B9B8
    Get last 8 hex numbers and convert in to 4 bit binary - 0000 0000 0101 1001 1011 1001 1011 1000
    Above binary with even parity bits included - 0000000000010101001010111100101011110001
*/

void loop() 
{
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

    Serial.println("Enter your name: "); //print prompt for user to enter their name
    while (Serial.available() == 0) {
      // wait for user input
    }
    String name = Serial.readString(); // store user input to name string
    // print name to serial monitor
    Serial.print("Name: ");
    Serial.println(name);
    //loop to store name in next array slot
    for (int i = 0; i < 10; i++) {
      if (names[i] == "") {
        names[i] = name;
        names[i] = content.substring(1);
        break;
      }
    }

    //loop for all cards in array
    for (int i = 0; i < 10; i++) {
        Serial.print("Name: ");
        Serial.println(names[i]);
        Serial.print("Card ID: ");
        Serial.println(cardIDs[i]);
        if (content.substring(1) == names[0]) //change here the UID of the card/cards that you want to give access
        {
            Serial.println("Authorized access");
            Serial.println();
            delay(3000);
        }
        
        else   {
            Serial.println(" Access denied");
            delay(3000);
        }
    }
} 
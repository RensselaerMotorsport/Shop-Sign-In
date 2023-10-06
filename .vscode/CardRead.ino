#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5          
#define SS_PIN          10         
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 card

void setup() {
	Serial.begin(9600);		
	while (!Serial);		
	SPI.begin();			
	mfrc522.PCD_Init();		
	delay(4);				
	mfrc522.PCD_DumpVersionToSerial();	// Show details of MFRC522 card 
	Serial.println(F("Scan card"));
}

void loop() {
	if ( ! mfrc522.PICC_IsNewCardPresent()) { //reset if no new card present
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial()) { //select card if it exists
		return;
	}


	Serial.print("Card ID #:"); //show ID on serial monitor
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
	if (content.substring(1) == "HERE") //put card ID for access into where it says "HERE"
	//make a database here of all the card IDs that are allowed access
	{
		Serial.println("Authorized access");
		Serial.println();
		delay(3000);
	}
	
	else   {
		Serial.println(" Access denied"); // deny access if card ID is not in database
		delay(3000);
	}

	//mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); //dump card info
}

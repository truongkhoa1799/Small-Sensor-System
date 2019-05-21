#include <SPI.h>
#include <MFRC522.h>
#include <Display_RFID.h>
MFRC522 mfrc522(2, HIGH);   // Create MFRC522 instance.
#define MASTER "30 D7 52 73"
	
String RFID_read()
{
	//===================Show UID on serial monitor=====================

	Serial.println();
	Serial.print(" UID tag :");
	String content = "";
	byte letter;
	for (byte i = 0; i < mfrc522.uid.size; i++)
	{
		Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(mfrc522.uid.uidByte[i], HEX);
		content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		content.concat(String(mfrc522.uid.uidByte[i], HEX));
	}
	content.toUpperCase();
	return content.substring(1);
}

void checkAccess(String uid, bool &access_allow)
{
		//====================check id=======================================
		if (uid == MASTER) //change UID of the card that you want to give access // master
		{
			lcd.clear();
			//=====================cout welcome===============
			lcd.setCursor(3, 0);
			lcd.println(" Welcome       ");
			lcd.setCursor(0, 1);
			lcd.println("Mr.Khoa Handsome ");
			delay(2000);
			//====================cout have a nice day=======
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.println(" Have A NICE DAY            ");
			delay(1500);
			access_allow = true;
			//===================cout temp and humid=========
		}
		else {
			lcd.clear();
			Serial.println(" Access Denied ");
			lcd.println(" Access Denied    ");
			delay(2000);
		}
}
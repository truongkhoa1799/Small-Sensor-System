#include <Wire.h>
#include <Ticker.h>
#include <check_RFID.h>
#include <RFID.h>
#include <PubSubClient.h>

#define button_PIN A0
#define RST_SIM_PIN D3
#define STATUS_WF D8


bool access_allow=false;
int pointer=0;
int menu_screen=false;
bool access_DHT=false;
char IDWF[]="BKHCM_OISP";
char PASSWF[]="bachkhoaquocte";
String uid="";


button _button(button_PIN);
Ticker State;
void check()
{
  _button.update_button(pointer,access_allow, menu_screen,temp, humid, WF_trig,WF_status,MQTT_status, MQTT_trig,MS_trig);
}

void setup() 
{
  Serial.begin(115200);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC52
  Wire.begin(5,4);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  State.attach(0.02, check);
  Display(access_allow, pointer, menu_screen,false, false, false);
}


void loop() {
  uid = RFID_read();
  check_DHT();
  access_WF(IDWF, PASSWF, pointer);
  access_MQTT(pointer);
  send_mess(pointer, MQTT_status,MS_trig);
  if (access_allow == false)
  {
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) return;
    if (uid!="") checkAccess(uid, access_allow);
    Display(access_allow, pointer, menu_screen, false, false,false);
  }
}

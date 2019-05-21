#pragma once
#include <access_MQTT.h>
#include <DHTesp.h>
DHTesp dht;
float temp;
float humid;
char message[6][20] = { "HELLO","WHAT R U DOING","EATEN RICE YET?","TEMPER:    ","HUMID:    " ,"QUIT MESSAGE" };
void change_to_char(char *temp_c, int pointer)
{
	int TEMP;
	(pointer == 3) ? TEMP = temp*100 : TEMP = humid*100;
	for (int i = 0; i < 2; i++)
	{
		char c = TEMP % 10 + 48;
		TEMP = TEMP / 10;
		temp_c[4 - i] = c;
	}
	temp_c[2] = '.';
	for (int i = 0; i < 2; i++)
	{
		char c = TEMP % 10 + 48;
		TEMP = TEMP / 10;
		temp_c[1 - i] = c;
	}
}
void check_DHT()
{
	humid = dht.getHumidity();
	temp = dht.getTemperature();
}
void send_mess( int pointer, bool MQTT_status, bool & MS_trig)
{
	if (MQTT_status==false && MS_trig)
	{
		MS_trig = false;
		delay(1000);
		Display(true, pointer, true, false, false, false);
	}
	else if (MS_trig && MQTT_status){
		MS_trig = false;
		lcd.clear();
		if (pointer == 4 || pointer == 3)
		{
			char temp_c[5] = "";
			char temp[16]="";
			strcpy(temp, message[pointer]);
			change_to_char(temp_c, pointer);
			strcat(temp, temp_c);
			MQTT.publish("From RFID", temp);
			lcd.print("Sent to server");
			lcd.setCursor(0, 1);
			lcd.print(temp);
			delay(2000);
		}
		else {
			MQTT.publish("From RFID", message[pointer]);
			lcd.print("Sent to server");
			lcd.setCursor(0, 1);
			lcd.print(message[pointer]);
			delay(2000);
		}
		Display(true, pointer, true, false, false, false);
	}
	
}

#pragma once

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void Display(bool access_allow, int pointer, int menu_screen, bool access_DHT, bool _WF_status, bool _MQTT_status,float humid = 0, float temp = 0)
{
	if (access_allow == false && access_DHT == false)
	{
		lcd.clear();
		lcd.print(" PLEASE INSERT   ");
		lcd.setCursor(0, 1);
		lcd.print("    YOUR ID               ");
	}
	else if (access_allow == true && access_DHT == false)
	{
		if (menu_screen == 0 )
		{
			switch (pointer)
			{
			case 0:
				lcd.clear();
				lcd.print(">:SEND MESSAGE         ");
				lcd.setCursor(0, 1);
				lcd.print(" :TEMP AND HUMID     ");
				break;
			case 1:
				lcd.clear();
				lcd.print(" :SEND MESSAGE      ");
				lcd.setCursor(0, 1);
				lcd.print(">:TEMP AND HUMID     ");
				break;
			case 2:
				lcd.clear();
				lcd.print(" :TEMP AND HUMID     ");
				lcd.setCursor(0, 1);
				lcd.print(">:CONNECT SV:           ");
				lcd.setCursor(13,1);
				(_MQTT_status == true) ? lcd.print("ON") : lcd.print("OFF");
				break;
			case 3:
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print(" :CONNECT SV:            ");
				lcd.setCursor(13, 0);
				(_MQTT_status == true) ? lcd.print("ON") : lcd.print("OFF");
				lcd.setCursor(0, 1);
				lcd.print(">:CONNECT WF:          ");
				lcd.setCursor(13, 1);
				(_WF_status == true)?  lcd.print("ON") :lcd.print("OFF");
				break;
			case 4:
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.print(" :CONNECT WF:          ");
				lcd.setCursor(0,1);
				lcd.print(">:CONTROL USERS         ");
				lcd.setCursor(13, 0);
				(_WF_status == true) ? lcd.print("ON") : lcd.print("OFF");
				break;
			default:
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print(" :CONTROL USERS           ");
				lcd.setCursor(13, 0);
				lcd.setCursor(0, 1);
				lcd.print(">:QUIT     ");
				break;
			}
		}
		else if (menu_screen == 1)
		{
			switch (pointer)
			{
			case 0:
				lcd.clear();
				lcd.print(">:HELLO         ");
				lcd.setCursor(0, 1);
				lcd.print(" :WHAT R U DOING?     ");
				break;
			case 1:
				lcd.clear();
				lcd.print(" :HELLO      ");
				lcd.setCursor(0, 1);
				lcd.print(">:WHAT R U DOING?      ");
				break;
			case 2:
				lcd.clear();
				lcd.print(" :WHAT R U DOING        ");
				lcd.setCursor(0, 1);
				lcd.print(">:EATEN RICE YET     ");
				break;
			case 3:
				lcd.clear();
				lcd.print(" :EATEN RICE YET        ");
				lcd.setCursor(0, 1);
				lcd.print(">:TEMPERATURE     ");
				break;
			case 4:
				lcd.clear();
				lcd.print(" :TEMPERATURE        ");
				lcd.setCursor(0, 1);
				lcd.print(">:HUMID     ");
				break;
			default:
				lcd.clear();
				lcd.print(" :HUMID       ");
				lcd.setCursor(0, 1);
				lcd.print(">:QUIT MESSAGE    ");
				break;
			}
		}
	}
	else 
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.println("TEMPERATURE: ");
		lcd.setCursor(12, 0);
		lcd.println(temp, 1);
		lcd.setCursor(0, 1);
		lcd.println("HUMID      :        ");
		lcd.setCursor(12, 1);
		lcd.println(humid, 1);
	}
}
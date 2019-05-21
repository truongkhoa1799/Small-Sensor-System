#pragma once
#include <Message.h>
#define NUM_OF_FEATURES 6
#define NUM_OF_MESS 6
//#define NUM_OF_USERS 6
class button
{
private:
	bool state_pointer = false;
	bool state_press = false;
	int button_pointer = LOW;
	int button_press = LOW;
	int pointer=0;
	int A0;
	bool access_DHT=false;
	float humid;
	float temp;
	float MQTT_status;
	float MQTT_trig;
	float WF_status;
	float WF_trig;
	bool MS_trig;
void button_choose()
{
	int button_A0 = analogRead(A0);
	if (button_A0 > 520 && button_A0 < 560 && state_pointer == false)
	{
		button_pointer = HIGH;
		state_pointer = true;
	}
	else if (button_A0 > 740 && button_A0 < 780 && state_press == false)
	{
		button_press = HIGH;
		state_press = true;
	}
	else if ((button_A0 <= 520 || button_A0 >= 560) && state_pointer == true)
		state_pointer = false;
	else if ((button_A0 <= 740 || button_A0 >= 780) && state_press == true)
		state_press = false;
}
void change_state(bool &_access_allow,	int &_menu_screen)
{
	if (_access_allow==true)
	{
		if (button_pointer == HIGH && access_DHT ==false)
		{
			button_pointer = LOW;
			button_press = LOW;
			switch (_menu_screen)
			{
			case 0: pointer = (pointer + 1) % NUM_OF_FEATURES; break;
			case 1: pointer = (pointer + 1) % NUM_OF_MESS; break;
			}
			Display(_access_allow, pointer, _menu_screen,access_DHT,WF_status,MQTT_status, humid, temp);
		}
		if (button_press == HIGH) (_menu_screen==false)? control_menu_screen(_access_allow, _menu_screen):control_message(_access_allow, _menu_screen);
	}
}
void control_message(bool &_access_allow,int &_menu_screen)
{
	if (pointer==5) 
	{
		_menu_screen = 0;
		pointer = 0;
		button_press = LOW;
		button_pointer = LOW;
		Display(_access_allow, pointer, _menu_screen,access_DHT,WF_status,MQTT_status, humid, temp);
	}
	else
	{
		MS_trig = true;
		button_press = LOW;
		button_pointer = LOW;
	}
}

void control_menu_screen(bool &_access_allow, int &_menu_screen)
{
	switch (pointer)
	{
	case 0:
		_menu_screen = 1; pointer = 0;  button_press = LOW; button_pointer = LOW; 
		Display(_access_allow, pointer, _menu_screen, access_DHT, WF_status, MQTT_status, humid, temp); 
		break;
	case 1:
		access_DHT = !access_DHT; button_press = LOW;	button_pointer = LOW; 
		Display(_access_allow, pointer, _menu_screen, access_DHT, WF_status, MQTT_status, humid, temp); 
		break;
	case 2:
		if (WF_status) MQTT_trig = true; button_press = LOW;	button_pointer = LOW; break;
	case 3:
		WF_trig = true;  button_press = LOW; button_press = LOW; button_pointer = LOW; break;
	case 5:
		_access_allow = false; pointer = 0; button_press = LOW; 	button_pointer = LOW; 
		Display(_access_allow, pointer, _menu_screen, access_DHT, WF_status, MQTT_status, humid, temp); 
		break;
	}
}
public:
	button(int _A0)
	{
			A0 = _A0;
	}
	void update_button(int &_pointer, bool &_access_allow,int &_menu_screen, float _temp, float _humid, bool &_WF_trig, bool &_WF_status, bool &_MQTT_status, bool &_MQTT_trig, bool &_MS_trig)
	{
		button_choose();
		MS_trig = _MS_trig;
		MQTT_status = _MQTT_status;
		MQTT_trig = _MQTT_trig;
		WF_status = _WF_status;
		WF_trig = _WF_trig;
		temp = _temp;
		humid = _humid;
		change_state(_access_allow,  _menu_screen);
		_MQTT_status= MQTT_status ;
		_MQTT_trig = MQTT_trig;
		_WF_status = WF_status;
		_WF_trig = WF_trig;
		_MS_trig = MS_trig;
		_pointer = pointer;
	}
};




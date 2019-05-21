#include <ESP8266WiFi.h>
#include <WiFiUdp.h> 
#include <NTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
bool WF_status = false;
bool WF_trig = false;
bool MQTT_status = false;
bool MQTT_trig = false;
bool MS_trig = false;


WiFiClient cli;
void receive_Infor(char*tp, byte * nd, unsigned int length);
PubSubClient MQTT("m16.cloudmqtt.com", 16357, receive_Infor, cli);

void access_WF(char * ID, char *PASS, int pointer)
{
	if (WF_trig == true && WF_status==false)
	{
		WF_trig = false;
		WiFi.begin(ID, PASS);
		lcd.clear();
		int watchDog = 0;
		int count_dot = 0;
		while (WiFi.status() != WL_CONNECTED && watchDog<200)
		{
			lcd.setCursor(0, 0);
			lcd.print("Connecting");
			lcd.setCursor(count_dot,1);
			watchDog++;
			delay(50);
			lcd.print(".");
			count_dot = (count_dot + 1) % 16;
			if (count_dot == 0) lcd.clear();
		}
		if (watchDog != 200)
		{
			WF_status = true;
			lcd.clear();
			lcd.setCursor(4, 0);
			lcd.print("Wifi is     ");
			lcd.setCursor(3, 1);
			lcd.print("connected              ");
			delay(1000);
			Display(true, pointer, false, false, WF_status, MQTT_status); // pointer=2
		}
		else
		{
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Fail to connect     ");
			lcd.setCursor(6, 1);
			lcd.print("WiFi              ");
			delay(2000);
			Display(true, pointer, false, false, WF_status, MQTT_status); // pointer=2
		}
	}
	else if (WF_trig == true && WF_status == true)
	{
		WF_trig = false;
		WiFi.disconnect();
		int count = 0;
		while (WiFi.status() != WL_CONNECTED && count <50)
		{
			count++;
		}
		WF_status = false;
		//MQTT.publish("List Features", "Topic...................................Features");
		Display(true, pointer, false, false, WF_status, MQTT_status);
	}
}

void receive_Infor(char*tp, byte * nd, unsigned int length)
{
	String topic(tp);
	String temp_state = String((char*)nd);
	temp_state.remove(length);
	Serial.print("Topic:");
	Serial.println(tp);
	Serial.print("Message:");
	Serial.println(temp_state);
}

bool check_connect_wf()
{
	int result = (WiFi.status() == WL_CONNECTED) ? true : false;
}

void access_MQTT(int pointer)
{
	if (MQTT_status == false && MQTT_trig == true)
	{
		MQTT_trig = false;
		int watchDog = 0;
		lcd.clear();
		int count_dot = 0;
		while (watchDog<400)
		{
			lcd.setCursor(0,0);
			lcd.print("Connecting");
			lcd.setCursor(count_dot, 1);
			watchDog++;
			delay(50);
			if (!MQTT.connect("Aquatic Tank", "bfglrgpa", "Xu7o8LYQCn4y"))
				lcd.print(".");
			else break;
			count_dot = (count_dot + 1) % 16;
			if (count_dot == 0) lcd.clear();
		}
		if (watchDog != 400)
		{
			MQTT_status = true;
			lcd.clear();
			lcd.setCursor(3, 0);
			lcd.print("Connected     ");
			lcd.setCursor(3, 1);
			lcd.print("to Server              ");
			delay(2000);
			MQTT.publish("Access", "Connected");
			Display(true, pointer, false, false, WF_status, MQTT_status);  //pointer=3
		}
		else
		{
			lcd.clear();
			lcd.setCursor(3, 0);
			lcd.print("Fail to connect     ");
			lcd.setCursor(4, 1);
			lcd.print("Server              ");
			delay(2000);
			Display(true, pointer, false, false, WF_status, MQTT_status);  //pointer=3
		}
	}
	else if ((MQTT_status == true && MQTT_trig == true)||(WF_status==false && MQTT_status==true))
	{
		MQTT.disconnect();
		MQTT_status = false;
		MQTT_trig = false;
		Display(true, pointer, false, false, WF_status, MQTT_status);
	}
}


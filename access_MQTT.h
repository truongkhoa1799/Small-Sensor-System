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
		WF_status = true;
		WiFi.begin(ID, PASS);
		lcd.clear();
		int count_dot = 0;
		while (WiFi.status() != WL_CONNECTED)
		{
			lcd.setCursor(0, 0);
			lcd.print("Connecting");
			lcd.setCursor(count_dot,1);
			delay(50);
			lcd.print(".");
			count_dot = (count_dot + 1) % 16;
			if (count_dot == 0) lcd.clear();
		}
		lcd.clear();
		lcd.setCursor(4,0);
		lcd.print("Wifi is     ");
		lcd.setCursor(3,1);
		lcd.print("connected              ");
		Display(true, pointer, false, false, WF_status, MQTT_status); // pointer=2
	}
	else if (WF_trig == false && WF_status == true)
	{
		MQTT_status = true;
		MQTT_trig = false;
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
		lcd.clear();
		int count_dot = 0;
		MQTT_status = true;
		while (1)
		{
			lcd.setCursor(0,0);
			lcd.print("Connecting");
			lcd.setCursor(count_dot, 1);
			delay(50);
			if (!MQTT.connect("Aquatic Tank", "bfglrgpa", "Xu7o8LYQCn4y"))
				lcd.print(".");
			else break;
			count_dot = (count_dot + 1) % 16;
			if (count_dot == 0) lcd.clear();
		}
		lcd.clear();
		lcd.setCursor(3, 0);
		lcd.print("Connected     ");
		lcd.setCursor(3, 1);
		lcd.print("to Server              ");
		delay(2000);
		MQTT.publish("Access", "Connected");
		Display(true, pointer, false, false, WF_status,MQTT_status);  //pointer=3
	}
	else if (MQTT_status == true && MQTT_trig == false)
	{
		MQTT.disconnect();
		MQTT_status = false;
		Display(true, pointer, false, false, WF_status, MQTT_status);
	}
}


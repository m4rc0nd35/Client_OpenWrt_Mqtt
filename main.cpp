#define MQTTCLIENT_QOS2 1
#include <memory.h>
#include "MQTTClient.h"
#include <Countdown.h>
#include <PubSubClient.h>
#include <Telemetry.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>

using namespace std;

void callbackMsg(MQTT::MessageData &md)
{
	MQTT::Message &message = md.message;

	char payload[255];
	string text;
	strcpy(payload, (char *)message.payload );
	
	for (int i = 0; (int)message.payloadlen > i; i++)
		text.push_back(payload[i]);
	cout << "Text: "<< text << endl;
}

int main(int argc, char *argv[])
{
	while (true)
	{
		try
		{
			bool connected = true;
			/* code */
			Telemetry *tele = new Telemetry();
			cout << tele->mac() << endl;
			cout << tele->wifi() << endl;

			PubSubClient connSocket = PubSubClient();
			const char *topic = "/open/cmd";
			const char *topic_pub = "/open/telemetry";
			// vector<string> lista = tele->split("adsf;qwret;nvfkbdsj;orthdfjgh;dfjrleih", ";");
			// for (auto i : lista)
			// 	cout << i << endl;

			MQTT::Client<PubSubClient, Countdown> client = MQTT::Client<PubSubClient, Countdown>(connSocket);

			const char *hostname = "mqtt.vejame.com.br";
			int port = 1883;
			printf("Connecting to %s:%d\n", hostname, port);
			int rc = connSocket.connect(hostname, port);
			if (rc != 0)
				connected = false;

			if (connected)
			{
				MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
				data.MQTTVersion = 3;
				data.clientID.cstring = (char *)"OpenWrt";
				data.username.cstring = (char *)"openwrt";
				data.password.cstring = (char *)"321654";
				printf("MQTT connecting\n");
				rc = client.connect(data);
				if (rc != 0)
					connected = false;
				else
				{
					printf("MQTT connected\n");

					rc = client.subscribe(topic, MQTT::QOS0, callbackMsg);
					if (rc != 0)
						connected = false;

					MQTT::Message message;

					// QoS 0
					while (connected)
					{
						char buf[500];
						sprintf(buf, "%s", tele->wifi().c_str());
						message.qos = MQTT::QOS2;
						message.retained = false;
						message.dup = false;
						message.payload = (void *)buf;
						message.payloadlen = strlen(buf) + 1;
						rc = client.publish(topic_pub, message);
						if (rc != 0)
							connected = false;

						client.yield(5000);
					}

					rc = client.unsubscribe(topic);
					if (rc != 0)
						printf("rc from unsubscribe was %d\n", rc);
				}
			}

			connSocket.disconnect();
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
		usleep(5 * 1000000);
	}
	return 0;
}
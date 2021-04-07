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

int main(int argc, char *argv[])
{
	while (true)
	{
		try
		{
			bool connected = true;
			/* code */
			Telemetry *tele = new Telemetry();
			string mac = tele->mac().c_str();
			PubSubClient connSocket = PubSubClient();
			char *topic_cmd;
			const char *topic_cmd_all = "/all/cmd";
			const char *topic_pub = "/telemetry";
			sprintf(topic_cmd, "/%s/cmd", (char*)mac.c_str());
			// vector<string> lista = tele->split("adsf;qwret;nvfkbdsj;orthdfjgh;dfjrleih", ";");
			// for (auto i : lista)
			// 	cout << i << endl;

			MQTT::Client<PubSubClient, Countdown> client = MQTT::Client<PubSubClient, Countdown>(connSocket);

			const char *hostname = "mqtt.vejame.com.br";
			int port = 1883;
			printf("Connecting to %s:%d...\n", hostname, port);
			int rc = connSocket.connect(hostname, port);
			if (rc != 0)
				connected = false;

			if (connected)
			{
				MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
				data.MQTTVersion = 3;
				data.clientID.cstring = (char *)mac.c_str();
				data.username.cstring = (char *)"radios";
				data.password.cstring = (char *)"projecttrampolimdavitoria";
				printf("MQTT connecting %s...\n", mac.c_str());
				rc = client.connect(data);
				if (rc != 0)
					connected = false;
				else
				{
					printf("MQTT connected!\n");

					rc = client.subscribe(topic_cmd, MQTT::QOS0, Telemetry::callbackCmdMac);
					if (rc != 0)
						connected = false;
						
					rc = client.subscribe(topic_cmd_all, MQTT::QOS0, Telemetry::callbackCmdAll);
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

						client.yield(30000);
					}

					rc = client.unsubscribe(topic_cmd);
					if (rc != 0)
						printf("rc from unsubscribe was %d\n", rc);
				}
			}

			connSocket.disconnect();
		}
		catch (const std::exception &e){
			std::cerr << e.what() << '\n';
		}
		
		usleep(5 * 1000000);
	}
	return 0;
}
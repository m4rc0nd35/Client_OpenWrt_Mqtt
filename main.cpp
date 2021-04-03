#define MQTTCLIENT_QOS2 1
#include <memory.h>
#include "MQTTClient.h"
#include "IPStack.cpp"
#include "Telemetry.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void callbackMsg(MQTT::MessageData &md)
{
	MQTT::Message &message = md.message;

	int payloadlen = (int) message.payloadlen;
	char payload[payloadlen];
	strcpy(payload, (char*)message.payload);
	cout << "Length: " <<  payloadlen << " Payload:" << payload << endl;
}

int main(int argc, char *argv[])
{
	try
	{
		Telemetry *tele = new Telemetry();
		cout << tele->serial_number() << endl;

		IPStack ipstack = IPStack();
		const char *topic = "/open/cmd";
		const char *topic_pub = "/open/telemetry";
		cout << "SERIA NUMBER:" << topic << endl;
		vector<string> lista = tele->split("adsf;qwret;nvfkbdsj;orthdfjgh;dfjrleih", ";");
		for (auto i : lista)
			cout << i << endl;
			
		MQTT::Client<IPStack, Countdown> client = MQTT::Client<IPStack, Countdown>(ipstack);

		const char *hostname = "mqtt.vejame.com.br";
		int port = 1883;
		printf("Connecting to %s:%d\n", hostname, port);
		int rc = ipstack.connect(hostname, port);
		if (rc != 0)
			printf("rc from TCP connect is %d\n", rc);

		printf("MQTT connecting\n");
		MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
		data.MQTTVersion = 3;
		data.clientID.cstring = (char *)"OpenWrt";
		data.username.cstring = (char *)"openwrt";
		data.password.cstring = (char *)"321654";
		rc = client.connect(data);
		if (rc != 0)
			printf("rc from MQTT connect is %d\n", rc);
		printf("MQTT connected\n");

		rc = client.subscribe(topic, MQTT::QOS2, callbackMsg);
		if (rc != 0)
			printf("rc from MQTT subscribe is %d\n", rc);

		MQTT::Message message;

		// QoS 0
		while (true)
		{
			char buf[100];
			sprintf(buf, "%s", "teste");
			// sprintf(buf, "%s", tele->exec("date").c_str());
			message.qos = MQTT::QOS2;
			message.retained = false;
			message.dup = false;
			message.payload = (void *)buf;
			message.payloadlen = strlen(buf) + 1;
			rc = client.publish(topic_pub, message);
			if (rc != 0)
				printf("Error %d from sending QoS 0 message\n", rc);

			client.yield(5000);
		}

		rc = client.unsubscribe(topic);
		if (rc != 0)
			printf("rc from unsubscribe was %d\n", rc);

		rc = client.disconnect();
		if (rc != 0)
			printf("rc from disconnect was %d\n", rc);

		ipstack.disconnect();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}

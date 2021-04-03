g++ main.cpp \
-I ./libs/ \
-I ./headers/ \
./Telemetry.cpp \
./libs/MQTTPacket.c \
./libs/MQTTDeserializePublish.c \
./libs/MQTTConnectClient.c \
./libs/MQTTSubscribeClient.c \
./libs/MQTTSerializePublish.c \
./libs/MQTTUnsubscribeClient.c \
-o telemetry && \
./telemetry
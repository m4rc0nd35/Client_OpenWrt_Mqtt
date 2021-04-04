g++ main.cpp \
-I ./libs/ \
-I ./src/ \
./src/PubSubClient.cpp \
./src/Countdown.cpp \
./src/Telemetry.cpp \
./libs/MQTTPacket.c \
./libs/MQTTDeserializePublish.c \
./libs/MQTTConnectClient.c \
./libs/MQTTSubscribeClient.c \
./libs/MQTTSerializePublish.c \
./libs/MQTTUnsubscribeClient.c \
-o telemetry && \
./telemetry
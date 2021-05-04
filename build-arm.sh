export STAGING_DIR=./ && \
/home/m4rc0nd35/toolchain-C60-V3/bin/mips-openwrt-linux-g++ main.cpp \
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
-o telemetry -Wall && \
scp telemetry root@192.168.1.56:/root/

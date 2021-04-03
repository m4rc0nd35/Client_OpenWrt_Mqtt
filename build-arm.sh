export STAGING_DIR=./ && \
/home/m4rc0nd35/toolchain-aarch64_cortex-a53_gcc-7.5.0_musl/bin/aarch64-openwrt-linux-g++ main.cpp \
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
scp telemetry root@192.168.1.13:/root/
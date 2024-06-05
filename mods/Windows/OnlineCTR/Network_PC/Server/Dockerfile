FROM ubuntu:24.04

ENV TZ=Asia/Kuwait \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake libenet-dev libtool autoconf build-essential

RUN mkdir -p /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN mkdir -p /root/CTR-ModSDK/externals/enet
RUN mkdir -p /root/CTR-ModSDK/decompile


COPY . /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
COPY enet /root/CTR-ModSDK/externals/enet/
COPY decompile /root/CTR-ModSDK/decompile

WORKDIR /root/CTR-ModSDK/externals/enet/
RUN autoreconf -vfi && chmod +x ./configure && ./configure && make && make install

WORKDIR /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN cmake CMakeLists.txt && make

EXPOSE 8080

ENTRYPOINT ["/root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/entrypoint.sh"]

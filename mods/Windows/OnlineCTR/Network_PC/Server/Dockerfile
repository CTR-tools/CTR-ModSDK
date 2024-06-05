FROM ubuntu:24.04

ENV TZ=Asia/Kuwait \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake make gcc libenet-dev libtool autoconf automake build-essential

RUN mkdir -p /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN mkdir -p /root/CTR-ModSDK/externals/enet
RUN mkdir -p /root/CTR-ModSDK/decompile


COPY . /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
COPY enet /root/CTR-ModSDK/externals/enet/
COPY decompile /root/CTR-ModSDK/decompile


RUN cd /root/CTR-ModSDK/externals/enet/ && autoreconf -vfi
RUN chmod +x /root/CTR-ModSDK/externals/enet/configure
RUN cd /root/CTR-ModSDK/externals/enet/ && ./configure
RUN cd /root/CTR-ModSDK/externals/enet/ && cmake CMakeLists.txt
RUN cd /root/CTR-ModSDK/externals/enet/ && make
RUN cd /root/CTR-ModSDK/externals/enet/ && make install

RUN cd /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN cd /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/ && cmake CMakeLists.txt
RUN cd /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/ && make


EXPOSE 8080

ENTRYPOINT ["/root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/entrypoint.sh"]
FROM ubuntu:24.04 AS builder

ENV TZ=Asia/Kuwait \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake libenet-dev libtool autoconf build-essential

RUN mkdir -p /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN mkdir -p /root/CTR-ModSDK/externals/enet
RUN mkdir -p /root/CTR-ModSDK/decompile


COPY mods/Windows/OnlineCTR/Network_PC/Server /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server
COPY externals/enet /root/CTR-ModSDK/externals/enet/
COPY decompile /root/CTR-ModSDK/decompile

WORKDIR /root/CTR-ModSDK/externals/enet/
RUN autoreconf -vfi && chmod +x ./configure && ./configure && make && make install

WORKDIR /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN cmake CMakeLists.txt && make

FROM ubuntu:24.04 AS final

RUN apt-get update && apt-get install -y libenet-dev
RUN mkdir -p /app
WORKDIR /app
COPY --from=builder /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/ctr_srv /app/

ENV PORT 42069

EXPOSE ${PORT}

ENTRYPOINT /app/ctr_srv -p ${PORT}

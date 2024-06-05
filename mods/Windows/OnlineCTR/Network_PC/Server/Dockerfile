FROM i386/debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y cmake libenet-dev libtool autoconf build-essential

RUN mkdir -p /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN mkdir -p /root/CTR-ModSDK/externals/enet
RUN mkdir -p /root/CTR-ModSDK/decompile


COPY mods/Windows/OnlineCTR/Network_PC/Server /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server
COPY decompile /root/CTR-ModSDK/decompile

WORKDIR /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN cmake CMakeLists.txt && make

FROM i386/debian:bookworm-slim AS final

RUN mkdir -p /app
WORKDIR /app
COPY --from=builder /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/ctr_srv /app/
COPY --from=builder /usr/lib/i386-linux-gnu/libenet.* /usr/lib/i386-linux-gnu/

ENV PORT 64001

EXPOSE ${PORT}/udp

ENTRYPOINT /app/ctr_srv -p ${PORT}
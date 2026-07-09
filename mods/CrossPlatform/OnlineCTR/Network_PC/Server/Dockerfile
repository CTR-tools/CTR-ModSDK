FROM i386/debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y cmake libenet-dev libtool autoconf build-essential

COPY mods/Windows/OnlineCTR/Network_PC/Server /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server
COPY decompile /root/CTR-ModSDK/decompile

WORKDIR /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/
RUN cmake CMakeLists.txt && make

FROM scratch AS final

WORKDIR /app

COPY --from=builder /root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/ctr_srv /app/
COPY --from=builder /lib/i386-linux-gnu/libenet.so.7 /lib/i386-linux-gnu/
COPY --from=builder /lib/i386-linux-gnu/libc.so.6 /lib/i386-linux-gnu/
COPY --from=builder /lib/ld-linux.so.2 /lib/

# Ports are hard-coded; image is from scratch so no /bin/sh to interpret env variables
EXPOSE 64001/udp
ENTRYPOINT ["/app/ctr_srv", "-p", "64001"]

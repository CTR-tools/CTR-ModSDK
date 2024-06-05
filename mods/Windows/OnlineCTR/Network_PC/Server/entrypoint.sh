#!/usr/bin/env bash

PORT=${PORT:-8080}

/root/CTR-ModSDK/mods/Windows/OnlineCTR/Network_PC/Server/ctr_srv <<EOF
$PORT
EOF

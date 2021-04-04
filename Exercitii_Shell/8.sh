#!/usr/bin/bash

df -BM | sed -E "s/%//gi" | sed -E "s/M//g" | awk '($5 > 80) || ($3 < 10000000) {print $6}' | tail -n +2


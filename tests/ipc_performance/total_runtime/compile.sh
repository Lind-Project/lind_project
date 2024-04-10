#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/write16var.c -o scripts/write16var -lpthread -O3
gcc scripts/read16var.c -o scripts/read16var -lpthread -O3
gcc scripts/write32var.c -o scripts/write32var -lpthread -O3
gcc scripts/read32var.c -o scripts/read32var -lpthread -O3

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/write16var.c -o scripts/write16var.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/read16var.c -o scripts/read16var.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/write32var.c -o scripts/write32var.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/read32var.c -o scripts/read32var.nexe -std=gnu99 -lpthread -O3

echo "Compiling user test binaries"
cargo build --release --manifest-path=scripts/userpipe/Cargo.toml
cp scripts/userpipe/target/release/userpipe scripts/userpipetest

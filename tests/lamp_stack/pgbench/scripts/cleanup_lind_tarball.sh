#!/bin/bash
CWD=$PWD
echo -e "Resetting lind fs"
rm -rf lind/
cd "$CWD"

echo -e "Loading lind"
cp -r backup_lindfs/ lind/

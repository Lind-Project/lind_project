#!/bin/bash
CWD=$PWD
echo -e "Resetting lind fs"
cd lind/lindenv/fs
rm -rf *
cd "$CWD"

echo -e "Loading lind"
cp -r backup_lindfs/lindenv/fs/* lind/lindenv/fs/

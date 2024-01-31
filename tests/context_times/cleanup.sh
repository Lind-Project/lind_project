#!/bin/bash

echo -e "Cleaning up"
rm scripts/*.nexe
rm -f $(find . -type f ! -name "*.*")

#!/bin/bash

let size=2**$1
let size2=2**$2
dd if=test1gb.txt bs=$size | dd of=testcopy.txt bs=$size2

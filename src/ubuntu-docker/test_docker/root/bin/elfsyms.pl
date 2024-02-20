#!/bin/perl

use strict;
use warnings;

print join(" ",
	map { s|\s+| |gr; }
	join(" ",
	map { s|^.*\sT\s*(.*)$|$1\(| && $_ if /\bT\s[^_]/m; }
	map { split /\n/, `nm -D $_`; }
	keys %{{map { $_ => 1; }
	map { s|^.*$|/lib/lib$&.so|r; } @ARGV}})) . "\n";

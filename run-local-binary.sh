#!/bin/sh

# Run a binary using local libraries (the ones in the lib/ directory).
# Without this script, the system cannot find these dynamic libraries.
export LD_LIBRARY_PATH=lib
$1 $2 $3 $4 $5 $6 $7 $8 $9

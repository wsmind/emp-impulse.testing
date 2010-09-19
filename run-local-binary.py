#!/usr/bin/python

import os
import sys
import subprocess

if os.name == "nt":
	os.environ["PATH"] = "lib;lib\\thirdparty;" + os.environ["PATH"]
else:
	os.environ["LD_LIBRARY_PATH"] = "lib"

process = subprocess.Popen(sys.argv[1:])
sys.exit(process.wait())


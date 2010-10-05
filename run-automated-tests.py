import os
import sys
import subprocess
import threading
import glob
import time
import re
import json

# Allow human (not JSON) output
human = False
if len(sys.argv) > 1:
	if sys.argv[1] == "-h":
		human = True

# Process killer with timeout
class KillerThread(threading.Thread):
	def __init__(self, process, timeout):
		threading.Thread.__init__(self)
		self.process = process
		self.timeout = timeout
		self.daemon = True
	
	def run(self):
		time.sleep(self.timeout)
		if process.poll() is None:
			process.kill()

# Automated test executables
if os.name == "nt":
	files = "bin\\test\\auto-*.exe"
else:
	files = "bin/test/auto-*"

# Output structures
tests = {}
summary = {}

# Summary initialization
summary["pass"] = 0
summary["fail"] = 0
summary["total"] = 0
summary["crashes"] = 0

for testBinary in glob.glob(files):
	process = subprocess.Popen(["python", "run-local-binary.py", testBinary], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	killer = KillerThread(process, 5)
	killer.start()
	out = process.communicate()[0]
	
	# output analysis
	test = {}
	test["returncode"] = process.returncode
	test["output"] = out
	test["pass"] = 0
	test["fail"] = 0
	test["total"] = 0
	for line in out.splitlines():
		#print line
		if re.match(r"^\[OK\]", line) is not None:
			test["pass"] = test["pass"] + 1
			test["total"] = test["total"] + 1
		if re.match(r"^\[FAILED\]", line) is not None:
			test["fail"] = test["fail"] + 1
			test["total"] = test["total"] + 1
	
	# data for this test
	tests[testBinary] = test
	
	# aggregation
	summary["pass"] = summary["pass"] + test["pass"]
	summary["fail"] = summary["fail"] + test["fail"]
	summary["total"] = summary["total"] + test["total"]
	if process.returncode != 0:
		summary["crashes"] = summary["crashes"] + 1

if human:
	# Human output
	for name in tests:
		test = tests[name]
		print
		print "== %s (%d/%d) ==" % (name, test["pass"], test["total"])
		if int(test["returncode"]) != 0:
			print "--> CRASHED <--"
		print test["output"]
	
	print "== SUMMARY =="
	print "Passed:", summary["pass"]
	print "Failed:", summary["fail"]
	print "Total:", summary["total"]
	print "Crashes:", summary["crashes"]
else:
	# JSON output
	jsOutput = {}
	jsOutput["tests"] = tests
	jsOutput["summary"] = summary
	print json.dumps(jsOutput)


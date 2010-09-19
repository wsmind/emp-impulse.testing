################################################################################
#                                                                              #
# This file is part of the EMP Impulse project                                 #
#                                                                              #
# Copyright (C) 2010 ElectroMagnetic Potatoes (EMP)                            #
# See the AUTHORS file for more information.                                   #
#                                                                              #
# This program is free software: you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation, either version 3 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.        #
#                                                                              #
################################################################################

import os
import build

################################################################
# Default options (will be overriden by command line switches) #
################################################################

# Parallel build
SetOption('num_jobs', 4)

# include cache
SetOption('implicit_cache', 1)

##########################################################
# Command-line parameters (overriden by localconfig.py) #
##########################################################

buildVariables = Variables("localconfig.py")
buildVariables.Add(BoolVariable("DEBUG", "If true, build in debug configuration", False))
buildVariables.Add(BoolVariable("FORCE_MINGW", "When both MinGW and VC++ are installed, force the use of the MinGW compiler instead of the default (windows only)", False))
buildVariables.Add(BoolVariable("DISABLE_GRAPH", "Disable dependency graph generation", False))

##############################################################################
# Variable value extraction (nasty, should be updated when the API evolves)  #
# The reason for having this here is that we have to access variables before #
# we can create the real construction environment (for tools selection)      #
##############################################################################

currentVariables = Environment(variables = buildVariables).Dictionary()

####################
# Base environment #
####################

baseTools = []
if os.name == "nt":
	if currentVariables["FORCE_MINGW"]:
		baseTools.append("mingw")
	else:
		baseTools.append("default")
else:
	baseTools.append("default")

baseEnvironment = Environment(tools = baseTools, variables = buildVariables)

# additional variables
baseEnvironment["OSNAME"] = os.name
baseEnvironment["SYSPATH"] = os.environ["PATH"].split(os.pathsep)

if baseEnvironment["CC"] == "cl":
	baseEnvironment.AppendUnique(CPPFLAGS = ["/EHsc"])

# warning level
if baseEnvironment["CC"] == "cl":
	baseEnvironment.AppendUnique(CPPFLAGS = ["/W2"])
	baseEnvironment.AppendUnique(CPPFLAGS = ["/wd4251"])
else:
	baseEnvironment.AppendUnique(CPPFLAGS = ["-Wall"])

# debug symbols vs. optimization
if baseEnvironment["DEBUG"]:
	if baseEnvironment["CC"] == "cl":
		baseEnvironment.AppendUnique(CPPFLAGS = ["/Z7"])
	else:
		baseEnvironment.AppendUnique(CPPFLAGS = ["-g"])
else:
	if baseEnvironment["CC"] == "cl":
		baseEnvironment.AppendUnique(CPPFLAGS = ["/Ox"])
	else:
		baseEnvironment.AppendUnique(CPPFLAGS = ["-O2"])

# Under windows, add the platform SDK
if os.name == "nt" and baseEnvironment["CC"] == "cl":
	import _winreg
	key = _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows")
	winSdkHome = _winreg.QueryValueEx(key, "CurrentInstallFolder")[0]
	_winreg.CloseKey(key)
	baseEnvironment["WINSDK_HOME"] = winSdkHome
	baseEnvironment.AppendUnique(CPPPATH = ["$WINSDK_HOME/Include"])
	baseEnvironment.AppendUnique(LIBPATH = ["$WINSDK_HOME/Lib"])

# Do not rely on VC++ runtime library
if os.name == "nt" and baseEnvironment["CC"] == "cl":
	baseEnvironment.AppendUnique(CPPFLAGS = ["/MD"])

# Speed up change analysis
baseEnvironment.Decider('MD5-timestamp')

#####################
# Command-line help #
#####################

Help(buildVariables.GenerateHelpText(baseEnvironment))

##################################
# SCons environment declarations #
##################################

walker = build.DependencyWalker()

# external component database
for script in baseEnvironment.Glob("components.*.py"):
	baseEnvironment.SConscript(script, exports = "walker", variant_dir = "build", src_dir = ".", duplicate = 0)


walker.makeEnvironments(baseEnvironment)
if not baseEnvironment["DISABLE_GRAPH"]:
	walker.makeDependencyGraph("dependencies.png")

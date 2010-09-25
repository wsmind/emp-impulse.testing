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

import build
# do not import other things here; if you need something, add it to the
# environment in the SConstruct file

# dependency walker
Import("walker")

# utility function
# TODO: make a scons builder, when we got time
def PrepackageExternalDll(dllName, env):
	"""Look for the given Dll in the $LIBPATH variable, and copy it to
	lib/thirdparty if found. If the file is not found, a warning is
	printed. This function does nothing on other OSes than windows."""
	
	if env["OSNAME"] == "nt":
		# search for the dll to copy
		dllFile = env.FindFile(dllName, env["LIBPATH"])
		if dllFile != None:
			env.Command("lib/thirdparty/" + dllName, dllFile, Copy("$TARGET", "$SOURCE"))
		else:
			print "WARNING: unable to prepackage the file '%s', it will be missing from the lib/thirdparty directory" % (dllName)

class impulse_dependency_pack(build.Component):
	"""Virtual component pointing to the downloaded dependency pack"""
	
	def __init__(self):
		build.Component.__init__(self, "impulse-dependency-pack")
	
	def appendUsage(self, env):
		if env["OSNAME"] == "nt":
			if "DEPENDENCY_PACK_HOME" not in env:
				print "You must specify a dependency pack location under windows !"
				env.Exit(1)
			
			if env["CC"] == "gcc":
				compiler = "mingw"
			else:
				compiler = "vc2008"
			
			env.AppendUnique(CPPPATH = ["$DEPENDENCY_PACK_HOME/include"])
			env.AppendUnique(LIBPATH = ["$DEPENDENCY_PACK_HOME/lib/" + compiler])

walker.declareComponent(impulse_dependency_pack())

class boost_integer(build.Component):
	"""boost::integer"""
	
	def __init__(self):
		build.Component.__init__(self, "boost-integer", ["impulse-dependency-pack"])

walker.declareComponent(boost_integer())

class sfml(build.Component):
	"""boost::integer"""
	
	def __init__(self):
		build.Component.__init__(self, "sfml", ["impulse-dependency-pack"])
	
	def appendArtifacts(self, env):
		if env["OSNAME"] == "nt":
			PrepackageExternalDll("sfml-system.dll", env)
			PrepackageExternalDll("sfml-window.dll", env)
			PrepackageExternalDll("sfml-graphics.dll", env)
			PrepackageExternalDll("sfml-audio.dll", env)
			PrepackageExternalDll("libsndfile-1.dll", env)
			PrepackageExternalDll("openal32.dll.dll", env)
	
	def appendUsage(self, env):
		env.AppendUnique(LIBS = ["sfml-system", "sfml-window", "sfml-graphics", "sfml-audio"])

walker.declareComponent(sfml())


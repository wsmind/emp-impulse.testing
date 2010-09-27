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

class impulse_common(build.Component):
	"""Virtual component with basic Impulse environment"""
	
	def __init__(self):
		build.Component.__init__(self, "impulse-common", ["boost-integer"])
	
	def appendUsage(self, env):
		env.AppendUnique(CPPPATH = ["build/include"])
		env.AppendUnique(LIBPATH = ["lib"])

walker.declareComponent(impulse_common())

class impulse_math(build.Component):
	"""Math package"""
	
	def __init__(self):
		build.Component.__init__(self, "impulse-math", ["impulse-common"])
	
	def appendArtifacts(self, env):
		env.AppendUnique(CPPDEFINES = ["BUILDING_IMPULSE_MATH"])
		env.SharedLibrary("lib/impulse-math", env.Glob("build/src/math/*.cpp"))
	
	def appendUsage(self, env):
		env.AppendUnique(LIBS = ["impulse-math"])

walker.declareComponent(impulse_math())

class impulse_engine(build.Component):
	"""Low-level engine"""
	
	def __init__(self):
		build.Component.__init__(self, "impulse-engine", ["impulse-math", "sfml"])
	
	def appendArtifacts(self, env):
		env.AppendUnique(CPPDEFINES = ["BUILDING_IMPULSE_ENGINE"])
		env.SharedLibrary("lib/impulse-engine", env.Glob("build/src/engine/*.cpp"))
	
	def appendUsage(self, env):
		env.AppendUnique(LIBS = ["impulse-engine"])

walker.declareComponent(impulse_engine())


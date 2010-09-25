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


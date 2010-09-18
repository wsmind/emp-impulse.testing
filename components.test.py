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

class peel(build.Component):
	"""Problem Elusive Examination Library (PEEL, lightweight test library)"""
	
	def __init__(self):
		build.Component.__init__(self, "peel")
	
	def appendUsage(self, env):
		env.AppendUnique(CPPPATH = ["build/test/peel"])

walker.declareComponent(peel())

class peel_example(build.Component):
	"""PEEL example"""
	
	def __init__(self):
		build.Component.__init__(self, "peel-example", ["peel"])
	
	def appendArtifacts(self, env):
		env.Program("bin/test/peel-example", "build/test/peel/example.cpp")

walker.declareComponent(peel_example())


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

class test_examples(build.Component):
	"""Simple automated and non-automated test examples"""
	
	def __init__(self):
		build.Component.__init__(self, "test-examples", ["peel"])
	
	def appendArtifacts(self, env):
		env.Program("bin/test/auto-examples-mouse", "build/test/examples/auto-mouse.cpp")
		env.Program("bin/test/examples-cheese", "build/test/examples/cheese.cpp")

walker.declareComponent(test_examples())

class test_sfml(build.Component):
	"""Tests of SFML environment setup"""
	
	def __init__(self):
		build.Component.__init__(self, "test-sfml", ["peel", "sfml"])
	
	def appendArtifacts(self, env):
		env.Program("bin/test/sfml-basic", "build/test/sfml/basic.cpp")

walker.declareComponent(test_sfml())

class test_lua(build.Component):
	"""Tests of Lua environment setup"""
	
	def __init__(self):
		build.Component.__init__(self, "test-lua", ["peel", "lua"])
	
	def appendArtifacts(self, env):
		env.Program("bin/test/auto-lua-basic", "build/test/lua/auto-basic.cpp")

walker.declareComponent(test_lua())

class test_math(build.Component):
	"""Tests for the math package"""
	
	def __init__(self):
		build.Component.__init__(self, "test-math", ["peel", "impulse-math"])
	
	def appendArtifacts(self, env):
		env.Program("bin/test/auto-math-random", "build/test/math/auto-random.cpp")
		env.Program("bin/test/auto-math-vec2", "build/test/math/auto-vec2.cpp")
		env.Program("bin/test/auto-math-mat33", "build/test/math/auto-mat33.cpp")

walker.declareComponent(test_math())


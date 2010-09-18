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

class Component:
	"""The coarse-grained compilation unit. A component declares dependencies to
	other components and a set of artifacts to build, parametered by platform and
	config"""
	
	# Constructor
	def __init__(self, name, deps = []):
		"""The provided name is used by other components in order
		to reference this one. The optional argument is the list of component
		names this one depends on."""
		self.name = name
		self.deps = deps
	
	# How to build this component
	def appendArtifacts(self, env):
		"""The role of this method is to detail how the component artifacts are to
		be built. Note that dependencies will be added automatically to the
		environment, using the list given in the constructor. Thus, this
		method must only declare internal environment (e.g component-specific
		#define), but NEVER append other component's include paths or similar
		external settings.
		
		Every artifact must be appended to the given SCons environment."""
		pass
	
	# How to use this component
	def appendUsage(self, env):
		"""This method will be called when another component is using this one.
		The given SCons environment must be appended with whatever is necessary
		to use this component. For instance, a typical implementation would
		add include and library paths."""
		pass

class DependencyWalker:
	def __init__(self):
		self.components = {}
	
	def declareComponent(self, component):
		self.components[component.name] = component
	
	def findAllDependencies(self, component, deps):
		for dependency in component.deps:
			if not dependency in self.components:
				print "Warning: component '%s' depends on '%s', which has not been declared" % (component.name, dependency)
			else:
				if not dependency in deps:
					deps.append(dependency)
					self.findAllDependencies(self.components[dependency], deps)
	
	def makeEnvironments(self, baseEnvironment):
		for name, component in self.components.items():
			# start with a fresh SCons environment for each component
			env = baseEnvironment.Clone()
			
			# append dependencies
			dependencies = []
			self.findAllDependencies(component, dependencies)
			for dependency in dependencies:
				self.components[dependency].appendUsage(env)
			
			# declare this component artifacts
			component.appendArtifacts(env)
	
	def makeDependencyGraph(self, filename):
		# generate graphviz file
		f = open(filename + ".tmp.graphviz", "wt")
		
		f.write("digraph G {\n")
		
		# add all components
		for component in self.components.values():
			f.write("\"" + component.name + "\"\n")
			
			for dependency in component.deps:
				f.write("\"" + component.name + "\" -> \"" + dependency + "\"\n")
		
		f.write("}\n")
		
		f.close()
		
		# (try to) generate the graph
		os.system("dot -Tpng -o %s < %s.tmp.graphviz" % (filename, filename))
		os.remove("%s.tmp.graphviz" % (filename))

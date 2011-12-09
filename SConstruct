import os
env = Environment(
                CXX='clang++',
                CXXFLAGS='-std=c++0x ',
                LINKFLAGS='-L./lib',
                tools=['default','scons_qt4', 'gch'])
                
# Print compiler flags
cons_vars = env.Dictionary().keys()
#for v in sorted(cons_vars):
#        print v, env[str(v)]
#print env["LIBSUFFIXES"]
              
env.EnableQt4Modules([
        'QtGui',
        'QtCore',
        'QtOpenGL'])
        
Export('env')

SConscript('src/SConscript', variant_dir='build', duplicate=1)
buildtest = SConscript('srctest/SConscript', variant_dir='buildtest', duplicate=1)

def PhonyTarget(target, action):
	phony = Environment(ENV = os.environ,
						BUILDERS = {"phony" : Builder(action = action)})
	AlwaysBuild(phony.phony(target = target, source = 'SConstruct'))

PhonyTarget('run', 'build/Delaunay')
PhonyTarget('test', 'buildtest/Test')

						
import os

env = Environment(
	ENV     = os.environ,
	CPPPATH = [ '.' ],
	tools   = [ 'mingw', 'gcc' ]
)

if (env['CC'] == 'gcc') :
	env.Append(CCFLAGS = '-g -O0 -ansi -w -pipe')

main = env.Object(target = 'main', source = [ 'test.cxx' ])

env.Program(target = 'ArbInt', source = [ main ])
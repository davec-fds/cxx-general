# General info.
project_name        = open('config/NAME'       , 'r').read()
project_description = open('config/DESCRIPTION', 'r').read()
project_url         = open('config/URL'        , 'r').read()
project_version_maj = open('config/VER_MAJOR'  , 'r').read()
project_version_min = open('config/VER_MINOR'  , 'r').read()
project_version_pat = open('config/VER_PATCH'  , 'r').read()

# Version of the library.
cxxgeneral_maj_version = open('config/LIB_VER_MAJOR', 'r').read()
cxxgeneral_min_version = open('config/LIB_VER_MINOR', 'r').read()

# Imports.
import os

# Symlink builder. Am I missing something? Why do I have to do this?
def symlink_builder_func (target, source, env) :
  
  # Delete old symlink.
  try :
    os.unlink(target)
  except : pass
  
  # Make new symlink.
  os.symlink(str(source), str(target))
  
  # Always successful.
  return 0

# Pkg-config builder.
def pkgconfig_builder_func (target, source, env) :
  
  # Create the .pc file.
  #try :
  
  sfile = open(str(source[0]), 'r').readlines()
  tfile = open(str(target[0]), 'w')
  
  for line in sfile :
    if (line == "NAME\n") :
      tfile.write('Name: ' + project_name + "\n")
    elif (line == "DESCRIPTION\n") :
      tfile.write('Description: ' + project_description + "\n")
    elif (line == "URL\n") :
      tfile.write('URL: ' + project_url + "\n")
    elif (line == "VERSION\n") :
      tfile.write('Version: ' + project_version_maj + '.' + project_version_min + '.' + project_version_pat + "\n")
    elif (line == "LIBS\n") :
      tfile.write('Libs: -l' + project_name + "\n")
    elif (line == "CFLAGS\n") :
      tfile.write('Cflags: -I' + includedir + "\n")
  
  tfile.close()
  
  #except :
  #  return 1
  
  # Successful.
  return 0

# String for the symlink builder.
def symlink_builder_desc (target, source, env) :
  return "Symlink: %s -> %s" % (str(target[0]), str(source[0]))

# String for the pkg-config builder.
def pkgconfig_builder_desc (target, source, env) :
  return "pkg-config %s" % (str(target[0]))

# Create options.
opts = Options('custom.py')
opts.AddOptions(
  BoolOption('DEBUG',  'Set for a debug build.' , default = 0),
  PathOption('PREFIX', 'Prefix to install into.', default = '/usr', validator = PathOption.PathIsDir)
)

# Create the environment.
env = Environment(
  options    = opts,
  ENV        = os.environ,
  CPPPATH    = ['.']
)

# Install the builders.
symlink_builder   = Builder(action = Action(symlink_builder_func  , symlink_builder_desc  ))
pkgconfig_builder = Builder(action = Action(pkgconfig_builder_func, pkgconfig_builder_desc), suffix = '.pc', src_suffix = '.pc.src')
env.Append(BUILDERS = {'Symlink'   : symlink_builder  })
env.Append(BUILDERS = {'PkgConfig' : pkgconfig_builder})

# Generate help text.
Help(opts.GenerateHelpText(env))

# Set compiler options.
if env['CC'] == 'gcc' :
  env.Append(CCFLAGS    = '-g -O0 -ansi -pedantic-errors -Wall -Wextra -Wshadow -Wpointer-arith -Wredundant-decls -Wunreachable-code -Winline -Werror -pipe')
  env.Append(CPPDEFINES = 'CC_GCC')
if env['CC'] == 'cl' :
  env.Append(CCFLAGS    = '/GR /EHsc /Od /Wp64 /Za')
  env.Append(CPPDEFINES = 'CC_CL')

# Make a backup of env so SConscript files do not modify it.
tmpenv = env.Copy()

# Install locations.
includedir   = env['PREFIX'] + '/include/cxx-general'
libdir       = env['PREFIX'] + '/lib'
pkgconfigdir = libdir + '/pkgconfig'

# Headers.
headers = []
h_AutoArray        = env.File('AutoArray.h++'       ) ; headers += [h_AutoArray       ]
h_Exception        = env.File('Exception.h++'       ) ; headers += [h_Exception       ]
h_ReferencePointer = env.File('ReferencePointer.h++') ; headers += [h_ReferencePointer]
h_SafeInt          = env.File('SafeInt.h++'         ) ; headers += [h_SafeInt         ]
h_abs              = env.File('abs.h++'             ) ; headers += [h_abs             ]
h_demangle         = env.File('demangle.h++'        ) ; headers += [h_demangle        ]
h_gcd              = env.File('gcd.h++'             ) ; headers += [h_gcd             ]
h_lcm              = env.File('lcm.h++'             ) ; headers += [h_lcm             ]
h_logBase          = env.File('logBase.h++'         ) ; headers += [h_logBase         ]
h_reduce           = env.File('reduce.h++'          ) ; headers += [h_reduce          ]
h_rppower          = env.File('rppower.h++'         ) ; headers += [h_rppower         ]
h_toString         = env.File('toString.h++'        ) ; headers += [h_toString        ]
h_getErrorText     = env.File('getErrorText.h++'    ) ; headers += [h_getErrorText    ]

# Modules.
modules = []
cArbInt    = SConscript(['ArbInt/SConscript'   ], exports = 'env'                ) ; env = tmpenv.Copy() ; modules.append(cArbInt   )
cArb       = SConscript(['Arb/SConscript'      ], exports = 'env cArbInt'        ) ; env = tmpenv.Copy() ; modules.append(cArb      )
cTimestamp = SConscript(['Timestamp/SConscript'], exports = 'env cArb'           ) ; env = tmpenv.Copy() ; modules.append(cTimestamp)
cPOSIXFile = SConscript(['POSIXFile/SConscript'], exports = 'env'                ) ; env = tmpenv.Copy() ; modules.append(cPOSIXFile)
cwrapText  = SConscript(['wrapText/SConscript' ], exports = 'env'                ) ; env = tmpenv.Copy() ; modules.append(cwrapText )
cGetOpt    = SConscript(['GetOpt/SConscript'   ], exports = 'env cwrapText cArb' ) ; env = tmpenv.Copy() ; modules.append(cGetOpt   )
cINIFile   = SConscript(['INIFile/SConscript'  ], exports = 'env cPOSIXFile'     ) ; env = tmpenv.Copy() ; modules.append(cINIFile  )
cSyslog    = SConscript(['Syslog/SConscript'   ], exports = 'env'                ) ; env = tmpenv.Copy() ; modules.append(cSyslog   )

# Tests.
SConscript(['Tests/SConscript'], exports = 'env cArbInt cArb cTimestamp cPOSIXFile cGetOpt cINIFile cSyslog') ; env = tmpenv.Copy()

# Shared library filenames.
cxxgeneral_name   = env['LIBPREFIX'] + project_name + env['SHLIBSUFFIX']
cxxgeneral_soname = cxxgeneral_name   + '.' + cxxgeneral_maj_version
cxxgeneral_rname  = cxxgeneral_soname + '.' + cxxgeneral_min_version

# Create the shared library.
cxxgeneral_objs = []
for module in modules :
  for obj in module['own_sobj'] :
    cxxgeneral_objs += obj
cxxgeneral = env.SharedLibrary(target = cxxgeneral_rname, SHLIBSUFFIX = '', source = cxxgeneral_objs, SHLINKFLAGS = '-Wl,-soname,' + cxxgeneral_soname + env['SHLINKFLAGS'])

# Create the pkg-config file.
pcfile = env.PkgConfig(target = project_name, source = project_name)

# Install files.
install = []
install.append(env.Install(includedir, headers))
for module in modules :
  install.append(env.Install(includedir, module['own_headers']))
install.append(env.Install(libdir                        , cxxgeneral))
install.append(env.Symlink(libdir + '/' + cxxgeneral_name, cxxgeneral))
install.append(env.Install(pkgconfigdir, pcfile))

# Install alias.
env.Alias('install', install)

# Build the library by default.
if env.GetOption('clean') :
  env.Default('.')
else :
  env.Default(cxxgeneral)

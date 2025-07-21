project('coreuseless', 'c')

inc = include_directories('include')

sources = files('src/cat.c', 'src/cp.c', 'src/echo.c', 'src/false.c', 'src/ln.c', 'src/ls.c', 'src/mkdir.c', 'src/mv.c', 'src/pwd.c', 'src/rm.c', 'src/sleep.c', 'src/touch.c', 'src/true.c', 'src/yes.c')

foreach source : sources
  thing = source.full_path().split('/')
  executable(thing.get(thing.length()-1).replace('.c',''), source, 'src/utils.c', install: true, include_directories: inc)
endforeach

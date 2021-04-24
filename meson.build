project('N','cpp')
src = ['src/main.cc', 'src/shader.cc', 'src/texture.cc', 'src/text.cc', 'src/util.cc', 'src/system.cc']
epoxy = dependency('epoxy')
SDL2 = dependency('SDL2')
executable('gl',src, dependencies: [epoxy, SDL2])

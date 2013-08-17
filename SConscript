Import('env')

name = 'phylopp'
inc = env.Dir('.')
ext_inc = []
src = env.Glob('src/*.cpp')
deps = ['mili']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)

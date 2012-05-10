Import ('env')

name = 'phylopp'
inc = env.Dir('.')
ext_inc = env.Dir('phylopp')
src = env.Glob('src/*.cpp')
deps = ['mili']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)

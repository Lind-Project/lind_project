from distutils.core import setup, Extension
setup(name='lindpipe', version='1.0',  \
        ext_modules=[Extension('lindpipe', ['pypipe-lfq.c', 'lfq.c'], extra_compile_args=['-ltcmalloc_minimal -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free'], extra_link_args=['-lstdc++'], extra_objects=['libtcmalloc_minimal.a'], )])

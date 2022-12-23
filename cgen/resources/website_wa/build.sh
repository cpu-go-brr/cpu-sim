emcc wa/src/* -I wa/include/ -o js/cpu.js -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']" -s ALLOW_MEMORY_GROWTH=1 -fsanitize=address

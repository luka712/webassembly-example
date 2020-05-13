* First emsdk needs to be activated (make sure that emscripten is downloaded, follow instructions from emscripten page)
 go to emsdk folder 
 run : ./emsdk activate
       ./emsdk_env.bat

 theh with same shell navigate to this folder 
 and run

// for jskey 
emcc jskey.c -o jskey.html -s NO_EXIT_RUNTIME=1 --shell-file jskey_shell.html -s EXPORTED_FUNCTIONS="['_main','_press_up','_press_down','_press_left','_press_right','_release_down','_release_up','_release_right','_release_left']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap','ccall']" -s USE_SDL=2
emrun jskey.html

// for keyboard.html
emcc keyboard.c -o keyboard.html -s USE_SDL=2
emrun keyboard.html
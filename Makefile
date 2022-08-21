all:
	clang++ *.cpp glad.c dependencies/libraries/libglfw.3.3.dylib --std=c++20 -Idependencies/include -Ldependencies/libraries -Wall -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated -o "app"


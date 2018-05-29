LIBS=-lGL -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
HEADERS=  include/shaderprogram.h include/objloader.hpp include/texture.hpp
FILES= main_file.cpp include/shaderprogram.cpp include/objloader.cpp include/texture.cpp

main_file:  $(FILES) $(HEADERS)
	g++ -o main_file  $(FILES)  $(LIBS) -I.

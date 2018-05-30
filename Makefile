LIBS=-lGL -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
HEADERS=  include/shaderprogram.h include/objloader.hpp include/texture.hpp init.hpp gra.hpp plansza.hpp obiekt.hpp worms.hpp
FILES= main_file.cpp gra.cpp plansza.cpp include/shaderprogram.cpp include/objloader.cpp include/texture.cpp obiekt.cpp worms.cpp

main_file:  $(FILES) $(HEADERS)
	g++ -o main_file  $(FILES)  $(LIBS) -I.

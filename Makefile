all: compile link 

compile:
	# g++ -c video.cpp -I"C:\Users\Ibrahim\Downloads\SFML-2.6.2\include" -DSFML_STATIC#
	g++ -c video.cpp -I"C:\Users\Ibrahim\Downloads\SFML-2.6.2\include"

link:
	# g++ video.o -o video -L"C:\Users\Ibrahim\Downloads\SFML-2.6.2\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
	# ./video
	g++ video.o -o video -L"C:\Users\Ibrahim\Downloads\SFML-2.6.2\lib" -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system                           
	./video
clean:
	rm -f video *.o

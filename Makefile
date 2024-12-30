all: compile link

compile:
	g++ -c main.cpp -I"C:\Studies\1st Semester\Programming Fundamentals\SFML-3.0.0\include" -DSFML_STATIC -std=c++17


link:
	g++ main.o -o main -L"C:\Studies\1st Semester\Programming Fundamentals\SFML-3.0.0\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
	g++ main.o -o main -L"C:\Studies\1st Semester\Programming Fundamentals\SFML-3.0.0\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lstdc++fs

clean:
	rm -f main *.o
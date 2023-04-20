all: add_nbo

add_nbo: add_nbo.cpp
	g++ -o add_nbo add_nbo.c

clean:
	rm -f add_nbo


CC = gcc
CFLAGS = -O3 -flto -Wall $(shell pkg-config --cflags --libs libglfw) -std=gnu99

mac: 
	$(CC) $(CFLAGS) -Wl,-framework,OpenGL *.c -o gravitysim 

linux:
	$(CC) $(CFLAGS) -lm -lGL *.c -o gravitysim 

clean:
	rm -f *.o
#gcc *.c -o gravsim -lm -lglfw -lGL -lpthread -std=gnu99 -O3
#gcc *.c -o gravsim -lglfw -Wl,-framework,OpenGL -lpthread -std=gnu99 -O3

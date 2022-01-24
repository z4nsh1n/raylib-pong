LIBS := `pkg-config --libs raylib`

all:
	gcc $(LIBS) main.c

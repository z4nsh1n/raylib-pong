LIBS := `pkg-config --libs raylib`

all:
	gcc $(LIBS) main.c

watch:
	@inotifywait -m -e moved_to . | while read events; do clear; make all;done
	@echo test

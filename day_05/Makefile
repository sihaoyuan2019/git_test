CC = gcc  
MAINC = 01_gtk_thread.c
EXEC = demo 

CFLAGS = `pkg-config --cflags --libs gtk+-2.0 gmodule-export-2.0`
main:  
	$(CC)  $(MAINC)  -o $(EXEC) $(CFLAGS)  -lgthread-2.0
clean:
	rm $(EXEC) -rf
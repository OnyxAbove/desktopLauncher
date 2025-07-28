CC = gcc
CFLAGS = -Wall -g
TARGET = dl
SRC = desktopLauncher.c

all: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(pkg-config --cflags --libs glib-2.0) $(SRC)

install: $(TARGET)
	install -d ~/.local/bin/
	install -m 755 $(TARGET) ~/.local/bin/$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f ~/.local/bin/$(TARGET)

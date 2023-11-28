CC = g++
CFLAGS = -I include -O3 --std=c++17

OUT_OBJ = app

BUILD = build
SOURCES = $(wildcard src/*.cpp)

$(OUT_OBJ):
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD)/$@

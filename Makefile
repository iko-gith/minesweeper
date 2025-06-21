CCC     = gcc
CFLAGS = -Wall -Wextra -I./lib -I./input
SRCS   = main.c src/board/board.c src/game/game.c src/output/output.c src/plr_input/plr_input.c src/render/render.c
OUT    = game

.PHONY: all run clean

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = ddg_game

SRC = \
	MAIN_DDG.c \
	LIB_DDG.c \
	LIB_first_page.c \
	LIB_stage.c \
	for_ddg.c \
	for_worm.c \
	stage1.c \
	stage2.c \
	stage3.c \
	LIB_c_worm.c \
	LIB_shot.c \
	for_flower.c \
	LIB_hud.c

OBJ = $(SRC:.c=.o)

ALLEGRO_CFLAGS = $(shell pkg-config --cflags allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5)
ALLEGRO_LIBS = $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5)


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(ALLEGRO_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(ALLEGRO_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all
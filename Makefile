CC=cc
ENGINE_PATH=./src/
ENGINE_FILES=vector.c matrix.c vertex.c sprite.c body.c scene.c camera.c radix_sort.c renderer.c
ENGINE_SRC=$(addprefix $(ENGINE_PATH),$(ENGINE_FILES))
GAME_PATH=./game_src/
GAME_FILES=main.c
GAME_SRC=$(addprefix $(GAME_PATH),$(GAME_FILES))
CC_INCLUDE_FLAGS=$(addprefix -I,$(ENGINE_PATH) $(GAME_PATH))
RAYLIB_FLAGS=`pkg-config --libs --cflags raylib`
BUILD_PATH=./build/

game:
	$(CC) $(CC_INCLUDE_FLAGS) -o $(BUILD_PATH)$@ $(ENGINE_SRC) $(GAME_SRC) $(RAYLIB_FLAGS)

clean:
	rm -f ./build/game

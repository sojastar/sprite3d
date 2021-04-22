CC=cc
DEBUG_FLAG=-g
OPTIMIZATION_FLAG=-O2
ENGINE_PATH=./src/
ENGINE_FILES=vector.c matrix.c vertex.c sprite.c body.c scene.c camera.c counting_sort.c radix_sort.c merge_sort.c renderer.c
ENGINE_SRC=$(addprefix $(ENGINE_PATH),$(ENGINE_FILES))
EXAMPLE_PATH=./example/
EXAMPLE_FILES=main.c
EXAMPLE_SRC=$(addprefix $(EXAMPLE_PATH),$(EXAMPLE_FILES))
CC_INCLUDE_FLAGS=$(addprefix -I,$(ENGINE_PATH) $(GAME_PATH))
RAYLIB_FLAGS=`pkg-config --libs --cflags raylib`
BUILD_PATH=./build/

game:
	$(CC) $(CC_INCLUDE_FLAGS) -o $(BUILD_PATH)$@ $(ENGINE_SRC) $(EXAMPLE_SRC) $(RAYLIB_FLAGS)

clean:
	rm -f ./build/game

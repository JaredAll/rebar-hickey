CXX = clang++
SDL_INCLUDE = -I/usr/include/SDL2
INC_INCLUDE = -Isrc -Isrc/engine -Isrc/text -Isrc/io -Isrc/engine/input -Isrc/engine/utility
CXX_FLAGS = -Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++17 -g $(SDL_INCLUDE) $(INC_INCLUDE)
LINKER_FLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread
OBJ_DIR = build
BIN_DIR = bin
OBJ_FILES = $(addprefix $(OBJ_DIR)/, \
engine.o \
hickey_renderer.o \
easy_sdl.o \
input_event.o \
input_handler.o \
main.o \
glyph.o \
glyph_node.o \
glyph_data.o \
glyph_alphabet.o \
hickey.o\
hickey_highlights.o\
selected_highlight.o\
selected_editor_node.o\
gap_buffer.o\
cursor.o\
buffer_insert_action.o\
buffer_remove_action.o\
buffer_cursor_action.o\
buffer_executor.o\
io_action_factory.o\
io_executor.o\
hickey_action_factory.o\
buffer_action_factory.o)

VPATH = src:src/engine:src/engine/input:src/engine/utility:src/text:src/io

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/rebar-hickey cscope

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BIN_DIR)/rebar-hickey: $(OBJ_FILES)
	$(CXX) $(LINKER_FLAGS) -o $@ $(OBJ_FILES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/

$(BIN_DIR):
	mkdir -p $(BIN_DIR)/

.PHONY: clean

clean:
	-rm -rf $(OBJ_DIR) && rm -rf $(BIN_DIR)

.DELETE_ON_ERROR:

cscope:
	cd ~/rebar-hickey && find . -name "*.hpp" > cscope.files && \
	find . -name "*.cpp" >> cscope.files && cscope -b -q -k -R

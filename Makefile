ifeq ($(OS),Windows_NT)
  RM = del /Q /F
  RMDIR = rmdir /Q /S
  EXT = .exe
	RUN =
else
  RM = rm -f
  RMDIR = rm -rf
	RUN = ./
  EXT =
endif

CC=@gcc
BEAR=@bear
DEBUG_FLAGS =
DEBUG_SRC = debug_src/no_debug.c
SRC=$(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ=$(patsubst %.c,build/%.o,$(notdir $(SRC))) build/debug.o
INCLUDE=include/
EXEC=cry$(EXT)

ifeq ($(filter debug,$(MAKECMDGOALS)),debug)
  DEBUG_FLAGS = -g
  DEBUG_SRC = debug_src/debug.c
endif

all: $(EXEC)
debug: clean $(EXEC)

space:=$(subst ,, )
comma:=,
$(EXEC): $(OBJ)
	@echo "Linking $(subst $(space),$(comma)$(space),$(strip $^)) to $@"
	$(CC) $^ -o $@

VPATH = src:$(wildcard src/*/)

build/%.o: %.c | build/
	@echo "Compiling: $<"
	$(CC) -c $< -I $(INCLUDE) -o $@ $(DEBUG_FLAGS)

build/debug.o: $(DEBUG_SRC) | build/
	@echo "Compiling configuration: $<"
	$(CC) $(DEBUG_FLAGS) -c $< -I $(INCLUDE) -o $@

build/:
ifeq ($(OS),Windows_NT)
	@if not exist build mkdir build
else
	@mkdir -p build
endif

clean:
	@echo "Cleaning up...."
	@$(RMDIR) build/
	@$(RM) $(EXEC)
	@echo "Done."

run: $(EXEC)
	@$(RUN)$(EXEC)

ifneq ($(OS),Windows_NT)
compile_commands: clean
	@if ! command -v bear >/dev/null 2>&1; then \
		echo "Error: '$(BEAR)' is not installed! install it first first."; \
		exit 1; \
	fi
	@echo "Generating compile_commands.json..."
	$(BEAR) -- $(MAKE) all
	@echo "Done."
else
	@echo "Error: '$(BEAR)' is not available to windows"
endif

PHONY: all clean run compile_commands debug

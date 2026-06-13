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
SRC=$(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ=$(patsubst %.c,build/%.o,$(notdir $(SRC)))
INCLUDE=include/
EXEC=cry$(EXT)

all: $(EXEC)
debug: DEBUG_MODE=-g
debug: clean all

space:=$(subst ,, )
comma:=,
$(EXEC): $(OBJ)
	@echo "Linking $(subst $(space),$(comma)$(space),$(strip $^)) to $@"
	$(CC) $^ -o $@

VPATH = src:$(wildcard src/*/)

build/%.o: %.c | build/
	@echo "Compiling: $<"
	$(CC) -c $< -I $(INCLUDE) -o $@ $(DEBUG_MODE)

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

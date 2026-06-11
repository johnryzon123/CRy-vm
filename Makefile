CC=@gcc
SRC=$(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ=$(patsubst %.c,build/%.o,$(notdir $(SRC)))
INCLUDE=include/
EXEC=cry

all: $(EXEC)

space:=$(subst ,, )
comma:=,
$(EXEC): $(OBJ)
	@echo "Linking $(subst $(space),$(comma)$(space),$(strip $^)) to $@"
	$(CC) $^ -o $@

VPATH = src:$(wildcard src/*/)

build/%.o: %.c | build/
	@echo "Compiling: $<"
	$(CC) -c $< -I $(INCLUDE) -o $@

build/:
	@mkdir -p build

clean:
	@echo "Cleaning up...."
	@rm -rf build/
	@rm cry
	@echo "Done."

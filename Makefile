# === Generic Makefile Template ===

# Dynamic name: username + date + version
NAME = $(shell whoami)-$(shell date +"%Y_%m_%d_%H%M%S")-v0_a

CC = clang
CFLAGS = -Wall -Werror -Wextra
SRCDIR = src
OBJDIR = tmp
BUILDDIR = target

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
INC = -I ../

# Default target
all: setup $(BUILDDIR)/$(NAME)

# Link all object files into a single executable
$(BUILDDIR)/$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@
	@echo "Linked binary -> $@"

# Compile each source file into an object
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(INC) $(CFLAGS)
	@echo "Compiled $< -> $@"

# Ensure build directories exist
setup:
	mkdir -p $(BUILDDIR) $(OBJDIR)

# Clean object files
clean:
	rm -rf $(OBJDIR)
	@echo "Cleaned object files."

# Clean everything (objects + final binary)
fclean: clean
	rm -rf $(BUILDDIR)
	@echo "Removed build directory."

# Rebuild from scratch
re: fclean all

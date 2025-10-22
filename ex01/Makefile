CC       = clang
INC_DIR  = .
SRC_DIR  = .
# TEST_DIR = ./.test
OBJ_DIR  = ./target
# TEST_OBJD= $(OBJ_DIR)/test
NAME     = phonebook
# NTEST    = phonebook_test

SRCS     = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/PhoneBook.cpp \
	$(SRC_DIR)/Contact.cpp \

OBJS     = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
# TESTOBJS = $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJD)/%.o,$(TESTS)) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/main.c,$(SRCS)))

CFLAGS       = -Wall -Wextra -Werror -g3 -I$(INC_DIR) -std=c++98 -pipe -MMD -MP
FSAN_CFLAGS  = -Wall -Wextra -Werror -g3 -I$(INC_DIR) -std=c++98 -pipe -fsanitize=address -fsanitize=leak -MMD -MP
LDFLAGS      = -g3 -std=c++98 -pipe -lstdc++
FSAN_LDFLAGS = -g3 -std=c++98 -pipe -lstdc++ -fsanitize=address -fsanitize=leak

# Compiler preference: clang > gcc for main binary
ifeq ($(shell which clang),)
  CC = gcc
endif

# If mold is installed, use it as the linker
ifneq ($(shell which mold),)
	LDFLAGS += -fuse-ld=mold
endif

all: $(NAME)

# Fsanitize-compatible build (no AddressSanitizer)
fsanitize: CFLAGS = $(FSAN_CFLAGS)
fsanitize: LDFLAGS = $(FSAN_LDFLAGS)
fsanitize: fclean $(NAME)

$(NAME): $(OBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $(OBJS)"
	@$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp  $(_LIB_FT)
# Create the parent directory of the object file if it doesn't exist
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(NTEST)

re: fclean
	@$(MAKE) all -j$(shell nproc) CC=$(CC)
	@echo "$(NAME) recompiled successfully."

$(HOME)/.local/bin/trunk:
	@echo "Installing trunk..."
	@mkdir -p $(HOME)/.local/bin
	@curl -L https://trunk.io/releases/trunk -o $(HOME)/.local/bin/trunk
	@chmod +x $(HOME)/.local/bin/trunk
	@echo "Trunk installed successfully."
	@echo "Installing trunk tools..."
	@$(HOME)/.local/bin/trunk install
	@echo "Trunk tools installed successfully."

check: $(HOME)/.local/bin/trunk
	@echo "Running trunk check..."
	@$(HOME)/.local/bin/trunk check --all
	@echo "Trunk check completed."

format: $(HOME)/.local/bin/trunk
	@echo "Running trunk format..."
	@$(HOME)/.local/bin/trunk fmt --all
	@echo "Trunk format completed."

.PHONY: all clean fclean re check format
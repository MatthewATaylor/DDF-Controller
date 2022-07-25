TARGET := ddf

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:%=$(BUILD_DIR)/%.o)
DEP_FILES := $(OBJ_FILES:.o=.d)

INC_FLAG := $(addprefix -I,$(INCLUDE_DIR))
LDLIBS=-lm
CFLAGS=$(INC_FLAG) -MMD -MP -Wall -Wextra -Werror -ansi -pedantic

.PHONY: clean

$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDLIBS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

-include $(DEP_FILES)


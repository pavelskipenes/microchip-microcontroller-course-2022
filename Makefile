NAME_EXECUTABLE = program

BUILD_DIR = build/
SOURCE_DIR = src/
HEADERS_DIR = headers/
USER = $(shell id -un)

INCLUDE_DIR = $(SOURCE_DIR)$(HEADERS_DIR)
DEVICE_SUPPORT = device_support/
C_FLAGS = -O1 -g -Wall -Wextra -Werror -I $(INCLUDE_DIR) -I $(DEVICE_SUPPORT)include -D__AVR_ATmega4809__ -DF_CPU=3333333UL -mmcu=atmega4809 -B $(DEVICE_SUPPORT)gcc/dev/atmega4809
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJCOPY_FLAGS = -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures

SRC_FILES := $(foreach sdir,$(SOURCE_DIR),$(wildcard $(sdir)*.c))
OBJ_FILES = $(subst $(SOURCE_DIR),$(BUILD_DIR),$(SRC_FILES:.c=.o))
HEADER_FILES = $(foreach sdir,$(SOURCE_DIR)$(HEADERS_DIR),$(wildcard $(sdir)*.h))

QUITE = @
.DEFAULT_GOAL = flash


# Generate flashable binary
build: $(BUILD_DIR)$(NAME_EXECUTABLE).hex
.PHONY: build
$(BUILD_DIR)$(NAME_EXECUTABLE).hex: $(OBJ_FILES) | $(BUILD_DIR)
	$(QUITE) $(CC) $(C_FLAGS) $(OBJ_FILES) -o $(BUILD_DIR)$(NAME_EXECUTABLE).elf
	$(QUITE) $(OBJCOPY) $(OBJCOPY_FLAGS) $(BUILD_DIR)$(NAME_EXECUTABLE).elf $(BUILD_DIR)$(NAME_EXECUTABLE).hex

# generic object file generation
$(BUILD_DIR)%.o : $(SOURCE_DIR)%.c | $(BUILD_DIR)
	$(QUITE) $(CC) $< $(C_FLAGS) -c -o $@

# Create build directory
$(BUILD_DIR):
	$(QUITE) mkdir -p $(BUILD_DIR)


.PHONY: flash
flash: $(BUILD_DIR)$(NAME_EXECUTABLE).hex
	$(QUITE) mv $(BUILD_DIR)$(NAME_EXECUTABLE).hex /run/media/$(USER)/CURIOSITY/$(NAME_EXECUTABLE).hex

.PHONY: clean
clean:
	$(QUITE) rm -rf $(BUILD_DIR)

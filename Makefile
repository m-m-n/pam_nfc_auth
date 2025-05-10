CC = gcc
CFLAGS = -fPIC -Wall -Wextra
LDFLAGS = -shared -lpam

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/pam_nfc_auth.so
SRC = $(SRC_DIR)/pam_nfc_auth.c
NFC_READER = /usr/local/bin/nfc-reader
INSTALL_DIR = /usr/lib/x86_64-linux-gnu/security

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

check-nfc-reader:
	@if [ ! -x "$(NFC_READER)" ]; then \
		echo "Error: $(NFC_READER) not found or not executable"; \
		echo "Please install nfc-reader first"; \
		exit 1; \
	fi

install: check-nfc-reader $(TARGET)
	install -m 644 $(TARGET) $(INSTALL_DIR)/

clean:
	rm -rf $(BUILD_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(notdir $(TARGET))

.PHONY: all clean install uninstall check-nfc-reader

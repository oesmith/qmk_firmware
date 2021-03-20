BOOTLOADER = atmel-dfu

OLED_DRIVER_ENABLE= yes
WPM_ENABLE = yes

SRC +=  ./lib/layer_state_reader.c \
        ./lib/keylogger.c \
				./keymaps/ollysmith/bongocat.c

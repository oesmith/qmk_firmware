BOOTLOADER = atmel-dfu

OLED_DRIVER_ENABLE= yes
RGBLIGHT_ENABLE = yes
WPM_ENABLE = yes

SRC +=  ./lib/logo_reader.c \
        ./keymaps/ollysmith/bongocat.c

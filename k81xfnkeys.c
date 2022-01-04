#include <stdio.h>
#include <string.h>
#include <hidapi.h>

#define LOGITECH_VENDOR 0x046d
#define PRODUCT_K810 0xb319
#define PRODUCT_K811 0xb317

const unsigned char fn_keys_on[]  = {0x10, 0xff, 0x06, 0x15, 0x00, 0x00, 0x00};
const unsigned char fn_keys_off[] = {0x10, 0xff, 0x06, 0x15, 0x01, 0x00, 0x00};

#define MAX_STR 255

int main(int argc, char *argv[])
{
    int res;
    wchar_t wstr[MAX_STR];
    hid_device *handle;

    int on = -1;

    if (argc > 1) {
	if (!strcmp(argv[1], "off")) {
	    on = 0;
	} else if (!strcmp(argv[1], "on")) {
	    on = 1;
	}
    }

    if (argc < 2 || on < 0) {
	fprintf(stderr, "Usage: %s on|off\n", argv[0]);
	return 0;
    }

    res = hid_init();

    handle = hid_open(LOGITECH_VENDOR, PRODUCT_K810, NULL);
    if (!handle) {
	handle = hid_open(LOGITECH_VENDOR, PRODUCT_K811, NULL);
    }

    if (handle) {
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	if (res > 0) {
	    printf("%ls ", wstr);
	}

	res = hid_get_product_string(handle, wstr, MAX_STR);
	printf("%ls ", wstr);

	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	printf("(%ls)", wstr);

	res = hid_write(handle, on ? fn_keys_on : fn_keys_off, 7);
	if (res != 7) {
	    fprintf(stderr, "\nError write to keyboard!\n");
	} else {
	    printf(": FN keys are %s\n", on ? "enabled" : "disabled");
	}

	hid_close(handle);
    } else {
	fprintf(stderr, "Logitech K810 or K811 keyboard not found!\n");
    }

    res = hid_exit();

    return 0;
}

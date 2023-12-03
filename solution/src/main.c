#include "../include/bmp.h"
#include "../include/file.h"
#include "../include/rotate.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE* input = open(argv[1], "rb");
    FILE* output = open(argv[2], "wb");
    int angle = atoi(argv[3]);
    struct image* img = malloc(sizeof(struct image));
    if (!input || !output) {
        fprintf(stderr, "Error with opening files");
        return 1;
    }
    if (img == NULL) {
        fprintf(stderr, "Error with allocating memory");
        return 1;
    }

    if (from_bmp(input, img) != READ_OK) {
        fprintf(stderr, "Error with reading image");
        return 1;
    }

    struct image rotated_image = rotate(img, angle);

    if (rotated_image.data == NULL) {
        fprintf(stderr, "Image did not transform");
        return 1;
    }

    if (to_bmp(output, &rotated_image) != WRITE_OK) {
        fprintf(stderr, "Error with writing image");
        return 1;
    }
    return 0;
}

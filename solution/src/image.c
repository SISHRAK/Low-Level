#include "../include/image.h"
#include <stdint.h>
#include <stdlib.h>

struct image create_image(const size_t width, const size_t height) {
    struct pixel* pixels = calloc(width * height, sizeof(struct pixel));
    if (pixels == NULL){
        struct image im = {0};
        return im;
    } else {
        struct image ret_im;
        ret_im.height = height;
        ret_im.width = width;
        ret_im.data = pixels;
        return ret_im;
    }
}




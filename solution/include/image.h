#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include <stdint.h>



struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct pixel {
    uint8_t b, g, r;
};

struct image create_image(size_t width, size_t height);



#endif

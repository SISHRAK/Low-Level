#include "../include/rotate.h"
#include "../include/image.h"
void rotate90(struct image const *oldImage, struct image *newImage) {
    for (size_t i = 0; i < newImage->height; i++) {
        for (size_t j = 0; j < newImage->width; j++) {
            newImage->data[i * newImage->width + j] = oldImage->data[(j + 1) * oldImage->width - i - 1];
        }
    }
}

void rotate180(struct image const *oldImage, struct image *newImage) {
    for (size_t i = 0; i < newImage->height; i++) {
        for (size_t j = 0; j < newImage->width; j++) {
            newImage->data[oldImage->height * oldImage->width - i * oldImage->width - j - 1] = oldImage->data[
                    i * oldImage->width + j];
        }
    }
}

void rotate270(struct image const *oldImage, struct image *newImage) {
    for (size_t i = 0; i < newImage->width; i++) {
        for (size_t j = 0; j < newImage->height; j++) {
            newImage->data[(j + 1) * newImage->width - i - 1] = oldImage->data[i * oldImage->width + j];
        }
    }
}

struct image rotate(struct image *source, int angle) {
    struct image rotated_image1 = create_image(source->height, source->width);
    struct image rotated_image2 = create_image(source->width, source->height);
    if (angle == 90 || angle == -270) {
        if (rotated_image1.data)
            rotate90(source, &rotated_image1);
        return rotated_image1;
    } else if (angle == 180 || angle == -180) {
        if (rotated_image2.data)
            rotate180(source, &rotated_image2);
        return rotated_image2;
    } else if (angle == 270 || angle == -90) {
        if (rotated_image1.data)
            rotate270(source, &rotated_image1);
        return rotated_image1;
    } else {
        for (size_t i = 0; i < source->width * source->height; i++) {
            rotated_image2.data[i] = source->data[i];
        }
        return rotated_image2;
    }
}

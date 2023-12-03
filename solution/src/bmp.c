

#include "../include/bmp.h"
#include "../include/file.h"
#include "../include/defines.h"

#include <string.h>
#define BMP_HEADER_SIZE sizeof(struct bmp_header)
#define PIXEL_SIZE sizeof(struct pixel)

struct bmp_header create_bmp_header(struct image const *img) {
    struct bmp_header header;
    uint32_t size = img->height * (img->width * STRUCT_SIZE + get_padding(img->width));
    header.bfType = BMP_TYPE;
    header.bfileSize = size + BMP_STRUCT_SIZE;
    header.bfReserved = ZERO;
    header.bOffBits = BMP_STRUCT_SIZE;
    header.biSize = BMP_SIZE;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = BMP_PLANES;
    header.biBitCount = BIT_COUNT;
    header.biCompression = ZERO;
    header.biSizeImage = size;
    header.biXPelsPerMeter = PELS_PER_METER;
    header.biYPelsPerMeter = PELS_PER_METER;
    header.biClrUsed = ZERO;
    header.biClrImportant = ZERO;
    return header;
}

enum read_status read_header(FILE *bmp_file, struct bmp_header *header) {
    if (!bmp_file || !header) {
        return READ_ERROR;
    }
    if (!fread(header, BMP_HEADER_SIZE, 1, bmp_file)) {
        return READ_ERROR;
    }
    return READ_OK;
}

enum read_status read_pixels(FILE *bmp_file, struct image *img) {
    if (!bmp_file || !img || !img->data) {
        return READ_ERROR;
    }
    for (size_t row = 0; row < img->height; row++) {
        if (!fread(img->data + row * img->width, PIXEL_SIZE, img->width, bmp_file)) {
            return READ_ERROR;
        }
        size_t padding = get_padding(img->width);
        if (fseek(bmp_file, padding, SEEK_CUR)) {
            return READ_ERROR;
        }
    }
    return READ_OK;
}

enum read_status from_bmp(FILE *bmp_file, struct image *img) {
    struct bmp_header bmp_header;
    enum read_status header_status = read_header(bmp_file, &bmp_header);
    if (header_status != READ_OK) {
        return header_status;
    }
    *img = create_image(bmp_header.biWidth, bmp_header.biHeight);
    enum read_status pixels_status = read_pixels(bmp_file, img);
    if (pixels_status != READ_OK) {
        return pixels_status;
    }
    return READ_OK;
}



enum write_status write_header(FILE *bmp_file, struct image const *img) {
    if (!bmp_file || !img) {
        return WRITE_ERROR;
    }
    struct bmp_header bmp_header = create_bmp_header(img);
    if (!fwrite(&bmp_header, BMP_HEADER_SIZE, 1, bmp_file)) {
        return WRITE_ERROR;
    }
    return WRITE_OK;
}

enum write_status write_pixels(FILE *bmp_file, struct image const *img) {
    if (!bmp_file || !img) {
        return WRITE_ERROR;
    }
    for (size_t row = 0; row < img->height; row++) {
        if (!fwrite(img->data + row * img->width, PIXEL_SIZE, img->width, bmp_file)) {
            return WRITE_ERROR;
        }
        size_t padding = get_padding(img->width);
        if (padding > 0) {
            unsigned char padding_data[padding];
            memset(padding_data, 0, padding);
            if (!fwrite(padding_data, sizeof(unsigned char), padding, bmp_file)) {
                return WRITE_ERROR;
            }
        }
    }
    return WRITE_OK;
}

enum write_status to_bmp(FILE *bmp_file, struct image const *img) {
    enum write_status header_status = write_header(bmp_file, img);
    if (header_status != WRITE_OK) {
        return header_status;
    }
    enum write_status pixels_status = write_pixels(bmp_file, img);
    if (pixels_status != WRITE_OK) {
        return pixels_status;
    }
    return WRITE_OK;
}

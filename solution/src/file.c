
#include "../include/file.h"
#include "../include/image.h"
#include "../include/defines.h"

FILE* open(char* filename, char* mode) {
    return fopen(filename, mode);
}

uint32_t get_padding(const uint32_t width) {
    return (FACT_SIZE - (width * sizeof(struct pixel)) % FACT_SIZE) % FACT_SIZE;
}

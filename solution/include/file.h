
#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdint.h>

FILE *open(char *filename, char *mode);

uint32_t get_padding(uint32_t width);

#endif

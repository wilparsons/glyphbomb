#ifndef GLYPHBOMB_H
#define GLYPHBOMB_H

#include <stdbool.h>
#include <stdint.h>

bool glyphbomb_utf_16_to_utf_8(unsigned long input_count, unsigned short *input, unsigned long *output_count, unsigned char *output);
bool glyphbomb_utf_16_be_to_utf_8(unsigned long input_count, unsigned short *input, unsigned long *output_count, unsigned char *output);
bool glyphbomb_utf_16_le_to_utf_8(unsigned long input_count, unsigned short *input, unsigned long *output_count, unsigned char *output);
bool glyphbomb_utf_32_to_utf_8(unsigned long input_count, uint32_t *input, unsigned long *output_count, unsigned char *output);
bool glyphbomb_utf_32_be_to_utf_8(unsigned long input_count, uint32_t *input, unsigned long *output_count, unsigned char *output);
bool glyphbomb_utf_32_le_to_utf_8(unsigned long input_count, uint32_t *input, unsigned long *output_count, unsigned char *output);
bool glyphbomb_utf_8_to_utf_16(unsigned long input_count, unsigned char *input, unsigned long *output_count, unsigned short *output);
bool glyphbomb_utf_8_to_utf_32(unsigned long input_count, unsigned char *input, unsigned long *output_count, uint32_t *output);
bool glyphbomb_utf_8_validate(unsigned long count, unsigned char *input);
#endif

#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

// Function to parse form parameters
int parse_form_param(const char *body, const char *param_name, char *output, size_t maxlen);

// URL decoding function
int url_decode(const char *src, char *dest, size_t maxlen);

#endif

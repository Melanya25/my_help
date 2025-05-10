#ifndef INPUT_H
#define INPUT_H
#include <stddef.h>

int parse_form_param(const char *body, const char *param_name, char *output, size_t maxlen);

int url_decode(const char *src, char *dest, size_t maxlen);
#endif // INPUT_H

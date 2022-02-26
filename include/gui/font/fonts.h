#ifndef _FONTS_HEADER
#define _FONTS_HEADER
// Font handler

#include "../../../include/types.h"

typedef struct psf_header {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
} __attribute__((packed)) psf_header;

#endif
/* helpful.h - v0.01 - Jason Hilder

    A lot of inspiration/design from:
    https://github.com/nothings/stb/

    This is a single-header-file library that provides 
    convienent and helpful functions, defines etc. 

    To use this library, do this in *one* C or C++ file:
        #define HELPFUL_IMPLEMENTATION
        #include "helpful.h"

*/

#ifndef HELPFUL_H
#define HELPFUL_H

#include <stdio.h>
#include <stdlib.h>

// -------------------------------------- 
// Func Definitions
// -------------------------------------- 

// Function declarations (API)
int hf_read_file_to_buffer(char* file_path, char** out_buffer);

// -------------------------------------- 
// implementation Below
// -------------------------------------- 

#ifdef HELPFUL_IMPLEMENTATION

// -------------------------------------- 
// Macros:
// -------------------------------------- 
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})



// -------------------------------------- 
// Function defintions:
// -------------------------------------- 

// Takes file path and a buffer which will get 
// reallocated to the full file size. 
// Note: buffer still needs to be manually free'd
int hf_read_file_to_buffer(char* file_path, char** out_buffer)
{
    FILE *file = fopen(file_path, "rb");
    if(file == NULL)
    {
        perror("Failed to open file.");
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    if (file_size == -1)
    {
        perror("Failed to determine file size");
        fclose(file);
        return -1;
    }
    rewind(file);

    // Reallocate memory for the buffer, check if realloc is successful
    char *buffer = realloc(*out_buffer, file_size);
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Update the pointer to the newly allocated buffer
    *out_buffer = buffer; 

    size_t bytes_read = fread(*out_buffer, 1, file_size, file);
    if (bytes_read != file_size)
    {
        perror("Error reading file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

#endif

#endif 

#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#define MAX_MACRO_NAME 31
#define MAX_MACRO_LINES 100
#define MAX_LINE_LENGTH 81

typedef struct {
    char name[MAX_MACRO_NAME];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int line_count;
} Macro;

int pre_assemble_file(const char *base_filename);

#endif

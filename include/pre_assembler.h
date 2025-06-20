#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H
#define MAX_MACRO_NAME 31
#define MAX_MACRO_LINES 100
#define MAX_LINE_LENGTH 81

typedef enum {
    LINE_TYPE_IGNORE,         /* For comments or empty lines */
    LINE_TYPE_MACRO_DEF_START,  /* A line starting with "mcro" */
    LINE_TYPE_MACRO_DEF_END,    /* A line with "mcroend" */
    LINE_TYPE_MACRO_CONTENT,    /* A line inside a mcro/mcroend block */
    LINE_TYPE_MACRO_CALL,     /* A call to an existing macro */
    LINE_TYPE_REGULAR         /* Any other regular line of code */
} LineType;

typedef struct {
    char name[MAX_MACRO_NAME];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int line_count;
} Macro;

int pre_assemble_file(const char *base_filename);

#endif

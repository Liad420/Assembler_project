#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/pre_assembler.h"

static const char *reserved_words[] = {
    "mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", /* Instructions  */
    ".data", ".string", ".mat", ".entry", ".extern", /* Directives */
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" /* Registers  */
};

#define NUM_RESERVED_WORDS (sizeof(reserved_words) / sizeof(reserved_words[0]))

static bool is_reserved_word(const char *name) {
    int i;
    for (i = 0; i < NUM_RESERVED_WORDS; i++) {
        if (strcmp(name, reserved_words[i]) == 0) {
            return true;
        }
    }
    return false;
}
#define MAX_MACROS 50

static Macro macro_table[MAX_MACROS];
static int macro_count = 0;

int is_macro_definition(const char *line) {
    return strncmp(line, "mcro", 4) == 0;
}

int is_macro_end(const char *line) {
    return strncmp(line, "mcroend", 7) == 0;
}

void add_macro(const Macro *macro) {
    if (macro_count >= MAX_MACROS) {
        fprintf(stderr, "Error: too many macros.\n");
        exit(1);
    }
    macro_table[macro_count++] = *macro;
}

Macro *find_macro(const char *name) {
    int i;
    for (i = 0; i < macro_count; ++i) {
        if (strcmp(macro_table[i].name, name) == 0) {
            return &macro_table[i];
        }
    }
    return NULL;
}

int pre_assemble_file(const char *filename) {
    char input_name[100];
    char output_name[100];
    char line[MAX_LINE_LENGTH];
    char word[MAX_MACRO_NAME];
    FILE *in, *out;
    int in_macro;
    Macro current_macro;
    int error_found;
    Macro *macro; 
    int i;

    sprintf(input_name, "%s.as", filename);
    sprintf(output_name, "%s.am", filename);
    

    in = fopen(input_name, "r");
    if (!in) {
        perror("Failed to open input file");
        return 1;
    }

    out = fopen(output_name, "w");
    if (!out) {
        perror("Failed to open output file");
        fclose(in);
        return 1;
    }

    in_macro = 0;
    current_macro.line_count = 0;
    error_found = 0;

    while (fgets(line, MAX_LINE_LENGTH, in)) {
        if (is_macro_end(line)) {
            in_macro = 0;
            add_macro(&current_macro);
        }
        else if (is_macro_definition(line)) {
            in_macro = 1;
            sscanf(line + 4, "%s", current_macro.name); 
            current_macro.line_count = 0;

            if (is_reserved_word(current_macro.name)) {
                fprintf(stderr, "Error: Macro name '%s' is a reserved word.\n", current_macro.name);
                error_found = 1;
                break;
            }
            if (find_macro(current_macro.name) != NULL) {
                fprintf(stderr, "Error: Duplicate definition of macro '%s'.\n", current_macro.name);
                error_found = 1;
                break;
            }
        }
        
        else if (in_macro) {
            if (current_macro.line_count >= MAX_MACRO_LINES) {
                fprintf(stderr, "Macro too long: %s\n", current_macro.name);
                error_found = 1;
                break;
            }
            strcpy(current_macro.lines[current_macro.line_count++], line);
        }
        else {
            sscanf(line, "%s", word);
            macro = find_macro(word);
            if (macro) {
                for (i = 0; i < macro->line_count; ++i) {
                    fputs(macro->lines[i], out);
                }
            } else {
                fputs(line, out);
            }
        }
    }
    fclose(in);
    fclose(out);
    if (error_found) {
        remove(output_name);
        return 1;   
    }
    return 0;
}

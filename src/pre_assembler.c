

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/pre_assembler.h"
#include "../include/macro_table.h"

/* --- Helper Function Definitions --- */

static const char *reserved_words[] = {
    "mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop",
    ".data", ".string", ".mat", ".entry", ".extern",
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
};
#define NUM_RESERVED_WORDS (sizeof(reserved_words) / sizeof(reserved_words[0]))

/**
 * Checks if a given name is a reserved word.
 */
static bool is_reserved_word(const char *name) {
    int i;
    for (i = 0; i < NUM_RESERVED_WORDS; i++) {
        if (strcmp(name, reserved_words[i]) == 0) return true;
    }
    return false;
}

/**
 * Determines the type of a given line for the pre-assembler.
 * This is a key part of the parsing logic.
 */
static LineType determine_line_type(const char *line, bool in_macro, MacroNode *macro_head, char *first_word_out) {
    char temp_line[MAX_LINE_LENGTH];
    char *ptr;

    strcpy(temp_line, line);
    ptr = temp_line;
    while (isspace((unsigned char)*ptr)) ptr++;

    if (sscanf(ptr, "%s", first_word_out) != 1) {
        return LINE_TYPE_IGNORE;
    }

    if (in_macro) {
        if (strcmp(first_word_out, "mcroend") == 0) {
            return LINE_TYPE_MACRO_DEF_END;
        } else {
            return LINE_TYPE_MACRO_CONTENT;
        }
    }

    if (first_word_out[0] == ';') {
        return LINE_TYPE_IGNORE;
    }
    if (strcmp(first_word_out, "mcro") == 0) {
        return LINE_TYPE_MACRO_DEF_START;
    }
    if (find_macro(macro_head, first_word_out) != NULL) {
        return LINE_TYPE_MACRO_CALL;
    }

    return LINE_TYPE_REGULAR;
}

int pre_assemble_file(const char *filename) {
    char input_name[100], output_name[100], line[MAX_LINE_LENGTH];
    FILE *in, *out;
    int in_macro = 0, error_found = 0, line_number = 0, i;
    
    MacroNode *macro_table_head = NULL;
    MacroNode *found_macro;

    char current_macro_name[MAX_MACRO_NAME];
    char current_macro_lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int current_macro_line_count = 0;
    
    sprintf(input_name, "%s.as", filename);
    sprintf(output_name, "%s.am", filename);

    in = fopen(input_name, "r");
    if (!in) {
        fprintf(stdout, "Error: Failed to open input file '%s'.\n", input_name);
        return 1;
    }
    out = fopen(output_name, "w");
    if (!out) {
        fprintf(stdout, "Error: Failed to create output file '%s'.\n", output_name);
        fclose(in);
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, in)) {
        LineType line_type;
        char first_word[MAX_LINE_LENGTH];
        line_number++;

        line_type = determine_line_type(line, in_macro, macro_table_head, first_word);
        
        switch (line_type) {
            case LINE_TYPE_MACRO_DEF_START:
                in_macro = 1;
                sscanf(line, "mcro %s", current_macro_name);
                current_macro_line_count = 0;

                if (is_reserved_word(current_macro_name)) {
                    fprintf(stdout, "Error on line %d: Macro name '%s' is a reserved word.\n", line_number, current_macro_name);
                    error_found = 1;
                }
                if (find_macro(macro_table_head, current_macro_name) != NULL) {
                    fprintf(stdout, "Error on line %d: Duplicate definition of macro '%s'.\n", line_number, current_macro_name);
                    error_found = 1;
                }
                break;
            
            case LINE_TYPE_MACRO_DEF_END:
                in_macro = 0;
                macro_table_head = add_macro(macro_table_head, current_macro_name, current_macro_lines, current_macro_line_count);
                break;
            
            case LINE_TYPE_MACRO_CONTENT:
                if (current_macro_line_count >= MAX_MACRO_LINES) {
                    fprintf(stdout, "Error on line %d: Macro '%s' is too long.\n", line_number, current_macro_name);
                    error_found = 1;
                } else {
                    strcpy(current_macro_lines[current_macro_line_count++], line);
                }
                break;

            case LINE_TYPE_MACRO_CALL:
                found_macro = find_macro(macro_table_head, first_word);
                for (i = 0; i < found_macro->line_count; i++) {
                    fputs(found_macro->lines[i], out);
                }
                break;
            
            case LINE_TYPE_REGULAR:
            case LINE_TYPE_IGNORE:
                fputs(line, out);
                break;
        }

        if (error_found) {
            break;
        }
    }

    fclose(in);
    fclose(out);

    if (error_found) {
        remove(output_name);
    }
    
    free_macro_table(macro_table_head);
    return error_found;
}

#include <stdio.h>
#include <string.h> 
#include "include/pre_assembler.h"

#define MAX_LINE_LENGTH 81

int run_pre_assembler(const char* base_filename) {
    FILE *input_file, *output_file;
    char input_fname[256];
    char output_fname[256];
    char line[MAX_LINE_LENGTH];
    
    int line_number = 0; /* Good practice to keep track of the line number for errors */

    /* TODO: File opening logic here... */
    
    /* Open files - let's make this part more robust */
    strcpy(input_fname, base_filename);
    strcat(input_fname, ".as");
    input_file = fopen(input_fname, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open input file %s\n", input_fname);
        return 1;
    }

    strcpy(output_fname, base_filename);
    strcat(output_fname, ".am");
    output_file = fopen(output_fname, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Could not create output file %s\n", output_fname);
        fclose(input_file);
        return 1;
    }


    /* Read the input file line by line */
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        char first_word[MAX_LINE_LENGTH] = {0}; /* Initialize to empty */
        char second_word[MAX_LINE_LENGTH] = {0};

        line_number++;

        /* Try to read the first two words from the line. */
        sscanf(line, "%s %s", first_word, second_word);

        /* Now, let's just test what we found */
        if (first_word[0] != '\0') { /* Check if we actually read a word */
            printf("Line %d, First Word: '%s'\n", line_number, first_word);
        }
    }

    fclose(input_file);
    fclose(output_file);
    printf("Finished pre-assembler pass.\n");

    return 0;
}
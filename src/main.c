#include <stdio.h>
#include <string.h> 
#include "../include/pre_assembler.h" 
#include "../include/first_pass.h"
#include "../include/macro_table.h"

int main(int argc, char *argv[]) {

    int i;
    bool pre_assemble_success;

    /* Check if the user provided at least one filename */
    if (argc < 2) {
        fprintf(stdout, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    
    for (i = 1; i < argc; ++i) {
        printf("--- Processing file: %s.as ---\n", argv[i]);

        /* Call pre_assemble_file for each file provided in the command line arguments */
        pre_assemble_success = pre_assemble_file(argv[i]) == 0;

        if (pre_assemble_success) {
            /* If pre-assembly was successful, print a success message */
            printf("Pre-assembly for %s.as completed successfully.\n", argv[i]);

            printf("--- Starting First Pass for %s.am ---\n", argv[i]);

            if(run_first_pass(argv[i])) {
                /* If first pass was successful, print a success message */
                printf("First pass for %s.am completed successfully.\n\n", argv[i]);
                /* TODO: Call second_pass from here */
            } else {
                /* If first pass failed, print an error message */
                fprintf(stdout, "Stopping process for %s.as due to errors in First Pass.\n\n", argv[i]);
            }
        } else {
            /* If pre-assembly failed, print an error message */
           fprintf(stdout, "Stopping process for %s.as due to errors in Pre-Assembly.\n\n", argv[i]);
        }
    }

    return 0;
}
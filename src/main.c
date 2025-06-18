#include <stdio.h>
#include <string.h> 
#include "../include/pre_assembler.h" 

int main(int argc, char *argv[]) {

    int i;

    /* Check if the user provided at least one filename */
    if (argc < 2) {
        fprintf(stdout, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    
    for (i = 1; i < argc; ++i) {
        printf("--- Processing file: %s.as ---\n", argv[i]);
        /* Call pre_assemble_file for each file provided in the command line arguments */
        if (pre_assemble_file(argv[i]) != 0) {
            /* If pre_assemble_file returned an error, print a message and stop. */
            fprintf(stdout, "Stopping process for %s.as due to errors.\n\n", argv[i]);
        } else {
            /* Only print success if there were no errors */
            fprintf(stdout, "Pre-assembly for %s.as completed successfully.\n\n", argv[i]);
            
            /* TODO: Call first_pass and second_pass from here later */
        }
    }

    return 0;
}
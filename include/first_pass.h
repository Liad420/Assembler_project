#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include <stdbool.h> /* For the bool return type */

/**
 * Executes the first pass of the assembler.
 * Reads the .am file, builds the symbol table, and calculates memory layouts.
 * @param filename The base name of the file to process (e.g., "my_program").
 * @return True if the pass was successful (no errors), false otherwise.
 */
bool run_first_pass(const char *filename);

#endif
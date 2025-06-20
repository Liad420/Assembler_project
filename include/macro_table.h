/* In include/macro_table.h */

#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

#include <stdio.h>

/* A node in the linked list for storing macros */
typedef struct MacroNode {
    char *name;                 /* Dynamically allocated name */
    char **lines;               /* Dynamically allocated array of strings for content */
    int line_count;             /* Number of lines in the macro */
    struct MacroNode *next;     /* Pointer to the next macro in the list */
} MacroNode;

/* Function prototypes for functions in macro_table.c */

/**
 * Adds a new macro to the linked list.
 * @param head A pointer to the head of the list.
 * @param name The name of the macro to add.
 * @param lines The content of the macro.
 * @param line_count The number of lines in the content.
 * @return The new head of the list.
 */
MacroNode* add_macro(MacroNode *head, const char *name, char (*lines)[81], int line_count);

/**
 * Finds a macro by name in the linked list.
 * @param head The head of the list.
 * @param name The name of the macro to find.
 * @return A pointer to the found macro node, or NULL if not found.
 */
MacroNode* find_macro(MacroNode *head, const char *name);

/**
 * Frees all dynamically allocated memory for the macro table.
 * @param head The head of the list to free.
 */
void free_macro_table(MacroNode *head);

#endif
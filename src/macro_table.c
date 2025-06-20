#include <stdlib.h>
#include <string.h>
#include "../include/macro_table.h"

/* Adds a new macro to the head of the linked list */
MacroNode* add_macro(MacroNode *head, const char *name, char (*lines)[81], int line_count) {
    int i;
    /* 1. Allocate memory for the new node itself */
    MacroNode *new_node = (MacroNode *)malloc(sizeof(MacroNode));
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed for new macro node.\n");
        exit(1);
    }

    /* 2. Allocate memory for the macro name and copy it */
    new_node->name = (char *)malloc(strlen(name) + 1);
    if (!new_node->name) {
        fprintf(stderr, "Error: Memory allocation failed for macro name.\n");
        exit(1);
    }
    strcpy(new_node->name, name);

    /* 3. Allocate memory for the array of line pointers */
    new_node->lines = (char **)malloc(line_count * sizeof(char *));
    if (!new_node->lines) {
        fprintf(stderr, "Error: Memory allocation failed for macro lines array.\n");
        exit(1);
    }

    /* 4. Allocate memory for each line and copy it */
    for (i = 0; i < line_count; i++) {
        new_node->lines[i] = (char *)malloc(strlen(lines[i]) + 1);
        if (!new_node->lines[i]) {
            fprintf(stderr, "Error: Memory allocation failed for macro line content.\n");
            exit(1);
        }
        strcpy(new_node->lines[i], lines[i]);
    }

    new_node->line_count = line_count;
    new_node->next = head; /* 5. Link the new node to the start of the list */
    
    return new_node; /* The new node is now the new head of the list */
}

/* Finds a macro by name by traversing the linked list */
MacroNode* find_macro(MacroNode *head, const char *name) {
    MacroNode *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Frees all memory used by the macro table */
void free_macro_table(MacroNode *head) {
    MacroNode *current = head;
    MacroNode *next_node;
    int i;

    while (current != NULL) {
        next_node = current->next;

        /* Free each line string */
        for (i = 0; i < current->line_count; i++) {
            free(current->lines[i]);
        }
        /* Free the array of line pointers */
        free(current->lines);
        /* Free the name string */
        free(current->name);
        /* Free the node itself */
        free(current);

        current = next_node;
    }
}
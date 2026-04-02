#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static Symbol *hash_table[TABLE_SIZE];

unsigned int hash_function(const char *label) {
    unsigned int hash = 0;
    while (*label) {
        hash = (hash * 31 + (unsigned char)(*label)) % TABLE_SIZE;
        label++;
    }
    return hash;
}

void init_symbol_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

int add_symbol(const char *label, unsigned int address, const char *section) {
    unsigned int index = hash_function(label);

    Symbol *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->label, label) == 0) {
            return -1;  // aynı label zaten var
        }
        current = current->next;
    }

    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    if (new_symbol == NULL) {
        return -1;
    }

    strcpy(new_symbol->label, label);
    new_symbol->address = address;
    strcpy(new_symbol->section, section);
    new_symbol->next = hash_table[index];
    hash_table[index] = new_symbol;

    return 0;
}

int find_symbol(const char *label) {
    unsigned int index = hash_function(label);

    Symbol *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->label, label) == 0) {
            return current->address;
        }
        current = current->next;
    }

    return -1;
}

void print_symbol_table() {
    printf("\n--- SYMBOL TABLE (HASH) ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = hash_table[i];
        while (current != NULL) {
            printf("%s -> %u [%s] (bucket=%d)\n",
                   current->label,
                   current->address,
                   current->section,
                   i);
            current = current->next;
        }
    }
    printf("---------------------------\n");
}

void free_symbol_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = hash_table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

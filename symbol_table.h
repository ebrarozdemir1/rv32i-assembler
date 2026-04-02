#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TABLE_SIZE 101

typedef struct Symbol {
    char label[50];
    unsigned int address;
    char section[10];
    struct Symbol *next;
} Symbol;

void init_symbol_table();
int add_symbol(const char *label, unsigned int address, const char *section);
int find_symbol(const char *label);
void print_symbol_table();
void free_symbol_table();

#endif

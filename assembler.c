#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembler.h"
#include "utils.h"
#include "parser.h"
#include "symbol_table.h"

void run_assembler(const char *filename) {

    FILE *input = fopen(filename, "r");
    FILE *output = fopen("output.hex", "w");
    FILE *instr_mem = fopen("instr.mem", "w");
    FILE *data_mem  = fopen("data.mem", "w");

    char line[200];
    char current_section[10] = "text";

    unsigned int text_address = 0;
    unsigned int data_address = 0x1000;

    if (!input) {
        printf("File not found\n");
        return;
    }

    init_symbol_table();

    /* PASS 1: label adreslerini topla */
    while (fgets(line, sizeof(line), input)) {
        trim(line);

        if (line[0] == '\0') continue;

        if (strcmp(line, ".text") == 0) {
            strcpy(current_section, "text");
            continue;
        }

        if (strcmp(line, ".data") == 0) {
            strcpy(current_section, "data");
            continue;
        }

        if (strncmp(line, ".org", 4) == 0) {
            int new_addr = atoi(line + 4);
            if (strcmp(current_section, "text") == 0)
                text_address = new_addr;
            else
                data_address = new_addr;
            continue;
        }

        if (strchr(line, ':')) {
            char label[50];
            strcpy(label, line);

            char *colon = strchr(label, ':');
            *colon = '\0';

            if (strcmp(current_section, "text") == 0)
                add_symbol(label, text_address, "text");
            else
                add_symbol(label, data_address, "data");

            /* label ile aynı satırda directive varsa ileride ekleriz */
            continue;
        }

        if (line[0] == '.') {
            if (strncmp(line, ".word", 5) == 0) {
                data_address += 4;
            }
            else if (strncmp(line, ".byte", 5) == 0) {
                data_address += 1;
            }
            continue;
        }

        if (strcmp(current_section, "text") == 0) {
            text_address += 4;
        }
    }

    rewind(input);
    strcpy(current_section, "text");
    text_address = 0;
    data_address = 0x1000;

    /* PASS 2: çıktı üret */
    while (fgets(line, sizeof(line), input)) {
        trim(line);

        if (line[0] == '\0') continue;

        if (strcmp(line, ".text") == 0) {
            strcpy(current_section, "text");
            printf("Directive: .text\n");
            continue;
        }

        if (strcmp(line, ".data") == 0) {
            strcpy(current_section, "data");
            printf("Directive: .data\n");
            continue;
        }

        if (strcmp(line, ".end") == 0) {
            printf("Directive: .end\n");
            continue;
        }

        if (strncmp(line, ".org", 4) == 0) {
            int new_addr = atoi(line + 4);
            printf("Directive: %s\n", line);

            if (strcmp(current_section, "text") == 0)
                text_address = new_addr;
            else
                data_address = new_addr;

            continue;
        }

        if (strchr(line, ':')) {
            printf("Label: %s\n", line);
            continue;
        }

        if (strcmp(current_section, "text") == 0) {
            if (line[0] != '.') {
                parse_line(line, output, text_address);
                parse_line(line, instr_mem, text_address);
                text_address += 4;
            }
        }
        else if (strcmp(current_section, "data") == 0) {
            if (strncmp(line, ".word", 5) == 0) {
                int value = atoi(line + 5);
                printf("Directive: %s\n", line);
                fprintf(data_mem, "%08x\n", value & 0xFFFFFFFF);
                data_address += 4;
            }
            else if (strncmp(line, ".byte", 5) == 0) {
                int value = atoi(line + 5);
                printf("Directive: %s\n", line);
                fprintf(data_mem, "%02x\n", value & 0xFF);
                data_address += 1;
            }
        }
    }

    fclose(input);
    fclose(output);
    fclose(instr_mem);
    fclose(data_mem);

    print_symbol_table();
    free_symbol_table();
}


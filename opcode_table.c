#include <string.h>
#include "opcode_table.h"

static OpcodeEntry opcode_table[] = {
    {"add",  'R', 0x33, 0x0, 0x00},
    {"sub",  'R', 0x33, 0x0, 0x20},
    {"addi", 'I', 0x13, 0x0, 0x00},
    {"lw",   'I', 0x03, 0x2, 0x00},
    {"sw",   'S', 0x23, 0x2, 0x00},
    {"beq",  'B', 0x63, 0x0, 0x00},
    {"bne",  'B', 0x63, 0x1, 0x00}
};

static int opcode_count = sizeof(opcode_table) / sizeof(opcode_table[0]);

OpcodeEntry* find_opcode(const char *mnemonic) {
    for (int i = 0; i < opcode_count; i++) {
        if (strcmp(opcode_table[i].mnemonic, mnemonic) == 0) {
            return &opcode_table[i];
        }
    }
    return 0;
}

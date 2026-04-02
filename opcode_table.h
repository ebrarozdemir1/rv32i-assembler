#ifndef OPCODE_TABLE_H
#define OPCODE_TABLE_H

typedef struct {
    char mnemonic[10];
    char format;          // 'R', 'I', 'S'
    unsigned int opcode;
    unsigned int funct3;
    unsigned int funct7;
} OpcodeEntry;

OpcodeEntry* find_opcode(const char *mnemonic);

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "encoder.h"
#include "opcode_table.h"
#include "symbol_table.h"

int getRegisterNumber(char *reg) {
    if (reg[0] != 'x') return -1;
    int num = atoi(reg + 1);
    if (num < 0 || num > 31) return -1;
    return num;
}

void parse_memory_operand(char *memop, int *imm, int *rs1) {
    char offset_str[20];
    char reg_str[20];

    sscanf(memop, "%[^'(](%[^')'])", offset_str, reg_str);

    *imm = atoi(offset_str);
    *rs1 = getRegisterNumber(reg_str);
}

void parse_line(char *line, FILE *output, unsigned int current_address) {

    if (line[0] == '.') {
        printf("Directive: %s\n", line);
        return;
    }

    if (strchr(line, ':')) {
        printf("Label: %s\n", line);
        return;
    }

    char mnemonic[20], op1[20], op2[20], op3[20];
    op1[0] = op2[0] = op3[0] = '\0';

    sscanf(line, "%s %[^,], %[^,], %s", mnemonic, op1, op2, op3);

    OpcodeEntry *entry = find_opcode(mnemonic);

    if (!entry) {
        printf("Unknown instruction: %s\n\n", mnemonic);
        return;
    }

    printf("Instruction: %s\n", mnemonic);

    unsigned int code = 0;

    if (entry->format == 'R') {
        int rd  = getRegisterNumber(op1);
        int rs1 = getRegisterNumber(op2);
        int rs2 = getRegisterNumber(op3);

        code = encode_rtype(entry->opcode, entry->funct3, entry->funct7,
                            rd, rs1, rs2);
    }
    else if (entry->format == 'I') {
        int rd = getRegisterNumber(op1);

        if (strcmp(mnemonic, "lw") == 0) {
            int imm, rs1;
            parse_memory_operand(op2, &imm, &rs1);
            code = encode_itype(entry->opcode, entry->funct3, rd, rs1, imm);
        } else {
            int rs1 = getRegisterNumber(op2);
            int imm = atoi(op3);
            code = encode_itype(entry->opcode, entry->funct3, rd, rs1, imm);
        }
    }
    else if (entry->format == 'S') {
        int rs2 = getRegisterNumber(op1);
        int imm, rs1;
        parse_memory_operand(op2, &imm, &rs1);

        code = encode_stype(entry->opcode, entry->funct3, rs1, rs2, imm);
    }
    else if (entry->format == 'B') {
        int rs1 = getRegisterNumber(op1);
        int rs2 = getRegisterNumber(op2);
        int target_address = find_symbol(op3);

        if (target_address == -1) {
            printf("Undefined label: %s\n\n", op3);
            return;
        }

        int imm = target_address - current_address;

        code = encode_btype(entry->opcode, entry->funct3, rs1, rs2, imm);
    }

    printf("HEX: %08x\n\n", code);
    fprintf(output, "%08x\n", code);
}

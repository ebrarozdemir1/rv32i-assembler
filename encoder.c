#include "encoder.h"

unsigned int encode_rtype(unsigned int opcode, unsigned int funct3, unsigned int funct7,
                          int rd, int rs1, int rs2) {
    return ((funct7 & 0x7F) << 25) |
           ((rs2 & 0x1F) << 20) |
           ((rs1 & 0x1F) << 15) |
           ((funct3 & 0x7) << 12) |
           ((rd & 0x1F) << 7) |
           (opcode & 0x7F);
}

unsigned int encode_itype(unsigned int opcode, unsigned int funct3,
                          int rd, int rs1, int imm) {
    return ((imm & 0xFFF) << 20) |
           ((rs1 & 0x1F) << 15) |
           ((funct3 & 0x7) << 12) |
           ((rd & 0x1F) << 7) |
           (opcode & 0x7F);
}

unsigned int encode_stype(unsigned int opcode, unsigned int funct3,
                          int rs1, int rs2, int imm) {
    unsigned int imm11_5 = (imm >> 5) & 0x7F;
    unsigned int imm4_0  = imm & 0x1F;

    return ((imm11_5 & 0x7F) << 25) |
           ((rs2 & 0x1F) << 20) |
           ((rs1 & 0x1F) << 15) |
           ((funct3 & 0x7) << 12) |
           ((imm4_0 & 0x1F) << 7) |
           (opcode & 0x7F);
}

unsigned int encode_btype(unsigned int opcode, unsigned int funct3,
                          int rs1, int rs2, int imm) {
    unsigned int imm12   = (imm >> 12) & 0x1;
    unsigned int imm10_5 = (imm >> 5)  & 0x3F;
    unsigned int imm4_1  = (imm >> 1)  & 0xF;
    unsigned int imm11   = (imm >> 11) & 0x1;

    return ((imm12 & 0x1) << 31) |
           ((imm10_5 & 0x3F) << 25) |
           ((rs2 & 0x1F) << 20) |
           ((rs1 & 0x1F) << 15) |
           ((funct3 & 0x7) << 12) |
           ((imm4_1 & 0xF) << 8) |
           ((imm11 & 0x1) << 7) |
           (opcode & 0x7F);
}

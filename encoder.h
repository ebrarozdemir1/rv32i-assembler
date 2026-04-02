#ifndef ENCODER_H
#define ENCODER_H

unsigned int encode_rtype(unsigned int opcode, unsigned int funct3, unsigned int funct7,
                          int rd, int rs1, int rs2);

unsigned int encode_itype(unsigned int opcode, unsigned int funct3,
                          int rd, int rs1, int imm);

unsigned int encode_stype(unsigned int opcode, unsigned int funct3,
                          int rs1, int rs2, int imm);

unsigned int encode_btype(unsigned int opcode, unsigned int funct3,
                          int rs1, int rs2, int imm);

#endif

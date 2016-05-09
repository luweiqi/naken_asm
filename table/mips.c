/**
 *  naken_asm assembler.
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2010-2016 by Michael Kohn
 *
 */

#include <stdlib.h>

#include "table/mips.h"

struct _mips_instr mips_r_table[] =
{
  { "add", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x20, 3, MIPS_I },
  { "addu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x21, 3, MIPS_I },
  { "and", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x24, 3, MIPS_I },
  { "break", { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0x0d, 0, MIPS_I },
  { "dadd", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x2c, 3, MIPS_III },
  { "daddu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x2d, 3, MIPS_III },
  { "div", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 0x1a, 2, MIPS_I },
  { "divu", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 0x1b, 2, MIPS_I },
  { "dsll", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0xc8, 3, MIPS_III },
  { "dsll32", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x3c, 3, MIPS_III },
  { "dsllv", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_RS }, 0x14, 3, MIPS_III },
  { "dsra", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x3b, 3, MIPS_III },
  { "dsra32", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x3f, 3, MIPS_III },
  { "dsrav", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_RS }, 0x17, 3, MIPS_III },
  { "dsrl", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x3a, 3, MIPS_III },
  { "dsrl32", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x3e, 3, MIPS_III },
  { "dsrlv", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_RS }, 0x16, 3, MIPS_III },
  { "dsub", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x2e, 3, MIPS_III },
  { "dsubu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x2f, 3, MIPS_III },
  { "jalr", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_NONE }, 0x09, 2, MIPS_I },
  { "jr", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 0x08, 1, MIPS_I },
  { "mfhi", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 0x10, 1, MIPS_I },
  { "mflo", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 0x12, 1, MIPS_I },
  { "movn", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x0b, 3, MIPS_IV | MIPS_32 },
  { "movz", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x0a, 3, MIPS_IV | MIPS_32 },
  { "mthi", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 0x11, 1, MIPS_I },
  { "mtlo", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 0x13, 1, MIPS_I },
  { "mult", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 0x18, 2, MIPS_I },
  { "multu", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 0x19, 2, MIPS_I },
  { "nor", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x27, 3, MIPS_I },
  { "or", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x25, 3, MIPS_I },
  { "sll", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x00, 3, MIPS_I },
  { "sllv", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_RS }, 0x04, 3, MIPS_I },
  { "slt", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x2a, 3, MIPS_I },
  { "sltu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x2b, 3, MIPS_I },
  { "sra", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x03, 3, MIPS_I },
  { "srav", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_RS }, 0x07, 3, MIPS_I },
  { "srl", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 0x02, 3, MIPS_I },
  { "srlv", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_RS }, 0x06, 3, MIPS_I },
  { "sub", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x22, 3, MIPS_I },
  { "subu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x23, 3, MIPS_I },
  { "syscall", { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0x0c, 0, MIPS_I },
  { "xor", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 0x26, 3, MIPS_I },
  { NULL, { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0x00, 0 }
};

struct _mips_instr mips_i_table[] =
{
  { "addi", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED }, 0x08, 3, MIPS_I },
  { "addiu", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED }, 0x09, 3, MIPS_I },
  { "andi", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE }, 0x0c, 3, MIPS_I },
  { "daddi", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED }, 0x18, 3, MIPS_III },
  { "daddiu", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED }, 0x19, 3, MIPS_III },
  { "lb", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x20, 2, MIPS_I },
  { "lbu", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x24, 2, MIPS_I },
  { "ld", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x37, 2, MIPS_III },
  { "ldl", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x1a, 2, MIPS_III },
  { "ldr", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x1b, 2, MIPS_III },
  { "lh", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x21, 2, MIPS_I },
  { "lhu", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x25, 2, MIPS_I },
  { "lq", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x1e, 2, MIPS_EE_CORE },
  { "lui", { MIPS_OP_RT, MIPS_OP_IMMEDIATE, MIPS_OP_NONE }, 0x0f, 2, MIPS_I },
  { "ll", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x30, 2 },
  { "lw", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x23, 2, MIPS_I },
  { "lwl", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x22, 2, MIPS_I },
  { "lwc1", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x31, 2, MIPS_FPU },
  { "lwr", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x26, 2, MIPS_I },
  { "lwu", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x27, 2, MIPS_III },
  { "ori", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE }, 0x0d, 3, MIPS_I },
  { "pref", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x28, 2, MIPS_IV },
  { "sb", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x28, 2, MIPS_I },
  { "sc", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x38, 2, MIPS_II },
  { "sd", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x3f, 2, MIPS_III },
  { "sq", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x1f, 2, MIPS_III },
  { "sdl", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x2c, 2, MIPS_III },
  { "sdr", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x2d, 2, MIPS_III },
  { "sh", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x29, 2, MIPS_I },
  { "slti", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE }, 0x0a, 3, MIPS_I },
  { "sltiu", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE }, 0x0b, 3, MIPS_I },
  { "sw", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x2b, 2, MIPS_I },
  { "swl", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x2a, 2, MIPS_I },
  { "swr", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x2e, 2, MIPS_I },
  { "swc1", { MIPS_OP_RT, MIPS_OP_IMMEDIATE_RS, MIPS_OP_NONE }, 0x39, 2, MIPS_FPU },
  { "xori", { MIPS_OP_RT, MIPS_OP_RS, MIPS_OP_IMMEDIATE }, 0x0e, 3, MIPS_I },
  { NULL, { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0x00, 0 }
};

struct _mips_branch mips_branch_table[] =
{
  { "beq", 0x04, -1, MIPS_I },
  { "beql", 0x14, -1, MIPS_II },
  { "bgez", 0x01, 0x01, MIPS_I },
  { "bgezal", 0x01, 0x11, MIPS_I },
  { "bgezall", 0x01, 0x13, MIPS_II },
  { "bgezl", 0x01, 0x03, MIPS_II },
  { "bgtz", 0x07, 0x00, MIPS_I },
  { "bgtzl", 0x17, 0x00, MIPS_II },
  { "blez", 0x06, 0x00, MIPS_I },
  { "blezl", 0x16, 0x00, MIPS_II },
  { "bltz", 0x01, 0x00, MIPS_I },
  { "bltzal", 0x01, 0x10, MIPS_I },
  { "bltzall", 0x01, 0x12, MIPS_II },
  { "bltzl", 0x01, 0x02, MIPS_II },
  { "bne", 0x05, -1, MIPS_I },
  { "bnel", 0x15, -1, MIPS_II },
  { NULL, 0, 0, 0 }
};

struct _mips_special_instr mips_special_table[] =
{
  { "clo", { 1, 0, 0, -1 }, 2, FORMAT_SPECIAL2, 0x00, 0x21, SPECIAL_TYPE_REGS, MIPS_32 },
  { "clz", { 1, 0, 0, -1 }, 2, FORMAT_SPECIAL2, 0x00, 0x20, SPECIAL_TYPE_REGS, MIPS_32 },
  { "ext", { 1, 0, 3, 2 }, 4, FORMAT_SPECIAL3, 0x00, 0x00, SPECIAL_TYPE_BITS },
  { "ins", { 1, 0, 3, 2 }, 4, FORMAT_SPECIAL3, 0x00, 0x04, SPECIAL_TYPE_BITS2 },
  { "rotr", { 1, 0, 2, -1 }, 3, FORMAT_SPECIAL0, 0x01, 0x02, SPECIAL_TYPE_SA },
  { "rotrv", { 2, 1, 0, -1 }, 3, FORMAT_SPECIAL0, 0x01, 0x06, SPECIAL_TYPE_REGS },
  { NULL, { 0, 0, 0, 0 }, 0, 0, 0x00 }
};

struct _mips_cop_instr mips_cop_table[] =
{
  { "add.s", { MIPS_COP_FD, MIPS_COP_FS, MIPS_COP_FT }, 0x00, 0x10, 3 },
  { "cvt.s.w", { MIPS_COP_FD, MIPS_COP_FS, MIPS_COP_FT }, 0x20, 0x14, 3 },
  { "cvt.w.s", { MIPS_COP_FD, MIPS_COP_FS, MIPS_COP_FT }, 0x24, 0x10, 3 },
  { "div.s", { MIPS_COP_FD, MIPS_COP_FS, MIPS_COP_FT }, 0x03, 0x10, 3 },
  { "mfc1", { MIPS_COP_FT, MIPS_COP_FS, MIPS_OP_NONE }, 0x00, 0x00, 2 },
  { "mov.s", { MIPS_COP_FD, MIPS_COP_FS, MIPS_OP_NONE }, 0x06, 0x10, 2 },
  { "mtc1", { MIPS_COP_FT, MIPS_COP_FS, MIPS_OP_NONE }, 0x00, 0x04, 2 },
  { "mul.s", { MIPS_COP_FD, MIPS_COP_FS, MIPS_COP_FT }, 0x02, 0x10, 3 },
  { "sub.s", { MIPS_COP_FD, MIPS_COP_FS, MIPS_COP_FT }, 0x01, 0x10, 3 },
  { NULL, { MIPS_COP_NONE, MIPS_COP_NONE, MIPS_COP_NONE }, 0x00, 0x00, 0 }
};

struct _mips_no_operands mips_no_operands[] =
{
  { "sync.l", 0x0000000f, MIPS_II },
  { "sync", 0x0000000f, MIPS_II },
  { "sync.p", 0x0000040f, MIPS_II },
  { NULL, 0, 0 }
};

struct _mips_other mips_other[] =
{
  { "bc0f", { MIPS_OP_LABEL, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x41000000, 0xffff0000, MIPS_I },
  { "bc0fl", { MIPS_OP_LABEL, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x21020000, 0xffff0000, MIPS_I },
  { "bc0t", { MIPS_OP_LABEL, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x41010000, 0xffff0000, MIPS_I },
  { "bc0tl", { MIPS_OP_LABEL, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x41030000, 0xffff0000, MIPS_I },
  { "di", { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0, 0x42000039, 0xffffffff, MIPS_I },
  { "div1", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x7000001a, 0xfc00ffff, MIPS_EE_CORE },
  { "divu1", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x7000001b, 0xfc00ffff, MIPS_EE_CORE },
  { "ei", { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0, 0x42000038, 0xffffffff, MIPS_I },
  { "eret", { MIPS_OP_NONE, MIPS_OP_NONE, MIPS_OP_NONE }, 0, 0x42000018, 0xffffffff, MIPS_I },
  { "madd", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000000, 0xfc00ffff, MIPS_32 },
  { "madd", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 2, 0x70000000, 0xfc0007ff, MIPS_EE_CORE },
  { "madd1", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000020, 0xfc00ffff, MIPS_EE_CORE },
  { "madd1", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 2, 0x70000020, 0xfc0007ff, MIPS_EE_CORE },
  { "maddu", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000001, 0xfc00ffff, MIPS_32 },
  { "maddu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 2, 0x70000001, 0xfc0007ff, MIPS_EE_CORE },
  { "maddu1", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000021, 0xfc00ffff, MIPS_32 },
  { "maddu1", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 2, 0x70000021, 0xfc0007ff, MIPS_EE_CORE },
  { "mfbpc", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c000, 0xffff03ff, MIPS_I },
  { "mfc0", { MIPS_OP_RT, MIPS_OP_RD, MIPS_OP_NONE }, 2, 0x40000021, 0xffe007ff, MIPS_I },
  { "mfdab", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c004, 0xffe0ffff, MIPS_I },
  { "mfdabm", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c005, 0xffe0ffff, MIPS_I },
  { "mfdvb", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c006, 0xffe0ffff, MIPS_I },
  { "mfdvbm", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c007, 0xffe0ffff, MIPS_I },
  { "mfiab", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c002, 0xffe0ffff, MIPS_I },
  { "mfiabm", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4000c003, 0xffe0ffff, MIPS_I },
  { "mfhi1", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000010, 0xffff07ff, MIPS_EE_CORE },
  { "mflo1", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000012, 0xffff07ff, MIPS_EE_CORE },
  { "mfpc", { MIPS_OP_RT, MIPS_OP_PREG, MIPS_OP_NONE }, 2, 0x4000c801, 0xffe0ffc1, MIPS_I },
  { "mfps", { MIPS_OP_RT, MIPS_OP_PREG, MIPS_OP_NONE }, 2, 0x4000c800, 0xffe0ffc1, MIPS_I },
  { "mtbpc", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c000, 0xffe0ffff, MIPS_I },
  { "mtc0", { MIPS_OP_RT, MIPS_OP_RD, MIPS_OP_NONE }, 2, 0x40800000, 0xffe007ff, MIPS_I },
  { "mtdab", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c004, 0xffe0ffff, MIPS_I },
  { "mtdabm", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c005, 0xffe0ffff, MIPS_I },
  { "mtdvb", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c006, 0xffe0ffff, MIPS_I },
  { "mtdvbm", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c007, 0xffe0ffff, MIPS_I },
  { "mtiab", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c002, 0xffe0ffff, MIPS_I },
  { "mtiabm", { MIPS_OP_RT, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x4080c003, 0xffe0ffff, MIPS_I },
  { "mtpc", { MIPS_OP_RT, MIPS_OP_PREG, MIPS_OP_NONE }, 2, 0x4080c801, 0xffe0ffc1, MIPS_I },
  { "mtps", { MIPS_OP_RT, MIPS_OP_PREG, MIPS_OP_NONE }, 2, 0x4080c800, 0xffe0ffc1, MIPS_I },
  { "mthi1", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x00000011, 0xffff07ff, MIPS_EE_CORE },
  { "mtlo1", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x00000013, 0xffff07ff, MIPS_EE_CORE },
  { "mtsa", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x00000029, 0xffff07ff, MIPS_EE_CORE },
  { "mtsab", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 1, 0x04180000, 0xfc1f0000, MIPS_EE_CORE },
  { "mtsah", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 1, 0x04190000, 0xfc1f0000, MIPS_EE_CORE },
  { "msub", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000004, 0xfc00ffff, MIPS_32 },
  { "msubu", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000005, 0xfc00ffff, MIPS_32 },
  { "mul", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000002, 0xfc0007ff, MIPS_32 },
  { "mult", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x00000018, 0xfc0007ff, MIPS_EE_CORE },
  { "mult1", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000018, 0xfc00ffff, MIPS_EE_CORE },
  { "mult1", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000018, 0xfc0007ff, MIPS_EE_CORE },
  { "multu", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x00000019, 0xfc0007ff, MIPS_EE_CORE },
  { "multu1", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000019, 0xfc00ffff, MIPS_EE_CORE },
  { "multu1", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000019, 0xfc0007ff, MIPS_EE_CORE },
  { "pabsh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000168, 0xffe007ff, MIPS_EE_CORE },
  { "pabsw", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000068, 0xffe007ff, MIPS_EE_CORE },
  { "paddb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000208, 0xfc0007ff, MIPS_EE_CORE },
  { "paddh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000108, 0xfc0007ff, MIPS_EE_CORE },
  { "paddsb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000608, 0xfc0007ff, MIPS_EE_CORE },
  { "paddsh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000508, 0xfc0007ff, MIPS_EE_CORE },
  { "paddsw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000408, 0xfc0007ff, MIPS_EE_CORE },
  { "paddub", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000628, 0xfc0007ff, MIPS_EE_CORE },
  { "padduh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000528, 0xfc0007ff, MIPS_EE_CORE },
  { "padduw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000428, 0xfc0007ff, MIPS_EE_CORE },
  { "paddw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000008, 0xfc0007ff, MIPS_EE_CORE },
  { "padsbh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000128, 0xfc0007ff, MIPS_EE_CORE },
  { "pand", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000489, 0xfc0007ff, MIPS_EE_CORE },
  { "pceqb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700002a8, 0xfc0007ff, MIPS_EE_CORE },
  { "pceqh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700001a8, 0xfc0007ff, MIPS_EE_CORE },
  { "pceqw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700000a8, 0xfc0007ff, MIPS_EE_CORE },
  { "pcgtb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000288, 0xfc0007ff, MIPS_EE_CORE },
  { "pcgth", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000188, 0xfc0007ff, MIPS_EE_CORE },
  { "pcgtw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000088, 0xfc0007ff, MIPS_EE_CORE },
  { "pcpyh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700006e9, 0xfc0007ff, MIPS_EE_CORE },
  { "pcpyld", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000389, 0xfc0007ff, MIPS_EE_CORE },
  { "pcpyud", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700003a9, 0xfc0007ff, MIPS_EE_CORE },
  { "pdivbw", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000749, 0xfc00ffff, MIPS_EE_CORE },
  { "pdivuw", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000369, 0xfc00ffff, MIPS_EE_CORE },
  { "pdivw", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000349, 0xfc00ffff, MIPS_EE_CORE },
  { "pexch", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x700006a9, 0xffe007ff, MIPS_EE_CORE },
  { "pexeh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000689, 0xffe007ff, MIPS_EE_CORE },
  { "pexew", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000e89, 0xffe007ff, MIPS_EE_CORE },
  { "pext5", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000788, 0xffe007ff, MIPS_EE_CORE },
  { "pextlb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000688, 0xfc0007ff, MIPS_EE_CORE },
  { "pextlh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000588, 0xfc0007ff, MIPS_EE_CORE },
  { "pextlw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000488, 0xfc0007ff, MIPS_EE_CORE },
  { "pextub", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700006a8, 0xfc0007ff, MIPS_EE_CORE },
  { "pextuh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700005a8, 0xfc0007ff, MIPS_EE_CORE },
  { "pextuw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700004a8, 0xfc0007ff, MIPS_EE_CORE },
  { "phmadh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000449, 0xfc0007ff, MIPS_EE_CORE },
  { "phmsbh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000549, 0xfc0007ff, MIPS_EE_CORE },
  { "pinteh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700002a9, 0xfc0007ff, MIPS_EE_CORE },
  { "pinth", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000289, 0xfc0007ff, MIPS_EE_CORE },
  { "plzcw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_NONE }, 2, 0x70000004, 0xfc1f07ff, MIPS_EE_CORE },
  { "pmaddh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000409, 0xfc0007ff, MIPS_EE_CORE },
  { "pmadduw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000029, 0xfc0007ff, MIPS_EE_CORE },
  { "pmaddw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000009, 0xfc0007ff, MIPS_EE_CORE },
  { "pmaxh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700001c8, 0xfc0007ff, MIPS_EE_CORE },
  { "pmaxw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700000c8, 0xfc0007ff, MIPS_EE_CORE },
  { "pmfhi", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000209, 0xffff07ff, MIPS_EE_CORE },
  { "pmfhl.lh", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x700000f0, 0xffff07ff, MIPS_EE_CORE },
  { "pmfhl.lw", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000030, 0xffff07ff, MIPS_EE_CORE },
  { "pmfhl.sh", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000130, 0xffff07ff, MIPS_EE_CORE },
  { "pmfhl.slw", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x700000b0, 0xffff07ff, MIPS_EE_CORE },
  { "pmfhl.uw", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000070, 0xffff07ff, MIPS_EE_CORE },
  { "pmflo", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000249, 0xffff07ff, MIPS_EE_CORE },
  { "pminh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700001e8, 0xfc0007ff, MIPS_EE_CORE },
  { "pminw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700000e8, 0xfc0007ff, MIPS_EE_CORE },
  { "pmsubh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000509, 0xfc0007ff, MIPS_EE_CORE },
  { "pmsubw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000109, 0xfc0007ff, MIPS_EE_CORE },
  { "pmthi", { MIPS_OP_RD, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000229, 0xffff07ff, MIPS_EE_CORE },
  { "pmthl.uw", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000031, 0xfc1fffff, MIPS_EE_CORE },
  { "pmtlo", { MIPS_OP_RS, MIPS_OP_NONE, MIPS_OP_NONE }, 1, 0x70000269, 0xfc1fffff, MIPS_EE_CORE },
  { "pmulth", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000709, 0xfc0007ff, MIPS_EE_CORE },
  { "pmultuw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000329, 0xfc0007ff, MIPS_EE_CORE },
  { "pmultw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000309, 0xfc0007ff, MIPS_EE_CORE },
  { "pnor", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700004e9, 0xfc0007ff, MIPS_EE_CORE },
  { "por", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700004a9, 0xfc0007ff, MIPS_EE_CORE },
  { "ppac5", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x70000ec8, 0xffe007ff, MIPS_EE_CORE },
  { "ppacb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700006c8, 0xfc0007ff, MIPS_EE_CORE },
  { "ppach", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700005c8, 0xfc0007ff, MIPS_EE_CORE },
  { "ppacw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700004c8, 0xfc0007ff, MIPS_EE_CORE },
  { "prevh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x700006c9, 0xffe007ff, MIPS_EE_CORE },
  { "prot3w", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x700007c9, 0xffe007ff, MIPS_EE_CORE },
  { "psllh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 3, 0x70000034, 0xffe0003f, MIPS_EE_CORE },
  { "psllvw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000089, 0xfc0007ff, MIPS_EE_CORE },
  { "psllw", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 3, 0x7000003c, 0xffe0003f, MIPS_EE_CORE },
  { "psrah", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 3, 0x70000037, 0xffe0003f, MIPS_EE_CORE },
  { "psravw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700000e9, 0xfc0007ff, MIPS_EE_CORE },
  { "psraw", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 3, 0x7000003f, 0xffe0003f, MIPS_EE_CORE },
  { "psrlh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 3, 0x70000036, 0xffe0003f, MIPS_EE_CORE },
  { "psrlvw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700000c9, 0xfc0007ff, MIPS_EE_CORE },
  { "psrlw", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_SA }, 3, 0x7000003e, 0xffe0003f, MIPS_EE_CORE },
  { "psubb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000248, 0xfc0007ff, MIPS_EE_CORE },
  { "psubh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000148, 0xfc0007ff, MIPS_EE_CORE },
  { "psubsb", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000648, 0xfc0007ff, MIPS_EE_CORE },
  { "psubsh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000548, 0xfc0007ff, MIPS_EE_CORE },
  { "psubsw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000448, 0xfc0007ff, MIPS_EE_CORE },
  { "psubub", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000668, 0xfc0007ff, MIPS_EE_CORE },
  { "psubuh", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000568, 0xfc0007ff, MIPS_EE_CORE },
  { "psubuw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000468, 0xfc0007ff, MIPS_EE_CORE },
  { "psubw", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x70000048, 0xfc0007ff, MIPS_EE_CORE },
  { "pxor", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700004c9, 0xfc0007ff, MIPS_EE_CORE },
  { "qfsrv", { MIPS_OP_RD, MIPS_OP_RS, MIPS_OP_RT }, 3, 0x700006e8, 0xfc0007ff, MIPS_EE_CORE },
  { "seb", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x7c000420, 0xfc0007ff, MIPS_32 },
  { "seh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x7c000620, 0xfc0007ff, MIPS_32 },
  { "teq", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x00000034, 0xfc00003f, MIPS_II },
  { "teqi", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 2, 0x040c0000, 0xfc1f0000, MIPS_II },
  { "tge", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x000000c0, 0xfc00003f, MIPS_II },
  { "tgei", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 2, 0x04080000, 0xfc1f0000, MIPS_II },
  { "tgeiu", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 2, 0x04090000, 0xfc1f0000, MIPS_II },
  { "tgeu", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x000000c1, 0xfc00003f, MIPS_II },
  { "tlt", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x000000c2, 0xfc00003f, MIPS_II },
  { "tlti", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 2, 0x040a0000, 0xfc1f0000, MIPS_II },
  { "tltiu", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 2, 0x040b0000, 0xfc1f0000, MIPS_II },
  { "tltu", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x000000c3, 0xfc00003f, MIPS_II },
  { "tne", { MIPS_OP_RS, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x000000c6, 0xfc00003f, MIPS_II },
  { "tnei", { MIPS_OP_RS, MIPS_OP_IMMEDIATE_SIGNED, MIPS_OP_NONE }, 2, 0x040e0000, 0xfc1f0000, MIPS_II },
  { "wsbh", { MIPS_OP_RD, MIPS_OP_RT, MIPS_OP_NONE }, 2, 0x7c0000a0, 0xffe007ff, MIPS_II },
  { NULL, { 0, 0, 0 }, 0, 0, 0, 0 }
};

struct _mips_cache mips_cache[] =
{
  { "ixlrg", 0x00 },
  { "ixldt", 0x01 },
  { "bxlbt", 0x02 },
  { "ixstg", 0x04 },
  { "ixsdt", 0x05 },
  { "bxsbt", 0x06 },
  { "ixin", 0x07 },
  { "bhinbt", 0x0a },
  { "ihin", 0x0b },
  { "bfh", 0x0c },
  { "ifl", 0x0e },
  { "dxltg", 0x10 },
  { "dxldt", 0x11 },
  { "dxstg", 0x12 },
  { "dxsdt", 0x13 },
  { "dxwbin", 0x14 },
  { "dxin", 0x16 },
  { "dhwbin", 0x18 },
  { "dhin", 0x1a },
  { "dhwoin", 0x1c },
  { NULL, 0 },
};




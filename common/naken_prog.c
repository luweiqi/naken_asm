/**
 *  naken_asm assembler.
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2010-2013 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "lpc.h"
#include "parse_elf.h"
#include "parse_hex.h"
#include "version.h"

enum
{
  PROG_UNDEF=0,
  PROG_LPC,
};

enum
{
  COMMAND_UNDEF=0,
  COMMAND_INFO,
  COMMAND_READ,
  COMMAND_WRITE,
};

int main(int argc, char *argv[])
{
struct _memory memory;
char *hexfile=NULL;
int prog_type=PROG_UNDEF;
int command=COMMAND_UNDEF;
int param1=0,param2=0;
int i;

  printf("\nnaken_prog - by Michael Kohn\n");
  printf("    Web: http://www.mikekohn.net/\n");
  printf("  Email: mike@mikekohn.net\n\n");
  printf("Version: "VERSION"\n\n");

  if (argc<2)
  {
    printf("Usage: naken_util [options]\n");
    printf("  CPU options:\n");
    printf("   -lpc\n");
    printf("  Command:\n");
    printf("   -info\n");
    printf("   -write <hexfile>\n");
    printf("   -read <address> <count>\n");
    printf("\n");
    exit(0);
  }

  memset(&memory, 0, sizeof(memory));

  for (i=1; i<argc; i++)
  {
    if (strcmp(argv[i], "-lpc")==0)
    {
      prog_type=PROG_LPC;
    }
      else
    if (strcmp(argv[i], "-info")==0)
    {
      command=COMMAND_INFO;
    }
      else
    if (strcmp(argv[i], "-read")==0)
    {
      command=COMMAND_READ;
      if (i+2>=argc)
      {
        printf("Error: -read command takes 2 arguments\n");
        exit(1);
      }
      param1=atoi(argv[++i]);
      param2=atoi(argv[++i]);
    }
      else
    if (strcmp(argv[i], "-write")==0)
    {
      command=COMMAND_WRITE;
    }
      else
    {
      unsigned char cpu_type;
      if (parse_elf(argv[i], &memory, &cpu_type)>=0)
      {
        hexfile=argv[i];
        printf("Loaded elf %s from 0x%04x to 0x%04x\n", argv[i], memory.low_address, memory.high_address);
      }
        else
      if (parse_hex(argv[i], &memory)>=0)
      {
        hexfile=argv[i];
        printf("Loaded hexfile %s from 0x%04x to 0x%04x\n", argv[i], memory.low_address, memory.high_address);
      }
        else
      {
        printf("Could not load hexfile\n");
      }
    }
  }

  if (prog_type==PROG_UNDEF)
  {
    printf("Error: No chip type selected.\n");
  }

  if (command==COMMAND_INFO)
  {
    if (prog_type==PROG_LPC)
    {
      // FIXME - make USB port selectable
      lpc_info("/dev/ttyUSB0");
    }
  }
    else
  if (command==COMMAND_READ)
  {
    lpc_memory_read("/dev/ttyUSB0", param1, param2);
  }
    else
  if (command==COMMAND_WRITE)
  {
    if (hexfile==NULL)
    {
      printf("No hexfile loaded.  Exiting...\n");
      exit(1);
    }
  }

  return 0;
}



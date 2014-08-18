#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

typedef unsigned char byte;

const char* HOP = "hop-62fa7ade9a1fa9254361e69d70e7a7e3.exe";

/*
  0 .text         002c6510  0000000000401000  0000000000401000  00000400  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         000000a0  00000000006c8000  00000000006c8000  002c6a00  2**4
                  CONTENTS, ALLOC, LOAD, DATA
  2 .rdata        00000998  00000000006c9000  00000000006c9000  002c6c00  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .pdata        00000234  00000000006ca000  00000000006ca000  002c7600  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .xdata        00000200  00000000006cb000  00000000006cb000  002c7a00  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .bss          00000a00  00000000006cc000  00000000006cc000  00000000  2**5
                  ALLOC
  6 .idata        00000800  00000000006cd000  00000000006cd000  002c7c00  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  7 .CRT          00000068  00000000006ce000  00000000006ce000  002c8400  2**3
                  CONTENTS, ALLOC, LOAD, DATA
  8 .tls          00000068  00000000006cf000  00000000006cf000  002c8600  2**5
                  CONTENTS, ALLOC, LOAD, DATA
*/

struct Section {
  size_t size;
  size_t vma;
  size_t off;
};

Section sections[] = {
  { 0x2c6510, 0x401000, 0x400 },
#if 0
  { 0xa0, 0x6c8000, 0x2c6a00 },
  { 0x2c6510, 0x401000, 0x2c },
  { 0x2c6510, 0x401000, 0x400 },
#endif
  { 0, 0, 0 }
};

size_t roundup(size_t s) {
  return (s + 4095) & ~4095;
}

int main(int argc, char* argv[]) {
  const char* flag = "HITCON{01234567890123456789012345678901}";
  if (argv[1])
    flag = argv[1];
  int fd = open(HOP, O_RDONLY);

  for (int i = 0; sections[i].size; i++) {
    Section sec = sections[i];
    void* r = mmap((void*)sec.vma, roundup(sec.size),
                   PROT_READ | PROT_WRITE | PROT_EXEC,
                   MAP_ANONYMOUS | MAP_FIXED | MAP_PRIVATE, -1, 0);
    assert(r != MAP_FAILED);

    lseek(fd, sec.off, SEEK_SET);
    read(fd, (void*)sec.vma, sec.size);
  }

  byte* check_func_ms = (byte*)0x401590;
  // mov RCX, RDI (MS => GCC ABI)
  check_func_ms[-3] = 0x48;
  check_func_ms[-2] = 0x89;
  check_func_ms[-1] = 0xf9;

  int (*check_func)(const char*);
  check_func = (typeof(check_func))(check_func_ms - 3);
  //check_func("HITCON{SO0O0OO_MaNy_7Ar_Le\\/eLs}");
  //check_func("HITCON{0123456789012345678901}");
  //int r = check_func("HITCON{01234567890123456789012345678901}");
  int r = check_func(flag);
  printf("%d\n", r);
}

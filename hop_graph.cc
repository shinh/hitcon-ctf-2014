#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include <queue>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef unsigned char byte;
const char* HOP = "hop-62fa7ade9a1fa9254361e69d70e7a7e3.exe";

struct Chain {
  size_t addr;
  int mul;
  int add;
};

struct Ctx {
  int addr;
  string flag;
  //set<int> seen;
};

//const int GOAL = 0x4015b9;
const int GOAL = 0x43dbd2;
const int DEAD = 0x4015bf;

bool is_goal_reachable(int addr, multimap<int, pair<char, int> >& nex,
                       string* out = NULL) {
  if (addr == DEAD)
    return false;

  map<int, string> route;
  queue<pair<int, string> > q;
  q.push(make_pair(addr, ""));

  while (!q.empty()) {
    auto p = q.front();
    q.pop();

    if (!route.insert(p).second)
      continue;

    int a = p.first;
    if (a == DEAD)
      continue;

    if (a == GOAL) {
      if (out)
        *out = p.second;
      return true;
    }

    auto found = nex.find(a);
    if (found == nex.end()) {
      printf("%x %s\n", a, p.second.c_str());
      abort();
    }

    for (auto iter = found;
         iter != nex.end() && iter->first == a;
         ++iter) {
      auto e = iter->second;
      q.push(make_pair(e.second, p.second + e.first));
    }
  }
  return false;
}

int main() {
  int fd = open(HOP, O_RDONLY);
  const size_t text_size = 0x002c6510;
  byte* text = (byte*)calloc(text_size + 1000, 1);

  lseek(fd, 0x400, SEEK_SET);
  read(fd, text, 0x2c6510);

  vector<Chain> chains;

  for (size_t i = 0; i < text_size; i++) {
    //printf("%zu %d\n", i, text[i]);
    if (text[i] == 0x58 &&
        // imul
        text[i+1] == 0x48 &&
        text[i+2] == 0x69 &&
        text[i+3] == 0xc0 &&
        text[i+6] == 0x00 &&
        text[i+7] == 0x00 &&
        // mov
        text[i+8] == 0x8b &&
        text[i+9] == 0x84 &&
        text[i+10] == 0x02 &&
        text[i+13] == 0x00 &&
        text[i+14] == 0x00 &&
        // cltq
        text[i+15] == 0x48 &&
        text[i+16] == 0x98 &&
        // add
        text[i+17] == 0x48 &&
        text[i+18] == 0x01 &&
        text[i+19] == 0xc2 &&
        // jmp
        text[i+20] == 0xff &&
        text[i+21] == 0xe2) {
      size_t addr = i + 0x401000;
      int mul = text[i+5] * 256 + text[i+4];
      int add = text[i+12] * 256 + text[i+11];
      printf("%zx %x %x\n", addr, mul, add);
      Chain ch = {addr, mul, add};
      chains.push_back(ch);
    }
  }

  set<int> verts;
  multimap<int, pair<char, int> > nex;
  multimap<int, pair<char, int> > rev;
  map<int, map<char, int> > nex_map;

  for (size_t i = 0; i < chains.size(); i++) {
    Chain c = chains[i];
    for (int b = 0; b < 127; b++) {
      if (b < 32 && b > 0)
        continue;
      int eax = b * c.mul;
      eax = c.add + c.addr + eax;
      eax = *(int*)(text + eax - 0x401000);
      int go = c.addr + eax;
      //puts "#{b.chr} #{'%x'%edx} => #{'%x'%go}"
      printf("%c %x => %x\n", b, c.addr, go);

      nex.insert(make_pair(c.addr, make_pair(b, go)));
      rev.insert(make_pair(go, make_pair(b, c.addr)));
      nex_map[c.addr][b] = go;
      verts.insert(c.addr);
    }
  }

  puts("===");

  map<int, string> route;
  queue<pair<int, string> > q;
  int addr = 0x43a8fb;
  string flag = "HITCON{";
  //q.push(make_pair(0x44f491, ""));
  //q.push(make_pair(0x43a8fb, "HITCON{"));

  //string fix = "COf Us@ HUBA 0f Us@ 5";
  //string fix = "CabS0f Us@ 5hr1n] 0f Us@ ";
  //string fix = "yAA 0f Us@+U=: 0fUs@ 5hr1n3";
  //string fix = "CH2(Us@ H@A: 0f Us@ 5hr1n";
  //string fix = "CHeih1t-Q@ 5hr1n";
  //string fix = "CapiS";
  //string fix = "Cap7urA";
  string fix = "Cap7u";
  for (int i = 0; i < fix.size(); i++) {
    addr = nex_map[addr][fix[i]];
    flag += fix[i];
  }

  for (int b = 0; b < 127; b++) {
    if (b < 32 && b > 0)
      continue;

    int a = nex_map[addr][b];
    string s;
    if (is_goal_reachable(a, nex, &s)) {
      printf("%c %x => %x %c%s\n", b, addr, a, b, s.c_str());
    }
  }

#if 0
  string fix = "C";
  for (int i = 0; i < fix.size(); i++) {
    addr = nex_map[addr][fix[i]];
    flag += fix[i];
  }

  q.push(make_pair(addr, flag));

  while (!q.empty()) {
    auto p = q.front();
    q.pop();

    if (!route.insert(p).second)
      continue;

    int a = p.first;
    if (a == 0x4015bf)
      continue;

    auto found = nex.find(a);
    if (found == nex.end()) {
      printf("%x %s\n", a, p.second.c_str());
      return 0;
    }

    for (auto iter = found;
         iter != nex.end() && iter->first == a;
         ++iter) {
      auto e = iter->second;
      q.push(make_pair(e.second, p.second + e.first));
    }
  }
#endif

#if 0
  vector<int, string> addrs = { 0x44f491, "" };
  for (int i = 0; i < 40; i++) {
    set<int> naddrs;
    for (int a : addrs) {
      auto found = nex.find(a);
      if (found == nex.end())
        continue;
        //abort();

      for (auto iter = found;
           iter != nex.end() && iter->first == a;
           ++iter) {
        auto p = iter->second;
        printf("%x (%c)=> %x\n", a, p.first, p.second);
        naddrs.insert(p.second);
      }
    }

    addrs.clear();
    addrs.assign(naddrs.begin(), naddrs.end());
  }
#endif

#if 0
  vector<int> addrs = { 0x44f491 };
  //vector<int> addrs = { 0x43a8fb };
  for (int i = 0; i < 40; i++) {
    puts("---");
    printf("%d %zu\n", i, addrs.size());
    set<int> naddrs;
    for (int a : addrs) {
      auto found = nex.find(a);
      if (found == nex.end())
        continue;
        //abort();

      for (auto iter = found;
           iter != nex.end() && iter->first == a;
           ++iter) {
        auto p = iter->second;
        printf("%x (%c)=> %x\n", a, p.first, p.second);
        naddrs.insert(p.second);
      }
    }

    addrs.clear();
    addrs.assign(naddrs.begin(), naddrs.end());
  }
#endif

#if 0
  //const int goal = 0x4015b9;
  set<int> seen;

  queue<Ctx> q;
  q.push(Ctx({0x4015b9, ""}));
  //q.push(Ctx({0x43dbd2, ""}));
  //q.push(Ctx({0x403d07, ""}));

  while (!q.empty()) {
    Ctx c = q.front();
    q.pop();

    printf("%x %s\n", c.addr, c.flag.c_str());

    auto found = rev.find(c.addr);
    if (found == rev.end())
      continue;
      //return 0;
    for (auto iter = found;
         iter != rev.end() && iter->first == c.addr;
         ++iter) {
      auto p = iter->second;
      //printf("%c %d\n", p.first, p.first);
      int goal = p.second;
      //set<int> seen = c.seen;
      if (seen.insert(goal).second) {
        q.push(Ctx({goal, p.first + c.flag}));
      }
    }
  }

#endif
}

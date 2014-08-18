#include <stdio.h>
#include <time.h>

char g_buf[0x400];
time_t g_ptim;

void read_line(char* b, int n);
void print(char* b);

void show_msg(const char* time_str, const char* fmt) {
  char buf[0xb0];
  sprintf(buf, fmt, time_str, g_buf);
  print(buf);
}

void show() {
  char tmfmt[] = "         %2$s\n\0\0%s%s\n\0\0\0\0\0\0\0\0\0\0\0";
  time_t tim;
  struct tm* tm;
  char buf[80];

  time(&tim);
  tm = localtime(&tim);
  strftime(buf, 80, "%H:%M:%S ", tm);

  if (g_ptim != tim) {
    g_ptim = tim;
    show_msg(buf, tmfmt + 16);
  } else {
    show_msg(buf, tmfmt);
  }
}

void record_msg() {
  for (;;) {
    read_line(g_buf, 0x400);
    if (g_buf[0] == 'E' && g_buf[1] == 'N' && g_buf[2] == 'D' && !g_buf[3]) {
      return;
    }
    show();
  }
}

int main() {
  int i;
  char buf[4];

  alarm(30);
  for (i = 0; i < 3; i++) {
    print(".");
    sleep(1);
  }

  print("Sorry, we are not able to take your call right now.\n");
  print("Do you want to leave a message (y/n)? ");

  read_line(buf, 4);
  if (buf[0] != 'y') {
    print("Bye!\n");
  } else {
    record_msg();
  }
}

void read_line(char* b, int n) {
  for (; --n; b++) {
    *b = getchar();
    if (*b == '\n') {
      break;
    }
  }
  *b = 0;
}

void print(char* b) {
  for (; *b; b++) {
    putchar(*b);
    fflush(stdout);
  }
}

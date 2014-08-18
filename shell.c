char buf[99999];

int main() {
  const char* args[] = { "/bin/sh", 0 };
  asm("mov %0, %%rax\n"

      "mov %%rax, %%rsi\n"

      "mov %%rax, %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "inc %%rdx\n"
      "mov %%rdx, (%%rax)\n"

      "add $8, %%rax\n"
      "xor %%rdx, %%rdx\n"
      "mov %%rdx, (%%rax)\n"

      "add $8, %%rax\n"
      "mov %%rax, %%rdi\n"

      "movb $47, (%%rax)\n"
      "inc %%rax\n"

      "movb $98, (%%rax)\n"
      "inc %%rax\n"

      "movb $105, (%%rax)\n"
      "inc %%rax\n"

      "movb $110, (%%rax)\n"
      "inc %%rax\n"

      "movb $47, (%%rax)\n"
      "inc %%rax\n"

      "movb $115, (%%rax)\n"
      "inc %%rax\n"

      "movb $104, (%%rax)\n"
      "inc %%rax\n"

      "movb $0, (%%rax)\n"
      "inc %%rax\n"

      //"mov (%1), %%rdi\n"
      //"mov %1, %%rsi\n"
      "mov %%rsi, %%rdx\n"

      "xor %%rax, %%rax\n"
      "mov $59, %%rax\n"
      "syscall\n"
      ::"r"(buf), "r"(args)
      :"%rax", "%rdi", "%rsi", "%rdx");
}

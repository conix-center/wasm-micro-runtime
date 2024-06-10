#include "test_wasm.h"
#include <stdio.h>

int main() {
  for (int i = 0; i < 408; i++)
    putchar(wasm_test_file[i]);
  return 0;
}

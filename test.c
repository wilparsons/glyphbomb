#include <stdio.h>
#include "utf-8-validate.h"

int main(void) {
  unsigned char input[5] = {0x01, 0x02, 0x03, 0xC2, 0xA9};

  if (utf_8_validate(5, input) == 1) {
    printf("UTF-8 encoding is valid.\n");
  } else {
    printf("UTF-8 encoding is invalid.\n");
  }

  return 0;
}

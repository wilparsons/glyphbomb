#include "utf-8-validate.h"

char utf_8_validate(unsigned long count, unsigned char *input) {
  unsigned long i;
  char is_valid = 1;

  if (count != 0) {
    i = 0;

    while (
      is_valid == 1 &&
      i != count
    ) {
      if (
        input[i] > 127 &&
        input[i] < 247
      ) {
        i++;

        if (
          i != count &&
          input[i] > 127 &&
          input[i] < 192
        ) {
          if (input[i - 1] > 223) {
            i++;

            if (
              i != count &&
              input[i] > 127 &&
              input[i] < 192
            ) {
              if (
                input[i - 2] != 237 ||
                input[i - 1] < 160
              ) {
                if (input[i - 2] > 239) {
                  i++;

                  if (
                    input[i - 3] > 244 ||
                    (
                      input[i - 3] == 244 &&
                      input[i - 2] > 143
                    ) ||
                    i == count ||
                    input[i] < 128 ||
                    input[i] > 191
                  ) {
                    is_valid = 0;
                  }
                }
              } else {
                if (input[i - 1] < 176) {
                  i++;

                  if (
                    i != count &&
                    input[i] == 237
                  ) {
                    i++;

                    if (
                      i != count &&
                      input[i] > 175 &&
                      input[i] < 192
                    ) {
                      i++;

                      if (
                        i == count ||
                        input[i] < 128 ||
                        input[i] > 191
                      ) {
                        is_valid = 0;
                      }
                    } else {
                      is_valid = 0;
                    }
                  } else {
                    is_valid = 0;
                  }
                } else {
                  is_valid = 0;
                }
              }
            } else {
              is_valid = 0;
            }
          }
        } else {
          is_valid = 0;
        }
      } else {
        if (input[i] > 127) {
          is_valid = 0;
        }
      }

      i++;
    }
  }

  return is_valid;
}

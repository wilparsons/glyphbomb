#include "glyphbomb.h"

bool glyphbomb_utf_16_to_utf_8(unsigned long input_count, unsigned short *input, unsigned long *output_count, unsigned char *output) {
  unsigned short code_unit_1;
  unsigned short code_unit_2;
  uint32_t code_point;
  unsigned long i;
  unsigned long j = 0;
  bool is_reverse_byte_order;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;
    is_reverse_byte_order = false;

    if (
      input[0] == 0xFEFF ||
      input[0] == 0xFFFE
    ) {
      i = 1;

      if (input[0] == 0xFFFE) {
        is_reverse_byte_order = true;
      }
    }

    while (
      is_valid == true &&
      i != input_count
    ) {
      if (is_reverse_byte_order == true) {
        code_unit_1 = (input[i] << 8) + (input[i] >> 8);
      } else {
        code_unit_1 = input[i];
      }

      if (
        code_unit_1 > 55295 &&
        code_unit_1 < 57344
      ) {
        if (code_unit_1 < 56320) {
          i++;

          if (i != input_count) {
            if (is_reverse_byte_order == 1) {
              code_unit_2 = (input[i] << 8) + (input[i] >> 8);
            } else {
              code_unit_2 = input[i];
            }

            if (
              code_unit_2 > 56319 &&
              code_unit_2 < 57344
            ) {
              code_point = ((code_unit_1 & 1023) << 10) + (code_unit_2 & 1023) + 65536;
              output[j] = (code_point >> 18) + 240;
              j++;
              output[j] = ((code_point >> 12) & 63) + 128;
              j++;
              output[j] = ((code_point >> 6) & 63) + 128;
              j++;
              output[j] = (code_point & 63) + 128;
            } else {
              is_valid = false;
            }
          } else {
            is_valid = false;
          }
        } else {
          is_valid = false;
        }
      } else {
        if (code_unit_1 < 128) {
          output[j] = code_unit_1;
        } else {
          if (code_unit_1 < 2048) {
            output[j] = (code_unit_1 >> 6) + 192;
            j++;
            output[j] = (code_unit_1 & 63) + 128;
          } else {
            output[j] = (code_unit_1 >> 12) + 224;
            j++;
            output[j] = ((code_unit_1 >> 6) & 63) + 128;
            j++;
            output[j] = (code_unit_1 & 63) + 128;
          }
        }
      }

      i++;
      j++;
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_16_be_to_utf_8(unsigned long input_count, unsigned short *input, unsigned long *output_count, unsigned char *output) {
  uint32_t code_point;
  unsigned long i;
  unsigned long j = 0;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;

    while (
      is_valid == true &&
      i != input_count
    ) {
      if (
        input[i] > 55295 &&
        input[i] < 57344
      ) {
        if (input[i] < 56320) {
          i++;

          if (i != input_count) {
            if (
              input[i] > 56319 &&
              input[i] < 57344
            ) {
              code_point = ((input[i - 1] & 1023) << 10) + (input[i] & 1023) + 65536;
              output[j] = (code_point >> 18) + 240;
              j++;
              output[j] = ((code_point >> 12) & 63) + 128;
              j++;
              output[j] = ((code_point >> 6) & 63) + 128;
              j++;
              output[j] = (code_point & 63) + 128;
            } else {
              is_valid = false;
            }
          } else {
            is_valid = false;
          }
        } else {
          is_valid = false;
        }
      } else {
        if (input[i] < 128) {
          output[j] = input[i];
        } else {
          if (input[i] < 2048) {
            output[j] = (input[i] >> 6) + 192;
            j++;
            output[j] = (input[i] & 63) + 128;
          } else {
            output[j] = (input[i] >> 12) + 224;
            j++;
            output[j] = ((input[i] >> 6) & 63) + 128;
            j++;
            output[j] = (input[i] & 63) + 128;
          }
        }
      }

      i++;
      j++;
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_16_le_to_utf_8(unsigned long input_count, unsigned short *input, unsigned long *output_count, unsigned char *output) {
  unsigned short code_unit_1;
  unsigned short code_unit_2;
  uint32_t code_point;
  unsigned long i;
  unsigned long j = 0;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;

    while (
      is_valid == true &&
      i != input_count
    ) {
      code_unit_1 = (input[i] << 8) + (input[i] >> 8);

      if (
        code_unit_1 > 55295 &&
        code_unit_1 < 57344
      ) {
        if (code_unit_1 < 56320) {
          i++;

          if (i != input_count) {
            code_unit_2 = (input[i] << 8) + (input[i] >> 8);

            if (
              code_unit_2 > 56319 &&
              code_unit_2 < 57344
            ) {
              code_point = ((code_unit_1 & 1023) << 10) + (code_unit_2 & 1023) + 65536;
              output[j] = (code_point >> 18) + 240;
              j++;
              output[j] = ((code_point >> 12) & 63) + 128;
              j++;
              output[j] = ((code_point >> 6) & 63) + 128;
              j++;
              output[j] = (code_point & 63) + 128;
            } else {
              is_valid = false;
            }
          } else {
            is_valid = false;
          }
        } else {
          is_valid = false;
        }
      } else {
        if (code_unit_1 < 128) {
          output[j] = code_unit_1;
        } else {
          if (code_unit_1 < 2048) {
            output[j] = (code_unit_1 >> 6) + 192;
            j++;
            output[j] = (code_unit_1 & 63) + 128;
          } else {
            output[j] = (code_unit_1 >> 12) + 224;
            j++;
            output[j] = ((code_unit_1 >> 6) & 63) + 128;
            j++;
            output[j] = (code_unit_1 & 63) + 128;
          }
        }
      }

      i++;
      j++;
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_32_to_utf_8(unsigned long input_count, uint32_t *input, unsigned long *output_count, unsigned char *output) {
  uint32_t code_point;
  unsigned long i;
  unsigned long j = 0;
  bool is_reverse_byte_order;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;
    is_reverse_byte_order = false;

    if (
      input[0] == 0xFFFE0000 ||
      input[0] == 0x0000FEFF
    ) {
      i = 1;

      if (input[0] == 0xFFFE0000) {
        is_reverse_byte_order = true;
      }
    }

    while (
      is_valid == true &&
      i != input_count
    ) {
      if (is_reverse_byte_order == 1) {
        code_point = (input[i] << 24) + (((input[i] >> 8) & 255) << 16) + (((input[i] >> 16) & 255) << 8) + (input[i] >> 24);
      } else {
        code_point = input[i];
      }

      if (code_point < 1114112) {
        if (
          code_point < 55296 ||
          code_point > 57343
        ) {
          if (code_point < 128) {
            output[j] = code_point;
          } else {
            if (code_point < 2048) {
              output[j] = (code_point >> 6) + 192;
              j++;
              output[j] = (code_point & 63) + 128;
            } else {
              if (code_point < 65536) {
                output[j] = (code_point >> 12) + 224;
                j++;
                output[j] = ((code_point >> 6) & 63) + 128;
                j++;
                output[j] = (code_point & 63) + 128;
              } else {
                output[j] = (code_point >> 18) + 240;
                j++;
                output[j] = ((code_point >> 12) & 63) + 128;
                j++;
                output[j] = ((code_point >> 6) & 63) + 128;
                j++;
                output[j] = (code_point & 63) + 128;
              }
            }
          }

          i++;
          j++;
        } else {
          is_valid = false;
        }
      } else {
        is_valid = false;
      }
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_32_be_to_utf_8(unsigned long input_count, uint32_t *input, unsigned long *output_count, unsigned char *output) {
  unsigned long i;
  unsigned long j = 0;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;

    while (
      is_valid == 1 &&
      i != input_count
    ) {
      if (input[i] < 1114112) {
        if (
          input[i] < 55296 ||
          input[i] > 57343
        ) {
          if (input[i] < 128) {
            output[j] = input[i];
          } else {
            if (input[i] < 2048) {
              output[j] = (input[i] >> 6) + 192;
              j++;
              output[j] = (input[i] & 63) + 128;
            } else {
              if (input[i] < 65536) {
                output[j] = (input[i] >> 12) + 224;
                j++;
                output[j] = ((input[i] >> 6) & 63) + 128;
                j++;
                output[j] = (input[i] & 63) + 128;
              } else {
                output[j] = (input[i] >> 18) + 240;
                j++;
                output[j] = ((input[i] >> 12) & 63) + 128;
                j++;
                output[j] = ((input[i] >> 6) & 63) + 128;
                j++;
                output[j] = (input[i] & 63) + 128;
              }
            }
          }

          i++;
          j++;
        } else {
          is_valid = false;
        }
      } else {
        is_valid = false;
      }
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_32_le_to_utf_8(unsigned long input_count, uint32_t *input, unsigned long *output_count, unsigned char *output) {
  uint32_t code_point;
  unsigned long i;
  unsigned long j = 0;
  bool is_valid = 1;

  if (input_count != 0) {
    i = 0;

    while (
      is_valid == 1 &&
      i != input_count
    ) {
      code_point = (input[i] << 24) + (((input[i] >> 8) & 255) << 16) + (((input[i] >> 16) & 255) << 8) + (input[i] >> 24);

      if (code_point < 1114112) {
        if (
          code_point < 55296 ||
          code_point > 57343
        ) {
          if (code_point < 128) {
            output[j] = code_point;
          } else {
            if (code_point < 2048) {
              output[j] = (code_point >> 6) + 192;
              j++;
              output[j] = (code_point & 63) + 128;
            } else {
              if (code_point < 65536) {
                output[j] = (code_point >> 12) + 224;
                j++;
                output[j] = ((code_point >> 6) & 63) + 128;
                j++;
                output[j] = (code_point & 63) + 128;
              } else {
                output[j] = (code_point >> 18) + 240;
                j++;
                output[j] = ((code_point >> 12) & 63) + 128;
                j++;
                output[j] = ((code_point >> 6) & 63) + 128;
                j++;
                output[j] = (code_point & 63) + 128;
              }
            }
          }

          i++;
          j++;
        } else {
          is_valid = false;
        }
      } else {
        is_valid = false;
      }
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_8_to_utf_16(unsigned long input_count, unsigned char *input, unsigned long *output_count, unsigned short *output) {
  uint32_t code_point;
  unsigned long i;
  unsigned long j = 0;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;

    while (
      is_valid == true &&
      i != input_count
    ) {
      if (
        input[i] > 127 &&
        input[i] < 247
      ) {
        i++;

        if (
          i != input_count &&
          input[i] > 127 &&
          input[i] < 192
        ) {
          if (input[i - 1] > 223) {
            i++;

            if (
              i != input_count &&
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
                    (
                      input[i - 3] < 244 ||
                      (
                        input[i - 3] == 244 &&
                        input[i - 2] < 144
                      )
                    ) &&
                    (
                      input[i - 3] != 240 ||
                      input[i - 2] > 143
                    ) &&
                    i != input_count &&
                    input[i] > 127 &&
                    input[i] < 192
                  ) {
                    code_point = (((input[i - 3] & 7) << 18) + ((input[i - 2] & 63) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63)) - 65536;
                    output[j] = (code_point >> 10) + 55296;
                    j++;
                    output[j] = (code_point & 1023) + 56320;
                  } else {
                    is_valid = false;
                  }
                } else {
                  output[j] = ((input[i - 2] & 15) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                }
              } else {
                if (input[i - 1] < 176) {
                  output[j] = ((input[i - 2] & 15) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                  i++;
                  j++;

                  if (
                    i != input_count &&
                    input[i] == 237
                  ) {
                    i++;

                    if (
                      i != input_count &&
                      input[i] > 175 &&
                      input[i] < 192
                    ) {
                      i++;

                      if (
                        i != input_count &&
                        input[i] > 127 &&
                        input[i] < 192
                      ) {
                        output[j] = ((input[i - 2] & 15) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                      } else {
                        is_valid = false;
                      }
                    } else {
                      is_valid = false;
                    }
                  } else {
                    is_valid = false;
                  }
                } else {
                  is_valid = false;
                }
              }
            } else {
              is_valid = false;
            }
          } else {
            if (input[i - 1] > 193) {
              output[j] = ((input[i - 1] & 31) << 6) + (input[i] & 63);
            } else {
              is_valid = false;
            }
          }
        } else {
          is_valid = false;
        }
      } else {
        if (input[i] < 128) {
          output[j] = input[i];
        } else {
          is_valid = false;
        }
      }

      i++;
      j++;
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_8_to_utf_32(unsigned long input_count, unsigned char *input, unsigned long *output_count, uint32_t *output) {
  unsigned long i;
  unsigned long j = 0;
  bool is_valid = true;

  if (input_count != 0) {
    i = 0;

    while (
      is_valid == true &&
      i != input_count
    ) {
      if (
        input[i] > 127 &&
        input[i] < 247
      ) {
        i++;

        if (
          i != input_count &&
          input[i] > 127 &&
          input[i] < 192
        ) {
          if (input[i - 1] > 223) {
            i++;

            if (
              i != input_count &&
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
                    (
                      input[i - 3] < 244 ||
                      (
                        input[i - 3] == 244 &&
                        input[i - 2] < 144
                      )
                    ) &&
                    (
                      input[i - 3] != 240 ||
                      input[i - 2] > 143
                    ) &&
                    i != input_count &&
                    input[i] > 127 &&
                    input[i] < 192
                  ) {
                    output[j] = ((input[i - 3] & 7) << 18) + ((input[i - 2] & 63) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                  } else {
                    is_valid = false;
                  }
                } else {
                  output[j] = ((input[i - 2] & 15) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                }
              } else {
                if (input[i - 1] < 176) {
                  output[j] = ((input[i - 2] & 15) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                  i++;
                  j++;

                  if (
                    i != input_count &&
                    input[i] == 237
                  ) {
                    i++;

                    if (
                      i != input_count &&
                      input[i] > 175 &&
                      input[i] < 192
                    ) {
                      i++;

                      if (
                        i != input_count &&
                        input[i] > 127 &&
                        input[i] < 192
                      ) {
                        output[j] = ((input[i - 2] & 15) << 12) + ((input[i - 1] & 63) << 6) + (input[i] & 63);
                      } else {
                        is_valid = false;
                      }
                    } else {
                      is_valid = false;
                    }
                  } else {
                    is_valid = false;
                  }
                } else {
                  is_valid = false;
                }
              }
            } else {
              is_valid = false;
            }
          } else {
            if (input[i - 1] > 193) {
              output[j] = ((input[i - 1] & 31) << 6) + (input[i] & 63);
            } else {
              is_valid = false;
            }
          }
        } else {
          is_valid = false;
        }
      } else {
        if (input[i] < 128) {
          output[j] = input[i];
        } else {
          is_valid = false;
        }
      }

      i++;
      j++;
    }
  }

  *output_count = j;
  return is_valid;
}

bool glyphbomb_utf_8_validate(unsigned long count, unsigned char *input) {
  unsigned long i;
  bool is_valid = true;

  if (count != 0) {
    i = 0;

    while (
      is_valid == true &&
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
                    (
                      input[i - 3] == 240 &&
                      input[i - 2] < 144
                    ) ||
                    i == count ||
                    input[i] < 128 ||
                    input[i] > 191
                  ) {
                    is_valid = false;
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
                        is_valid = false;
                      }
                    } else {
                      is_valid = false;
                    }
                  } else {
                    is_valid = false;
                  }
                } else {
                  is_valid = false;
                }
              }
            } else {
              is_valid = false;
            }
          } else {
            if (input[i - 1] < 194) {
              is_valid = false;
            }
          }
        } else {
          is_valid = false;
        }
      } else {
        if (input[i] > 127) {
          is_valid = false;
        }
      }

      i++;
    }
  }

  return is_valid;
}

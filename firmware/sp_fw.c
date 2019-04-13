////////////////////////////////////////////////////////////////////////////////
//
//                     The Simple Platform project
//
// This file is distributed under the MIT License. See LICENSE.TXT for details.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "driver/camellia.h"
#include "driver/transmitter.h"

#define LOOPS 10

uint key[] = {0x11234567, 0x89ABCDEF, 0xEDCBA987, 0x76543210};
uint data[] = {0x40404040, 0x30303030, 0x20202020, 0x10101010};
uint result[] = {1, 2, 3, 4};

int run_testbench() {

  printf("Enabling Camellia...\n");
  enableCamellia();

  int fail = 0;
  for (int i = 0; i < LOOPS && fail == 0; i++) {

    // Loading the key for Camellia
    printf("Loading key:\t%x%x%x%x\n", key[0], key[1], key[2], key[3]);
    loadKey(key);

    // Encoding data
    printf("Encoding data:\t%x%x%x%x\n", data[0], data[1], data[2], data[3]);
    encDec(data, result, ENC);
    printf("Result:\t\t%x%x%x%x\n", result[0], result[1], result[2], result[3]);

    // Sending each byte to the transmitter
    for (int j = 0; j < 4; j++)
      transmitInt(result[j]);

    printf("Decoding....\n");
    encDec(result, result, DEC);

    // Checking the result:
    // text_1 -> (enc -> dec) -> text_2. text_1 must be equal to text_2
    printf("Checking....");
    for (int j = 0; j < 4; j++)
      fail = fail || (result[j] != data[j]);

    printf("%s\n", (fail)? "ERROR" : "OK");

	// Genering a new key and word for the cipher
	if (!fail) {
      uint tk = key[0];
      uint td = data[3];

      for (int j = 0; j < 3; j++) {
        key[j] = key[j + 1];
        data[4 - j - 1] = data[4 - j - 2];
      }

      key[3] = tk;
      data[0] = td;
    }
  }

  return fail;
}

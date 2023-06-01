#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
char *shifted_alphabet[25];
int MIN_SHIFT_VALUE = 0;
int MAX_SHIFT_VALUE = 26;

void printUsage() {
  printf("Usage: \n\n");
  printf("./main\n");
  printf("<msg>      The message to be encrypted\n\n");
  printf("<key>      A shift value between 0 and 25\n");
}

int main(int argc, char *argv[]) {
  if (argc == 3) {
    char *msg = argv[1];
    int msg_len = strlen(msg);
    int shift_key = atoi(argv[2]);
    if (shift_key < MIN_SHIFT_VALUE || shift_key > MAX_SHIFT_VALUE) {
      printUsage();
      exit(69);
    }
    size_t alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);
    for (size_t i = 0; i < alphabet_size; i++) {
      size_t shift_value = shift_key + i;
      if (shift_value > alphabet_size - 1) {
        shift_value = shift_value - alphabet_size;
      }
      shifted_alphabet[i] = alphabet[shift_value];
    }

    char *encrypted_msg = NULL;
    size_t encrypted_msg_size = 256;
    encrypted_msg = (char *) malloc(encrypted_msg_size * sizeof(char));

    if (encrypted_msg == NULL) {
      printf("Could not allocate memory\n");
      exit(69);
    }

    for (int i = 0; i < msg_len; i++) {
      for (size_t j = 0; j < alphabet_size; j++) {
        if (msg[i] == alphabet[j][0]) {
          encrypted_msg[i] = shifted_alphabet[j][0];
        }
      }
    }

    printf("-----BEGIN ENCRYPTED VALUE-----\n%s\n-----END ENCRYPTED VALUE-----\n", encrypted_msg);

    free(encrypted_msg);
  } else {
    printUsage();
  }

  return 0;
}
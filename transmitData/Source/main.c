#include "main.h"

int main(int argc, char const *argv[]) {
  frame_nfc data;

  transmit(&data, (char *)"1011", (char *)"10011001");

  printf("data.data_frame: %s\n", data.data_frame);

  return 0;
}

#include <iostream>
#include <string>
#include <windows.h>
#include "1-up-date-client.h"

int main(int argc, char **argv) {
  StartOneUpDateClient(1000, "test");
  int i = 0;
  
  TerminateOneUpDateClient();
  return 0;
}

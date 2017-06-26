#include <stdio.h>
#include "my_game.h"
#include "my_list.h"

int main(void){
  initialize();
  while (is_finish())exec();
  finalize();
  return 0;
}

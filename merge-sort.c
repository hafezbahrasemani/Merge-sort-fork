#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>



/*
 The sort function which is a recursive function
 that is based on merge-sort algorithm.
*/
void sort(int begin, int end)
{
  //The middle point
  int middle;

  //Base case -> begin >= end, it means sorting is done (:
  if(begin >= end) return;

  else
  {
    middle = (begin + end) / 2;

    //sort the left side of middle
    sort(begin, middle);

    //sort the right side of middle
    sort(middle + 1, end);

    //merge two sorted parts
    merge(begin, middle, middle + 1, end);
  }
}


int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}

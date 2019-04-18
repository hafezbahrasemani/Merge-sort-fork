#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SIZE 10000


void sort(int begin, int end);
void merge(int begin1m int end1, int begin2, int end2);

//Shared memory
int *shm;

//internal memory
int internal[SIZE];


int main(int argc, char const *argv[]) {
  
}


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

/*
  merge function that gets 4 integers as the
  begin and end points of two pats to be merged
*/
void merge(int begin1, int end1, int begin2, int end2)
{
  int i, j, k, l, m;
  k = begin1;

  //in every iteration compares two ints from both parts and adds the smaller one to the internal array as an temp array
  for(i = begin1, j = begin2; i <= end1, j <= end2; i++, j++)
  {
    if(shm[i] < shm[j]) internal[k++] = shm[i++];
    else internal[k++] = shm[j++];
  }


  for(l = i; l <= end1, l++) internal[k++] = shm[i];

  for(l = j; l <= end2, l++) internal[k++] = shm[j];

  //filling the actual array
  for(m = begin1; m <= end2, m++) shm[m] = internal[m];
}

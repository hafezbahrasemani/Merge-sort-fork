#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 10000

void sort(int begin, int end);
void merge(int begin1, int end1, int begin2, int end2);
void print_array(void);

//Shared memory
int *shm;

//internal memory
int internal[SIZE];


int main(int argc, char const *argv[]) {
  pid_t left, right;
  key_t key;
  int shmid;
  int M;
  int index = 0;
  int begin, middle, end;
  int status1, status2;

   /*
    * Create the segment.
    */
    if ((shmid = shmget(key, sizeof(int) * SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    //prompt the user to enter M
    printf("Please enter the value of M: ");
    scanf("%d", &M);

    //producing 10000 random numbers
    while(index < SIZE)
    {
      shm[index++] = (rand() % 100000) + 1;
    }
    print_array();

    //should not use fork() if the number of elements is less than M
    if(index <= M)
    {
      sort(0, index - 1);
      printf("----Sorted Array------\n");
      print_array();

      shmctl(shmid, IPC_RMID, NULL);
    }
    else{
      
        begin = 0;
        middle = (index - 1) / 2;
        end = index - 1;

        left = fork();
        if(left == 0){
          if((shm = shmat(shmid, (void *) 0, SHM_RND)) == (int *) -1) perror("shmat");
          sort(begin, middle);
        }else {
          right = fork();
          if(right == 0){
            if((shm = shmat(shmid, (void *) 0, SHM_RND)) == (int *) -1) perror("shmat");
            sort(middle + 1, end);
          } else{
                waitpid(left, &status1, 0);
                waitpid(right, &status2, 0);

                merge(begin, middle, middle + 1, end);

                printf("----Sorted Array------\n");
                print_array();

                if((shmdt(shm)) == -1) perror("shmat");
                shmctl(shmid, IPC_RMID, NULL);
          }
        }

    }
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
  for(i = begin1, j = begin2; i <= end1 && j <= end2; k++)
  {
    if(shm[i] < shm[j]) {
      internal[k] = shm[i++];
    } else {
      internal[k] = shm[j++];
    }
  }


  for(l = i; l <= end1; l++) internal[k++] = shm[l];

  for(l = j; l <= end2; l++) internal[k++] = shm[l];

  //filling the actual array
  for(m = begin1; m <= end2; m++) shm[m] = internal[m];
}

/*
  this function prints the elements of the array
*/
void print_array(void)
{
  for(int i = 0; i < SIZE; i++){
    printf("%d\n", shm[i]);
  }
}

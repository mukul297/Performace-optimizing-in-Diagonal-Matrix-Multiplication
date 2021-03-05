#include <pthread.h>
/*Making all the required variable global*/
int N;
int bs = 16;
int numOfThreads =64;
int *matA;
int *matB;
int *output;

/* I am creating an array for every thread to avoid synchronization. Storing the result of every thread in
their respective array and adding it to the output array in the last.*/


// args_struct type data variable is passed as a arguement with every thread when MultipleThreadCode function is called.
struct args_struct{
  // threadno stores what is the current thread no. the thread.
    int threadNo;
  // arr pointer will points to the array which is storing the result of every thread.
    int* arr;
};

void* MultipleThreadCode(void* arg){

    struct args_struct *args = (struct args_struct*) arg;
    //Dynamically allocating the array for the thread to store the temperary result.
    ( args->arr ) = (int* )malloc(( 2 * N - 1) * sizeof( int ) );

    for(int i = 0 ; i < N;i += bs)
    {
     for(int j = 0; j < N;j +=bs)
      {
        /* Checking which matrix blocks are allocated to the present thread. Based on that thread will proceed,
        if the condition is true */
      if( ( i + j ) % numOfThreads == (args->threadNo)){
         for( int k = i ; k < i + bs ; k++){
           for( int l = j ; l < j + bs ; l++){
             int rowA = k;
             int colA = l;
             int rowB = l;
             int colB = N-1-k;
            *(( args -> arr ) + rowA + colA) += matA[rowA * N + colA] * matB[rowB * N + colB];
           }
         }
        }
      }
    }
   pthread_exit(0);
}
void multiThread(int N, int *matA, int *matB, int *output)
{
  // Setting the global varibles
   ::N = N;
   ::matA = matA;
   ::matB = matB;
   ::output = output;

   // Spawning the threads
   struct args_struct args[numOfThreads];
   pthread_t tids[numOfThreads];
   for(int i = 0 ; i < numOfThreads;i++)
   {
      args[i].threadNo = i;
      pthread_attr_t attr;
      pthread_attr_init(&attr);
      pthread_create(&tids[i],&attr,MultipleThreadCode,&args[i]);
   }

   //Joining the threads and after getting all the threads array result adding them to output array.
   for(int i = 0; i < numOfThreads ; i++){
       pthread_join(tids[i],NULL);
        for(int j = 0;j<2*N-1;j++){
         output[j] += args[i].arr[j];
       }
   }

}

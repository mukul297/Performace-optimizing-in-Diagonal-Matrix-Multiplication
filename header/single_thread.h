void singleThread(int N, int *matA, int *matB, int *output)
{
    /*In this code,  I am accessing the matA in row major order and matB in column major order.
     Adding the output array, after initialising it to zero.
    */
    // block size = 64B
   int bs = 16;
   for(int i = 0 ; i < N;i += bs)
   {
     for(int j = 0; j < N;j +=bs)
     {
       // In each block, multiplying the elements of matA and matB and adding them to output array.
         for(int k = i ; k < i + bs ; k++){
           for(int l = j ; l < j + bs ; l++){
             int rowA = N - 1 - l ;
             int colA = k ;
             int rowB = k ;
             int colB = l ;
             output[rowA + colA] += matA[rowA * N + colA] * matB[rowB * N + colB];
           }
         }
      }
   }
 }

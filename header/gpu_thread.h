// Create other necessary functions here
#define M 16
__global__ void DMM(int N,int *a,int *b,int *o){
  int idx = blockIdx.x*M + threadIdx.x;
  if(idx==2*N-1){
     return;
  }
  else{
  //Two cases:
  int sum = 0,n,rowA,colA,rowB,colB;
  if(idx<N){
    n = idx+1;
    for(int i = 0;i<n;i++){
       rowA = i;
       colA = idx-i;
       rowB = idx-i;
       colB = N-1-i;
       sum+=a[rowA*N+colA]*b[rowB*N+colB];
   }
 }
 else{
      n = 2*N-1-idx;
   for(int i = 0;i<n;i++){
       rowA = N-n+i;
       colA = N-1-i;
       rowB = N-1-i;
       colB = n-1-i;
       sum+=a[rowA*N+colA]*b[rowB*N+colB];
       }
     }
    o[idx] = sum;
    }
}

// Fill in this function
void gpuThread(int N, int *matA, int *matB, int *output)
{
  int *a,*b,*o;
  int size_ab = N*N*sizeof(int);
  int size_o = (2*N-1)*sizeof(int);
  cudaMalloc((void **)&a,size_ab);
  cudaMalloc((void **)&b,size_ab);
  cudaMalloc((void **)&o,size_o);

  cudaMemcpy(a,matA,size_ab,cudaMemcpyHostToDevice);
  cudaMemcpy(b,matB,size_ab,cudaMemcpyHostToDevice);

  DMM<<<((2*N+M-1)/M),M>>>(N,a,b,o);

  cudaError_t err = cudaGetLastError();
  if(err!=cudaSuccess)
    printf("Error: %s\n",cudaGetErrorString(err));

  cudaMemcpy(output,o,size_o,cudaMemcpyDeviceToHost);
  cudaFree(a);
  cudaFree(b);
  cudaFree(o);
}

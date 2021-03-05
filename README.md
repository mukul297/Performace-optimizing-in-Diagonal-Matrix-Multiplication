# Performace-optimizing-in-Diagonal-Matrix-Multiplication
We have to reduce the execution time for diagonal matrix multiplication. We can use many concepts like loop unrolling, loop nested optimization and many other things. 

## Problem Statement
Input: Two N*N matrices. N = 2^{K}, where K is a natural number.

Output: An array of length 2N-1.

Sample Input/Output:
![alt text](https://lh6.googleusercontent.com/0HmiZLTZmsc_3dYGPRjYfc1NaaqFG41gb6XmYJn977hmTXgM4cOO0E3Qm8bqealfK38=w1200-h630-p)

Three major activites that I have to perform:
1. Single-Threading DMM (CPU): Reduce the execution time of the DMM considering it as single thread. I have learnt many concepts like loop nested optimisation in this part.
2. Multi-Threading DMM (CPU): Implemented the above part in multi threading using pthreads library in C++. Checked the execution for different inputs of matrix size and calculated the speed up.
3. DMM in CUDA (GPU): In this part, I have implemented the DMM on GPU using the cuda programming language. Every element of the output vector is considered as a thread. They all are executed in parallel on different GPU thread blocks.



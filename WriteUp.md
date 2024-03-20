# Project 4: OpenMP and Hybrid Parallelism 

In this project, you will gain experience with the basics of shared-memory parallelism using OpenMP. 
You will also combine distributed- and shared-memory approaches by implementing hybrid parallelism with MPI and OpenMP. 
In addition to the course text book, you may wish to refer to the excellent OpenMP resource pages at <https://computing.llnl.gov/tutorials/openMP/>.

## Part 1: OpenMP Matrix-Matrix Multiplication (TODO: Jared and Jacob)

Consider the simple matrix-matrix multiplication,

```C
for i = 1, N
  for j = 1, N
    for k = 1, N
      C[i,j] += A[i,k] * B[k,j]
```

What strategies could you use to add parallelism using OpenMP threading to this kernel? Is each of the three loops threadable?

Now, let's implement so OpenMP loop parallelism.

1. Modify your MMM code from Project 1 to implement OpenMP threading by adding appropriate compiler directives to the outer loop of the MMM kernel. When compiling the OpenMP version of your code be sure to include the appropriate compiler flag (`-fopenmp` for GCC). Done!
2. Compute the time-to-solution of your MMM code for 1 thread (e.g., `export OMP_NUM_THREADS=1`) to the non-OpenMP version (i.e., compiled without the `-fopenmp` flag). Any matrix size `N` will do here. Does it perform as you expect? If not, consider the OpenMP directives you are using.

Running openMP version of matrix_mult.c on dev-amd20 produces these times when N = 5 for NUM_THREADS = 1
| Run Number | openMP MMM time (seconds) | non-openMP MMM (seconds) |
|---------|----------|----------|
|    1    |  0.00001 |    0.000001     |
|    2    |  0.00001 |    0.000001     |
|    3    |  0.000008 |    0.000000     |
|    4    |  0.00001 |    0.000001     |
|    5    |  0.000007 |    0.000001     |
|    6    |  0.000008 |    0.000001     |
|    7    |  0.000007 |    0.000001     |
|    8    |  0.000010 |    0.000000     |
|    9    |  0.000007 |    0.000001     |
|    10    |  0.000007 |    0.000001     |

At the moment, the non-openMP version of MMM is running faster than the openMP version. This is due to the overhead require to instantiate openMP and only using one thread for all the calculation. 

3. Perform a thread-to-thread speedup study of your MMM code either on your laptop or HPCC. Compute the total time to solution for a few thread counts (in powers of 2): `1,2,4,...T`, where T is the maximum number of threads available on the machine you are using. Do this for matrix sizes of `N=20,100,1000`.

In the chart below, NUM_THREADS = 1, N = 20
| Run Number | openMP MMM time (seconds) for NUM_THREADS = 1, N= 20 | openMP MMM time (seconds) for NUM_THREADS = 2, N= 20 | openMP MMM time (seconds) for NUM_THREADS = 4, N= 20
|---------|----------|----------| ---------- | 
|    1    | 0.000048   |    0.000084     |    0.000144    |
|    2    | 0.000050   |    0.000089     |    0.000148    | 
|    3    | 0.000053   |    0.000081     |      0.000142   |   
|    4    | 0.000045    |    0.000094     |     0.000163   |
|    5    | 0.000049    |    0.000112     |    0.000176   |

#TODO: This does not look right, there should be a speed up happening as the threads gets larger....

4. Plot the times-to-solution for the MMM for each value of `N` separately as functions of the the thread count `T`. Compare the scaling of the MMM for different matrix dimensions.
5. Verify that for the same input matrices that the solution does not depend on the number of threads.

## Part 2: Adding OpenMP threading to a simple MPI application (TODO: Berk and Cheng)

Take a look at the Hello World applications that we have used in past assignments that include basic MPI functionality. Modify one of these applications to include OpenMP. 

1. Wrap the print statements in an `omp parallel` region.
2. Make sure to modify the `MPI_Init` call accordingly to allow for threads! What level of thread support do you need?
3. Compile the code including the appropriate flag for OpenMP support. For a GCC-based MPI installation, this would be, e.g., `mpic++ -fopenmp hello.cpp`.
4. Run the code using 2 MPI ranks and 4 OpenMP threads per rank. To do this, prior to executing the run command, set the number of threads environment variable as `> export OMP_NUM_THREADS=4`. Then you can simply execute the application with the `mpiexec` command: `> mpiexec -n 2 ./a.out`.
5. Explain the output.

## Part 3: Hybrid Parallel Matrix Multiplication (TODO: Everyone)

Now, let's combine OpenMP and MPI functionality into a hybrid parallel version of the MMM. 

1. Add MPI to  you OpenMP MMM code by distributing the rows of one of the input matrices across MPI ranks. Have each MPI rank perform its portion of the MMM using OpenMP threading. Think very carefully about the structure of the main MMM loops! Once done, gather the resulting matrix on rank 0 and output the result. Verify that for the same input matrices the result does not depend on either the number of MPI ranks or the number of OpenMP threads per rank. 
2. On HPCC, carry out a performance study in which you vary the number of MPI ranks, the number of OpenMP threads per rank, and the matrix size. Make plots showing the times to solution for the various cases. Explain your results.

## What to turn in

To your git project repo, commit your final working code for the above exercises and a concise write-up including all plots, and detailed responses to the questions posed concerning your results. 

// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
 
// #define NUM_THREADS 5
 
// void *PrintHello(void *threadid)
// {
//     long* tid = (long*)(threadid);
//     printf("Hello World! It's me, thread #%ld!\n", *tid);
//     pthread_exit(NULL);
// }
 
// int main(int argc, char *argv[])
// {
//     pthread_t threads[NUM_THREADS];
//     int rc;
//     long t;
//     for (t = 0; t < NUM_THREADS; t++)
//     {
//         printf("In main: creating thread %ld\n", t);
//         rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);
//         if (rc)
//         {
//             printf("ERROR; return code from pthread_create() is %d\n", rc);
//             exit(-1);
//         }
//     }
//     /* Last thing that main() should do : main() 调用 pthread_exit 来等所有线程完成任务 */
//     pthread_exit(NULL);
// }


// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string>
 
// #define NUM_THREADS    8
 
// char *messages[NUM_THREADS];
// // std::string messages[NUM_THREADS];
// struct thread_data
// {
//     int thread_id;
//     int sum;
//     char *message;
//     // std::string message;
// } thread_data_array[NUM_THREADS];
 
// void *PrintHello(void *threadarg)
// {
//     int taskid, sum;
//     char *hello_msg;
//     // std::string hello_msg;
//     struct thread_data* my_data;
 
//     sleep(1);
//     my_data = (struct thread_data* ) threadarg;
//     taskid = my_data->thread_id;
//     sum = my_data->sum;
//     hello_msg = my_data->message;
//     printf("Thread %d: %s  Sum=%d\n", taskid, hello_msg, sum);
//     pthread_exit(NULL);
// }
 
// int main(int argc, char *argv[])
// {
//     pthread_t threads[NUM_THREADS];
//     int rc, t, sum;

//     sum = 0;
//     messages[0] = "English: Hello World!";
//     messages[1] = "French: Bonjour, le monde!";
//     messages[2] = "Spanish: Hola al mundo";
//     messages[3] = "Klingon: Nuq neH!";
//     messages[4] = "German: Guten Tag, Welt!";
//     messages[5] = "Russian: Zdravstvytye, mir!";
//     messages[6] = "Japan: Sekai e konnichiwa!";
//     messages[7] = "Latin: Orbis, te saluto!";
 
//     for (t = 0; t < NUM_THREADS; t++)
//     {
//         sum = sum + t;
//         thread_data_array[t].thread_id = t;
//         thread_data_array[t].sum = sum;
//         thread_data_array[t].message = messages[t];
//         printf("Creating thread %d\n", t);
//         rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_array[t]);
//         if (rc)
//         {
//             printf("ERROR; return code from pthread_create() is %d\n", rc);
//             exit(-1);
//         }
//     }
//     pthread_exit(NULL);
// }


// #include <stdlib.h>
// #include <pthread.h>
// #include <stdio.h>
// #include <math.h>
 
// #define NUM_THREADS 4
 
// void *BusyWork(void *t)
// {
//     int i;
//     long tid;
//     double result = 0.0;
//     tid = (long) t;
//     printf("Thread %ld starting...\n", tid);
//     for (i = 0; i < 1000000; i++)
//     {
//         result = result + sin(i) * tan(i);
//     }
//     printf("Thread %ld done. Result = %e\n", tid, result);
//     pthread_exit((void *) t);
//     // pthread_exit(NULL);
// }
 
// int main(int argc, char *argv[])
// {
//     pthread_t thread[NUM_THREADS];
//     pthread_attr_t attr;
//     int rc;
//     long t;
//     void *status;
// /* Initialize and set thread detached attribute */
//     pthread_attr_init(&attr);
//     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//     for (t = 0; t < NUM_THREADS; t++)
//     {
//         printf("Main: creating thread %ld\n", t);
//         rc = pthread_create(&thread[t], &attr, BusyWork, (void *) t);
//         if (rc)
//         {
//             printf("ERROR; return code from pthread_create() is %d\n", rc);
//             exit(-1);
//         }
//     }
 
// /* Free attribute and wait for the other threads */
//     pthread_attr_destroy(&attr);
 
 
//     for (t = 0; t < NUM_THREADS; t++)
//     {
//         rc = pthread_join(thread[t], &status);
//         if (rc)
//         {
//             printf("ERROR; return code from pthread_join() is %d\n", rc);
//             exit(-1);
//         }
//         printf("Main: completed join with thread %ld having a status of %ld\n", t, (long) status);
//     }
//     printf("Main: program completed. Exiting.\n");
 
//     pthread_exit(NULL);
// }

// #include <stdlib.h>
// #include <pthread.h>
// #include <stdio.h>
 
// #define NTHREADS 4
// #define N 1000
// #define MEGEXTRA 1000000
 
// pthread_attr_t attr;
 
// void *dowork(void *threadid)
// {
//     double A[N][N];
//     int i, j;
//     long tid;
//     size_t mystacksize;
 
//     tid = (long) threadid;
//     pthread_attr_getstacksize(&attr, &mystacksize);
//     printf("Thread %ld: stack size = %li bytes \n", tid, mystacksize);
//     mystacksize-= 1000000;
//     pthread_attr_setstacksize(&attr, mystacksize);
//     for (i = 0; i < N; i++)
//         for (j = 0; j < N; j++)
//             A[i][j] = ((i * j) / 3.452) + (N - i);
//     pthread_exit(NULL);
// }
 
// int main(int argc, char *argv[])
// {
//     pthread_t threads[NTHREADS];
//     size_t stacksize;
//     int rc;
//     long t;
 
//     pthread_attr_init(&attr);
//     pthread_attr_getstacksize(&attr, &stacksize);
//     printf("Default stack size = %li\n", stacksize);
//     stacksize = sizeof(double) * N * N + MEGEXTRA;
//     printf("Amount of stack needed per thread = %li\n", stacksize);
//     pthread_attr_setstacksize(&attr, stacksize);
//     printf("Creating threads with stack size = %li bytes\n", stacksize);
//     for (t = 0; t < NTHREADS; t++)
//     {
//         rc = pthread_create(&threads[t], &attr, dowork, (void *) t);
//         if (rc)
//         {
//             printf("ERROR; return code from pthread_create() is %d\n", rc);
//             exit(-1);
//         }
//     }
//     printf("Created %ld threads.\n", t);
//     pthread_exit(NULL);
// }

// // mutex 互斥锁
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
 
// /*   
// The following structure contains the necessary information  
// to allow the function "dotprod" to access its input data and 
// place its output into the structure.  This structure is 
// unchanged from the sequential version.
// */
 
// typedef struct
// {
//     double *a;
//     double *b;
//     double sum;
//     int veclen;
// } DOTDATA;
 
// /* Define globally accessible variables and a mutex */
 
// #define NUMTHRDS 4
// #define VECLEN 100000
// DOTDATA dotstr;
// pthread_t callThd[NUMTHRDS];
// pthread_mutex_t mutexsum;
 
// /*
// The function dotprod is activated when the thread is created.
// As before, all input to this routine is obtained from a structure 
// of type DOTDATA and all output from this function is written into
// this structure. The benefit of this approach is apparent for the 
// multi-threaded program: when a thread is created we pass a single
// argument to the activated function - typically this argument
// is a thread number. All  the other information required by the 
// function is accessed from the globally accessible structure. 
// */
 
// void *dotprod(void *arg)
// {
 
// /* Define and use local variables for convenience */
 
//     int i, start, end, len;
//     long offset;
//     double mysum, *x, *y;
//     offset = (long) arg;
 
//     len = dotstr.veclen;
//     start = offset * len;
//     end = start + len;
//     x = dotstr.a;
//     y = dotstr.b;
 
// /*
// Perform the dot product and assign result
// to the appropriate variable in the structure. 
// */
//     mysum = 0;
//     for (i = start; i < end; i++)
//     {
//         mysum += (x[i] * y[i]);
//     }
 
// /*
// Lock a mutex prior to updating the value in the shared
// structure, and unlock it upon updating.
// */
//     // pthread_mutex_lock(&mutexsum);
//     dotstr.sum += mysum;
//     printf("Thread %ld did %d to %d: mysum=%f global sum=%f\n", offset, start,
//            end, mysum, dotstr.sum);
//     // pthread_mutex_unlock(&mutexsum);

//     /* 如果把mutex去掉，会出现这种情况
//     Thread 0 did 0 to 100000: mysum=100000.000000 global sum=100000.000000
//     Thread 2 did 200000 to 300000: mysum=100000.000000 global sum=200000.000000
//     Thread 3 did 300000 to 400000: mysum=100000.000000 global sum=300000.000000
//     Thread 1 did 100000 to 200000: mysum=100000.000000 global sum=300000.000000
//     Sum =  300000.000000 
//     */

//     pthread_exit((void *) 0);
// }
 
// /* 
// The main program creates threads which do all the work and then print out result 
// upon completion. Before creating the threads, The input data is created. Since 
// all threads update a shared structure, we need a mutex for mutual exclusion. 
// The main thread needs to wait for all threads to complete, it waits for each one 
// of the threads. We specify a thread attribute value that allow the main thread to
// join with the threads it creates. Note also that we free up handles  when they
// are no longer needed.
// */
 
// int main(int argc, char *argv[])
// {
//     long i;
//     double *a, *b;
//     void *status;
//     pthread_attr_t attr;
 
// /* Assign storage and initialize values */
 
//     a = (double *) malloc(NUMTHRDS * VECLEN * sizeof(double));
//     b = (double *) malloc(NUMTHRDS * VECLEN * sizeof(double));
 
//     for (i = 0; i < VECLEN * NUMTHRDS; i++)
//     {
//         a[i] = 1;
//         b[i] = a[i];
//     }
 
//     dotstr.veclen = VECLEN;
//     dotstr.a = a;
//     dotstr.b = b;
//     dotstr.sum = 0;
 
//     pthread_mutex_init(&mutexsum, NULL);
 
// /* Create threads to perform the dotproduct  */
//     pthread_attr_init(&attr);
//     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
//     for (i = 0; i < NUMTHRDS; i++)
//     {
//         /* Each thread works on a different set of data.
//          * The offset is specified by 'i'. The size of
//          * the data for each thread is indicated by VECLEN.
//          */
//         pthread_create(&callThd[i], &attr, dotprod, (void *) i);
//     }
 
//     pthread_attr_destroy(&attr);
// /* Wait on the other threads */
 
//     for (i = 0; i < NUMTHRDS; i++)
//     {
//         pthread_join(callThd[i], &status);
//     }
// /* After joining, print out the results and cleanup */
 
//     printf("Sum =  %f \n", dotstr.sum);
//     free(a);
//     free(b);
//     pthread_mutex_destroy(&mutexsum);
//     pthread_exit(NULL);
// }

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define NUM_THREADS  2
#define TCOUNT 20
#define COUNT_LIMIT1 10
#define COUNT_LIMIT2 145
 
int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;
 
void *inc_count(void *t)
{
    int i;
    long my_id = (long) t;
 
    for (i = 0; i < TCOUNT; i++)
    {
        pthread_mutex_lock(&count_mutex);
        printf("inc_count--locking mutex\n");
        count++;
 
        /* 
        Check the value of count and signal waiting thread when condition is
        reached.  Note that this occurs while mutex is locked. 
        */
        if (count == COUNT_LIMIT1 || count == COUNT_LIMIT2)
        {
            printf("inc_count(): thread %ld, count = %d  Threshold reached. ",
                   my_id, count);
            pthread_cond_signal(&count_threshold_cv);
            printf("Just sent signal.\n");
        }
        pthread_mutex_unlock(&count_mutex);
        printf("inc_count(): thread %ld, count = %d, unlocking mutex\n", my_id, count);
        /* Do some work so threads can alternate on mutex lock */
        sleep(1);
    }
    pthread_exit(NULL);
}
 
void *watch_count(void *t)
{
    long my_id = (long) t;
 
    printf("Starting watch_count(): thread %ld\n", my_id);
 
    /*
    Lock mutex and wait for signal.  Note that the pthread_cond_wait routine
    will automatically and atomically unlock mutex while it waits. 
    Also, note that if COUNT_LIMIT is reached before this routine is run by
    the waiting thread, the loop will be skipped to prevent pthread_cond_wait
    from never returning.
    */
    pthread_mutex_lock(&count_mutex);
    printf("watch_count--locking mutex\n");
    while (count < COUNT_LIMIT2)
    {
        printf("watch_count(): thread %ld Count= %d. Going into wait...\n", my_id, count);
        /*
        pthread_cond_wait(&count_threshold_cv, &count_mutex)
        当前线程会释放 count_mutex 互斥锁，并进入等待状态，
        直到其他线程发出信号（通过 pthread_cond_signal 或 pthread_cond_broadcast）表明条件满足。
        当条件满足并且有线程调用 pthread_cond_signal 或 pthread_cond_broadcast 唤醒等待线程时，
        当前线程会重新获取 count_mutex 互斥锁，然后继续执行。
        */
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count(): thread %ld Condition signal received. Count= %d\n", my_id,
               count);
        printf("watch_count(): thread %ld Updating the value of count...\n", my_id, count);
        count += 125;
        printf("watch_count(): thread %ld count now = %d.\n", my_id, count);
    }
    pthread_mutex_unlock(&count_mutex);
    printf("watch_count(): thread %ld Unlocking mutex.\n", my_id);
    pthread_exit(NULL);
}
 
int main(int argc, char *argv[])
{
    int i;
    long t1 = 1, t2 = 2;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
 
    /* Initialize mutex and condition variable objects */
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold_cv, NULL);
 
    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, inc_count, (void *) t1);
    pthread_create(&threads[1], &attr, watch_count, (void *) t2);
    // pthread_create(&threads[2], &attr, inc_count, (void *) t3);
 
    /* Wait for all threads to complete */
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Main(): Waited and joined with %d threads. Final value of count = %d. Done.\n",
           NUM_THREADS, count);
 
    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit(NULL);
 
}
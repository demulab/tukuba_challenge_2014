//----Thread.cpp----
#include"Thread.h"
#include<iostream>


using namespace std;
Thread::Thread()
{
    threadid = 0;
    runnable = false;
    pthread_mutex_init(&mutex, NULL);
}

Thread::~Thread()
{
    usleep(1000);   
    pthread_mutex_destroy( &mutex );
    cout << "Threadデストラクタ" << endl;
    runnable = false;
    join();
}

void* Thread::start_routine(void* arg)
{
    if(arg == 0)
        return 0;
    Thread* p = (Thread*)arg;
    p->Run();
    return arg;
}

void Thread::lock() {
    pthread_mutex_lock(&mutex);
}
void Thread::unlock() {
    pthread_mutex_unlock(&mutex);
}

int Thread::start()
{
    lock();
    if(runnable == true) return -1;
    {
        runnable = true;
    }
    unlock();


    return::pthread_create(&threadid, 0, Thread::start_routine, this);
}
void Thread::stop() {
    lock();
    {
        runnable = false;
    }
    unlock();
    usleep(10000);   
}

//success = 0
//failure =
//ESRCH th で指定された ID に対応するスレッドが見つからなかった。
//EINVAL th で指定されたスレッドはすでにデタッチされている。
//EINVAL すでに別のスレッドがスレッド th の終了を待っている。
//EDEADLK 引数 th が呼び出しスレッドを指している。
int Thread::join()
{
    if(threadid != 0)
    	return::pthread_join(threadid, 0);
}

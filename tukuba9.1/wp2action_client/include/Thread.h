//-------Thread.hpp-----------
#pragma once
#include<pthread.h>
#include<iostream>
class Thread
{
private:
    static void* start_routine(void *);
    bool runnable;
    pthread_mutex_t mutex;
public:
    Thread();
    virtual ~Thread();
    void lock();
    void unlock();

    int start();

    int join();
   
    void stop();

protected:
    virtual void *Run()=0;
    pthread_t threadid;
    bool isRunnable() {
        return runnable;
    }

};





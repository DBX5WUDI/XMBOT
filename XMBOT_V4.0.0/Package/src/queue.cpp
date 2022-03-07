#include "queue.h"

Queue queue;

Queue::Queue()
{
    arr[0]=0;
    head=0;
    tail=0;
}

unsigned char Queue::getData(void)
{
    unsigned char data;
    data = arr[head];
    head++;
    if(head >= QUEUE_SIZE) head=0;
    return data;
}

void Queue::putData(unsigned char ch)
{
    arr[tail] = ch;
    tail++;
    if(tail >= QUEUE_SIZE) tail=0;
}

unsigned char Queue::emptyCheck(void)
{
    if( head == tail )
        return 1;
    else
        return 0;
}

unsigned char Queue::fullCheck(void)
{
    if( tail + 1 == head )
        return 1;
    else
        return 0;
}


#include "mbed.h"
#include "mbed_events.h"
#include "CircBuffer.h"



#define MAX_BUF_SIZE 128

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;
InterruptIn input(p21);
Serial pc(USBTX, USBRX);
Timer timer;
DigitalOut led(LED1);


CircBuffer<int, MAX_BUF_SIZE> buf;


void sendToBrowser() {
    return;
}

void rise_handler() {
    int ts = timer.read_us();
    led = !led;
    queue.event(sendToBrowser);
    //pc.printf("%d\r\n", ts);
}

int main() {
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    timer.start();
    input.rise(rise_handler);
    while(1) {
    }
}
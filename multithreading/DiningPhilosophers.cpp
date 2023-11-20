#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

const int N = 5; // number of philosophers
mutex forks[N]; // mutexes for forks
mutex cout_mutex; // mutex for cout
bool stop = false; // flag to stop philosophers

void philosopher(int i) {
    while (!stop) {
        cout_mutex.lock();
        cout << "Philosopher " << i << " is thinking.\n";
        cout_mutex.unlock();
        if (i == N - 1) { // the last philosopher picks up the right fork first
            forks[0].lock();
            forks[i].lock();
        }
        else { // the other philosophers pick up the left fork first
            forks[i].lock();
            forks[(i + 1) % N].lock();
        }
        cout_mutex.lock();
        cout << "Philosopher " << i << " is eating.\n";
        cout_mutex.unlock();
        forks[i].unlock();
        forks[(i + 1) % N].unlock();
    }
}

void timer() {
    this_thread::sleep_for(chrono::seconds(5));
    stop = true;
}

int main() {
    // create threads for philosophers
    thread philosophers[N];
    for (int i = 0; i < N; i++) {
        philosophers[i] = thread(philosopher, i);
    }
    // create timer thread
    thread t(timer);
    // join threads
    for (int i = 0; i < N; i++) {
        philosophers[i].join();
    }
    t.join();
    return 0;
}
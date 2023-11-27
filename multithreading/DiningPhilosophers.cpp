#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;



const int N = 5; // number of philosophers
mutex forks[N]; // mutexes for forks
mutex cout_mutex; // mutex for cout
bool stop = false; // flag to stop philosophers
vector<int> eat_count(N, 0); // count of eating times for each philosopher
vector<int> think_count(N, 0); // count of thinking times for each philosopher
int semaphore = N - 1; // semaphore to control number of philosophers eating
condition_variable cv; // condition variable for the semaphore
mutex semaphore_mutex; // mutex for the semaphore

void philosopher(int i) {
    try {
        while (!stop) {
            cout_mutex.lock();

            // cout << "Philosopher " << i << " is thinking.\n";

            think_count[i]++; // increment thinking count
            cout_mutex.unlock();

            unique_lock<mutex> semaphore_lock(semaphore_mutex);
            cv.wait(semaphore_lock, [&]() { return semaphore > 0; }); // wait for the semaphore
            --semaphore; // decrement the semaphore
            semaphore_lock.unlock();

            // Determine the order of forks for each philosopher
            int first_fork = min(i, (i+1)%N);
            int second_fork = max(i, (i+1)%N);

            unique_lock<mutex> lock1(forks[first_fork], defer_lock);
            unique_lock<mutex> lock2(forks[second_fork], defer_lock);

            lock(lock1, lock2); // lock both forks at once

            cout_mutex.lock();

            // cout << "Philosopher " << i << " is eating.\n";
            
            eat_count[i]++; // increment eating count
            cout_mutex.unlock();

            lock1.unlock(); // release the first fork
            lock2.unlock(); // release the second fork

            semaphore_lock.lock();
            ++semaphore; // increment the semaphore
            cv.notify_one(); // notify one waiting philosopher
        }
    } catch (const exception& e) {
        cerr << "Exception in philosopher " << i << ": " << e.what() << '\n';
    }
}

void timer() {
    this_thread::sleep_for(chrono::seconds(3));
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

    // print report
    for (int i = 0; i < N; i++) {
        cout << "Philosopher " << i << " ate " << eat_count[i] << " times and thought " << think_count[i] << " times.\n";
    }

    return 0;
}
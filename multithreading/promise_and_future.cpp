#include <iostream>
#include <thread>
#include <future>

//program that uses multithreading to compute the expression (A+B) * (C+D) with two different threads for addition of the variables 

int result = 0; // shared variable to store the final result
int sum1 = 0; // variable to store the sum of A+B
int sum2 = 0; // variable to store the sum of C+D

// function to compute A+B on a thread
void addAB(std::promise<int> p, int a, int b) {
    p.set_value(a + b); // set the value of promise
}

// function to compute C+D on a thread
void addCD(std::promise<int> p, int c, int d) {
    p.set_value(c + d); // set the value of promise
}

int main() {
    int a = 10, b = 20, c = 30, d = 40; // input values
    std::promise<int> p1, p2; // create two promises
    std::future<int> f1 = p1.get_future(), f2 = p2.get_future(); // get futures from promises
    std::thread t1(addAB, std::move(p1), a, b); // create a thread to run addAB(a, b)
    std::thread t2(addCD, std::move(p2), c, d); // create a thread to run addCD(c, d)
    t1.join(); // wait for t1 to finish
    t2.join(); // wait for t2 to finish
    sum1 = f1.get(); // get the value from future f1
    sum2 = f2.get(); // get the value from future f2
    result = sum1 * sum2;
    std::cout << "(A+B) * (C+D) = " << result << std::endl;
    return 0;
}

#include <iostream>
#include <thread>

//program that uses multithreading to compute the expression (A+B) * (C+D) with two different threads for addition of the variables 

int result = 0; // shared variable to store the final result
int sum1 = 0; // variable to store the sum of A+B
int sum2 = 0; // variable to store the sum of C+D

// function to compute A+B on a thread
void addAB(int a, int b) {
    sum1 = a + b; // local variable to store the sum
    std::cout << "A+B = " << sum1 << std::endl;
}

// function to compute C+D on a thread
void addCD(int c, int d) {
    sum2 = c + d; // local variable to store the sum
    std::cout << "C+D = " << sum2 << std::endl;
}

int main() {
    int a = 10, b = 20, c = 30, d = 40; // input values
    std::thread t1(addAB, a, b); // create a thread to run addAB(a, b)
    std::thread t2(addCD, c, d); // create a thread to run addCD(c, d)
    t1.join(); // wait for t1 to finish
    t2.join(); // wait for t2 to finish
    result = sum1 * sum2;
    std::cout << "(A+B) * (C+D) = " << result << std::endl;
    return 0;
}

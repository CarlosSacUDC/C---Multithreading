#include <iostream>
#include <thread>

//program that uses multithreading to compute the expression (A+B) * (C+D) with two different threads for addition of the variables 

int result = 0; // shared variable to store the final result

// function to compute A+B on a thread
void addAB(int a, int b) {
    int sum = a + b; // local variable to store the sum
    std::cout << "A+B = " << sum << std::endl;
   
    result += sum; // update the shared variable
    
}

// function to compute C+D on a thread
void addCD(int c, int d) {
    int sum = c + d; // local variable to store the sum
    std::cout << "C+D = " << sum << std::endl;
    result += sum; // update the shared variable
}

int main() {
    int a = 10, b = 20, c = 30, d = 40; // input values
    std::thread t1(addAB, a, b); // create a thread to run add(a, b)
    std::thread t2(addCD, c, d); // create a thread to run add(c, d)
    t1.join(); // wait for t1 to finish
    t2.join(); // wait for t2 to finish
    result *= result; // compute (A+B) * (C+D)
    std::cout << "(A+B) * (C+D) = " << result << std::endl;
    return 0;
}

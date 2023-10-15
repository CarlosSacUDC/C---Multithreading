#include <iostream>
#include <future>

//program that uses multithreading to compute the expression (A+B) * (C+D) with two different threads for addition of the variables 

int result = 0; // shared variable to store the final result
int sum1 = 0; // variable to store the sum of A+B
int sum2 = 0; // variable to store the sum of C+D

// function to compute the sum of two numbers
auto add = [] (int x, int y, std::string s) {
    return x + y;
};

int main() {
    std::cout <<"Asynchronous Communication"<< std::endl;
    int a = 10, b = 20, c = 30, d = 40; // input values
    // create two async tasks to run add(a, b) and add(c, d) and get the futures
    std::future<int> f1 = std::async(std::launch::deferred, add, a, b, "AB");
    std::future<int> f2 = std::async(std::launch::deferred, add, c, d, "CD");
    // get the values from futures f1 and f2
    sum1 = f1.get(); 
    sum2 = f2.get(); 
    result = sum1 * sum2;
    std::cout << "(A+B) * (C+D) = " << result << std::endl;
    return 0;
}

#include <iostream>
#include <thread>
#include <future>

int result = 0; 
int sum1 = 0;
int sum2 = 0; 

// lambda expression to compute the sum of two numbers and set the value of a promise
auto add = [] (std::promise<int> p, int x, int y, std::string s) {
    std::cout << s << " is running on thread " << std::this_thread::get_id() << std::endl;
    p.set_value(x + y); // set the value of promise
};

int main() {
    std::cout <<"Lambda Expressions"<< std::endl;
    int a = 10, b = 20, c = 30, d = 40;
    std::promise<int> p1, p2; // create two promises
    std::future<int> f1 = p1.get_future(), f2 = p2.get_future(); // get futures from promises
    // create a thread to run add(a, b, "AB") and set the value of promise p1
    std::thread t1(add, std::move(p1), a, b, "AB");
    // create a thread to run add(c, d, "CD") and set the value of promise p2
    std::thread t2(add, std::move(p2), c, d, "CD");
    t1.join(); // wait for t1 to finish
    t2.join(); // wait for t2 to finish
    sum1 = f1.get(); // get the value from future f1
    sum2 = f2.get(); // get the value from future f2
    result = sum1 * sum2;
    std::cout << "(A+B) * (C+D) = " << result << std::endl;
    return 0;
}

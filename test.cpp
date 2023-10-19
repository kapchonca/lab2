#include <iostream>
#include <chrono>

int main() {
    // Start the timer
    auto start = std::chrono::steady_clock::now();

    // Simulate some work or code execution
    for (int i = 0; i < 100000; i++) {
        for (int j = 0; j < 10000; j++) {

        }
    }

    // Stop the timer
    auto end = std::chrono::steady_clock::now();

    // Calculate the elapsed time in seconds
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    int i = elapsedTime.count();

    std::cout << "Elapsed time: " << elapsedTime.count() << " seconds" << std::endl << i;

    return 0;
}

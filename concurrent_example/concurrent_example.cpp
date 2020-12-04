#include <iostream>
#include <unistd.h>
#include <thread>
#include "progresscpp/ProgressBar.hpp"

/*
 * Function which is thrown as thread
 */
void workerThread(int total, progresscpp::ProgressBar& progressBar) {
    for (int i = 0; i < total; i++) {
        ++progressBar; // record the tick

        usleep(200); // simulate work

        // display the bar only at certain steps
        if (i % 10 == 0)
            progressBar.display();
    }
}

/* Example usage of ProgressBar by multiple threads */
int main() {
    const int partial = 1000;

    /*
     * Define a progress bar that has a total of 10000,
     * a width of 70, shows `#` to indicate completion
     * and a dash '-' for incomplete
     */
    progresscpp::ProgressBar progressBar(10 * partial, 70, '#', '-');

    /*
     * Throw ten threads which access the same ProgressBar 
     * instance concurrently
     */
    std::thread workers[10];
    for (int i = 0; i < 10; i++) {
    	workers[i] = std::thread(workerThread, partial, std::ref(progressBar));
    }

    /*
     * Wait for threads to finish the work
     */
    for (int i = 0; i < 10; i++) {
    	workers[i].join();
    }

    // tell the bar to finish
    progressBar.done();

    std::cout << "Done!" << std::endl;
    return 0;
}

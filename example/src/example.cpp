#include <iostream>
#include <unistd.h>
#include "progresscpp/ProgressBar.hpp"

/* Example usage of ProgressBar */
int main() {
    const int total = 10000;

    /*
     * Define a progress bar that has a total of 10000,
     * a width of 70, shows `#` to indicate completion
     * and a dash '-' for incomplete
     */
    progresscpp::ProgressBar progressBar(total, 70, '#', '-');

    for (int i = 0; i < total; i++) {
        ++progressBar; // record the tick

        usleep(200); // simulate work

        // display the bar only at certain steps
        if (i % 10 == 0)
            progressBar.display();
    }

    // tell the bar to finish
    progressBar.done();

    std::cout << "Done!" << std::endl;
    return 0;
}

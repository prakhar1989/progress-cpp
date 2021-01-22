#pragma once

/*
 * from progress-cpp by prakhar1989 (@ref https://github.com/prakhar1989/progress-cpp)
 * added throttling by sikbrad @ref https://github.com/sikbrad/progress-cpp-throttled.git
 */

#include <chrono>
#include <iostream>
#include <math.h>

namespace progresscpp {
class ProgressBar {
private:
    unsigned int ticks = 0;

    const unsigned int total_ticks;
    const unsigned int bar_width = 70;
    const char complete_char = '=';
    const char incomplete_char = ' ';
    const std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

private:
    int prev_progress_percent = 0;
    int throttle_progress = 5;
    int throttle_counter = 0;

public:
    ProgressBar(unsigned int total, unsigned int width, char complete, char incomplete, int throttle) :
            total_ticks{total}, bar_width{width}, complete_char{complete}, incomplete_char{incomplete}, throttle_progress{throttle} {}

    ProgressBar(unsigned int total, unsigned int width, char complete, char incomplete) :
            total_ticks{total}, bar_width{width}, complete_char{complete}, incomplete_char{incomplete} {}

    ProgressBar(unsigned int total, unsigned int width) : total_ticks{total}, bar_width{width} {}

    ProgressBar(unsigned int total) : total_ticks{total} {}

    unsigned int operator++() { return ++ticks; }
    
    void UnsetThrottle(){
        throttle_progress = 0;
    }

    void _display() const {
    }

    void display() {
        float progress = (float) (ticks+1) / total_ticks;
        int curr_progress_percent = ceil(100 * progress);
        bool is_print = false;

        //dont limit if set as zero
        if(throttle_progress == 0){
            is_print = true;
        }
        //if limit is set,
        else if(prev_progress_percent > 0){

            //detect percentage change
            if(prev_progress_percent < curr_progress_percent){
                throttle_counter++;
            }

            //when throttle exceeds, then print and reset the counter.
            if(throttle_counter >= throttle_progress){
                is_print = true;
                throttle_counter = 0;
            }
        }

        if(is_print){
            int pos = (int) (bar_width * progress);

            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();

            std::cout << "[";

            for (int i = 0; i < bar_width; ++i) {
                if (i < pos) std::cout << complete_char;
                else if (i == pos) std::cout << ">";
                else std::cout << incomplete_char;
            }
            std::cout << "] " << int(progress * 100.0) << "% "
                      << float(time_elapsed) / 1000.0 << "s\r";
            std::cout.flush();
        }

        //save status
        prev_progress_percent = curr_progress_percent;
    }

    void done() {
        display();
        std::cout << std::endl;
    }
};
}

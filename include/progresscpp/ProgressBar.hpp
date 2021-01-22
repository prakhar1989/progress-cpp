#pragma once

/*
 * from progress-cpp by prakhar1989 (@ref https://github.com/prakhar1989/progress-cpp)
 * added throttling by sikbrad @ref https://github.com/sikbrad/progress-cpp-throttled.git
 */

#include <chrono>
#include <iostream>
#include <math.h>
#include <iomanip>

namespace progresscpp {
class ProgressBar {
private:
    unsigned int ticks = 0;

    const unsigned int total_ticks;
    const unsigned int bar_width = 70;
    const char complete_char = '=';
    const char incomplete_char = ' ';
    const std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

public:
    int throttle_progress = 5;
    bool is_eta_enabled = true;
    bool is_spinner_enabled = true;

private:
    int prev_progress_percent = 0;
    int throttle_counter = 0;
    int count_display = 0;

public:
    bool is_displayed = false;

public:
    ProgressBar(unsigned int total, unsigned int width, char complete, char incomplete, int throttle, bool is_eta) :
            total_ticks{total}, bar_width{width}, complete_char{complete}, incomplete_char{incomplete}, throttle_progress{throttle}, is_eta_enabled{is_eta} {}

    ProgressBar(unsigned int total, unsigned int width, char complete, char incomplete) :
            total_ticks{total}, bar_width{width}, complete_char{complete}, incomplete_char{incomplete} {}

    ProgressBar(unsigned int total, unsigned int width) : total_ticks{total}, bar_width{width} {}

    ProgressBar(unsigned int total) : total_ticks{total} {}

    unsigned int operator++() { return ++ticks; }

    void _display() const {
    }

    bool display() {
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
                ++throttle_counter;

                //when throttle exceeds, then print and reset the counter.
                if(throttle_counter >= throttle_progress){
                    is_print = true;
                    throttle_counter = 0;
                }
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
            std::cout << "] ";

            std::cout << "[" << int(progress * 100.0) << "% ";
            std::cout << std::fixed << std::setprecision(2) << float(time_elapsed) / 1000.0 << "s";
            std::cout << "]";

            if(is_eta_enabled){
                float expected = float(time_elapsed) / progress;
                float eta = abs(expected - time_elapsed);
                std::cout << " eta " <<  std::fixed << std::setprecision(2) << float(eta) / 1000.0 << "s ";
            }

            if(is_spinner_enabled){
                //followed character spinner style of etaprogress(python)
                //@ref https://pypi.org/project/etaprogress/
                const int total_pinchar = 4;
                int idx_spinchar = count_display % total_pinchar;
                char spinchar = ' ';
                switch(idx_spinchar){
                    case 0:
                        spinchar = '-'; break;
                    case 1:
                        spinchar = '\\'; break;
                    case 2:
                        spinchar = '|'; break;
                    case 3:
                        spinchar = '/'; break;
                    default:
                        break;
                }
                std::cout << " " <<  spinchar;
            }


            std::cout << " \r";
            std::cout.flush();

            is_displayed = true;
            count_display++;
        }else{
            is_displayed = false;
        }

        //save status
        prev_progress_percent = curr_progress_percent;

        return is_displayed;
    }

    void done() {
        display();
        std::cout << std::endl;
    }
};
}

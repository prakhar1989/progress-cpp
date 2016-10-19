#ifndef PROGRESSBAR_PROGRESSBAR_HPP
#define PROGRESSBAR_PROGRESSBAR_HPP

#include <chrono>
#include <iostream>

class ProgressBar {
private:
    /* ticks completed */
    int current;

    const int barTotal;
    const int barWidth;
    const char completeChar;
    const char incompleteChar;
    const std::chrono::steady_clock::time_point start_time;
public:
    ProgressBar(int total, int width):
            barTotal {total}, barWidth {width}, completeChar {'='},
            incompleteChar {' '}, start_time {std::chrono::steady_clock::now()}
    {
        current = 0;
    }
    ProgressBar(int total, int width, char complete, char incomplete) :
            barTotal {total}, barWidth {width}, completeChar {complete},
      incompleteChar {incomplete}, start_time {std::chrono::steady_clock::now()}
    {
        current = 0;
    }

    int operator++()
    {
        return ++current;
    }

    void display()
    {
        float progress = (float) current / barTotal;
        int pos = (int) (barWidth * progress);

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count();

        std::cout << "[";

        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << completeChar;
            else if (i == pos) std::cout << ">";
            else std::cout << incompleteChar;
        }
        std::cout << "] " << int(progress * 100.0) << "% "
                  << float(time_elapsed) / 1000.0 << "s\r";
        std::cout.flush();
    }

    void done()
    {
        display();
        std::cout << std::endl;
    }
};

#endif //PROGRESSBAR_PROGRESSBAR_HPP

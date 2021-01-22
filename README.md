Progress-CPP-Throttled-HeaderOnly
===



### What's better, TLDR

By printing progress bar only when it is needed, performance got better.

Added ETA(Estimated time of arrival), and Spinner.

It is just one header file, like original.



## What's new, and why.

### Throttling added

Displaying progress is important, but when printing too much console from your program, your program slows down. That's what exactly happened to me when using original library. So I added throttling feature, to print the progress bar only when it is needed. When `throttle_progress` is set to 1(default), then program will display the progress bar only when percentage changes. If we set `throttle_progress` larger than 1, then it will skip printing progress bar until added progress percentage gets larger than `throttle_progress` .

### ETA added

Time estimation is added. It can be enabled/disabled by variable `is_eta_enabled`

### Spinner added

Spinner is added. It can be enabled/disabled by variable `is_spinner_enabled`



## Original README of Progress-CPP

A flexible ASCII progress bar for your console based C++ projects.

### Usage
Progress is a header-only library and can be used by simply including the `ProgressBar.hpp` header file.

The bar takes the following options at initialization
- Limit: the total number of ticks that need to be completed
- Width: width of the bar
- Complete Char: the character to indicate completion (defaults to `=`)
- Incomplete Char: the character to indicate pending. (defaults to ' ')

```c++
#include "ProgressBar.hpp"

int main() {

    const int limit = 10000;

    // initialize the bar
    ProgressBar progressBar(limit, 70);

    for (int i = 0; i < limit; i++) {
        // record the tick
        ++progressBar;

        // display the bar
        progressBar.display();
    }

    // tell the bar to finish
    progressBar.done();
}
```
The above code results in the following output

```
[===================>                                                 ] 29% 0.821s
```

### Example
Refer to [example.cpp](example/src/example.cpp) file for an example usage. To run it,

```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./ProgressBar
```

Or without `cmake`
```
$ g++ -O3 -I. main.cpp -Wall -std=c++11 -o ProgressBar
$ ./ProgressBar
```

### CMake configuration
Cmake and project layout is inspired by [github.com/TheLartians/ModernCppStarter](https://github.com/TheLartians/ModernCppStarter).

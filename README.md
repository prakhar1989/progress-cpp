Progress-CPP
===

A flexible ASCII progress bar for your console based C++ projects.

### Usage
Progress is a header-only library and can be used by simply including the `ProgressBar.hpp` header file.

The bar takes the following options at initialization
- Limit: the total number of ticks that need to be completed
- Width: width of the bar
- Complete Char: the character to indicate completion
- Incomplete Char: the character to indicate pending.

```c++
#include "ProgressBar.hpp"

int main() {

    const int limit = 10000;

    // initialize the bar
    ProgressBar progressBar(limit, 70, '=', ' ');

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
Refer to [main.cpp](main.cpp) file for an example usage.

### License
MIT

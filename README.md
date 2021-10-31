# RcppClock

RcppClock is a simple wrapper for `std::chrono::high_resolution_clock` that makes benchmarking Rcpp code easy.

Install RcppClock from CRAN.

```
install.packages("RcppClock")
library(RcppClock)
?RcppClock
```

## The Rcpp side of things

Load the RcppClock header into your R session using `library(RcppClock)`, but more commonly you will load the header library into Rcpp functions:

```
//[[Rcpp::depends(RcppClock)]]
#include <RcppClock.h>
#include <thread>

//[[Rcpp::export]]
void sleepy(){
  Rcpp::Clock clock;
  
  // start the timer
  clock.tick("short_nap");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));  
  
  // stop the previous timer and start a new timer
  clock.tick("long_nap");
  std::this_thread::sleep_for(std::chrono::milliseconds(100));  

  // stop the previous timer, don't start a new timer
  clock.tock();
  
  // send the times to the R global environment variable, named "naptimes"
  clock.fetch("naptimes");
}
```

`.tick()` starts the timer for one function and stops it for the preceding function (if applicable). 

`.tock()` simply stops the timer for the preceding function and does not re-start it. 

`.fetch()` captures the times up to that point and creates a variable in the global environment with the specified name.

## The R side of things

On the R end, we can now do stuff with the "naptimes" variable that was created in the above Rcpp function:

```{R}
sleepy()
# global variable "naptimes" is now created in the environment
naptimes
```

```{R}
summary(naptimes, units = "us")
```

```{R}
plot(naptimes)
```

## Timing multiple replicates

If a `.tick()` with the same name is called multiple times, RcppClock automatically groups the results.

The following code reproduces the `?fibonacci` function example included in the RcppClock package:

```
int fib(int n) {
  return ((n <= 1) ? n : fib(n - 1) + fib(n - 2));
}

//[[Rcpp::export]]
void fibonacci(std::vector<int> n, int reps = 10) {
  Rcpp::Clock clock;
  
  while(reps-- > 0){
    for(auto number : n){
      clock.tick("fib" + std::to_string(number));
      fib(number);
    }
  }
  clock.tock();
  clock.write("clock");
}
```

On the R end, we'll get an object named "clock":

```{R}
fibonacci(n = c(25:35), reps = 10)
# global variable "clock" is created in the R global environment
clock
```

```{R}
plot(clock)
```

## Limitations

* Not compatible with timing inside multi-threaded loops.
* Processes taking less than 1 microsecond cannot be reliably timed.

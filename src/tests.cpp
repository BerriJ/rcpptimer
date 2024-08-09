#include <thread>
#include <chrono>
#include <rcpptimer.h>
using namespace Rcpp;

//[[Rcpp::export]]
void test_default()
{
  Rcpp::Timer timer;
  Rcpp::Timer::ScopedTimer scoped_timer(timer);
  timer.tic();
  std::this_thread::sleep_for(std::chrono::nanoseconds(5));
  timer.toc();
}

//[[Rcpp::export]]
List test_update()
{
  Rcpp::Timer timer;
  timer.autoreturn = false;
  List L = List::create();
  {
    Rcpp::Timer::ScopedTimer scoped_timer(timer, "t1");
    timer.tic("t2");
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    timer.toc("t2");
    DataFrame results1 = timer.stop();
    L.push_back(results1);
    timer.tic("t2");
    std::this_thread::sleep_for(std::chrono::nanoseconds(500));
    timer.toc("t2");
  }
  DataFrame results2 = timer.stop();
  L.push_back(results2);
  return (L);
}

//[[Rcpp::export]]
List test_reset()
{
  Rcpp::Timer timer;
  {
    Rcpp::Timer::ScopedTimer scoped_timer(timer, "t1");
    timer.autoreturn = false;
    timer.tic("t2");
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    timer.toc("t2");
  }
  DataFrame results1 = timer.stop();
  timer.reset();
  timer.tic("t3");
  List L = List::create();
  L.push_back(results1);
  timer.toc("t3");
  DataFrame results2 = timer.stop();
  L.push_back(results2);
  return (L);
}

//[[Rcpp::export]]
DataFrame test_misc(const bool tic = true,
                    const bool toc = true,
                    const bool verbose = true,
                    const bool autoreturn = true,
                    const bool scoped_timer = true)
{
  Rcpp::Timer timer(verbose);
  timer.autoreturn = autoreturn;
  if (scoped_timer)
  {
    Rcpp::Timer::ScopedTimer scoped_timer(timer, "t1");
    if (tic)
      timer.tic("t2");
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    if (toc)
      timer.toc("t2");
  }
  DataFrame results = timer.stop();
  return (results);
}

#include <RcppArmadillo.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include <RcppClock.h>

// typedef std::map<std::pair<std::string, int>, double> TimesMap;

// // [[Rcpp::export]]
// void test(Rcpp::CharacterVector tick_names,
//           Rcpp::CharacterVector tock_names,
//           arma::vec tick_times,
//           arma::vec tock_times)
// {

//     std::pair<TimesMap::iterator, bool> insertTime;
//     std::pair<std::string, int> key;

//     /* Sort ticks and tocks by tick_name and tock_name */

//     TimesMap tickmap;
//     for (std::size_t i = 0; i < tick_names.size(); ++i)
//     {
//         key.first = tick_names[i];
//         key.second = i;
//         insertTime = tickmap.insert(
//             std::pair<std::pair<std::string, int>, double>(key, tick_times[i]));
//     }

//     TimesMap tockmap;
//     for (std::size_t i = 0; i < tock_names.size(); ++i)
//     {
//         key.first = tock_names[i];
//         key.second = i;
//         insertTime = tockmap.insert(
//             std::pair<std::pair<std::string, int>, double>(key, tock_times[i]));
//     }

//     std::vector<std::string> keys;
//     keys.reserve(tickmap.size());
//     std::vector<double> ticks;
//     ticks.reserve(tickmap.size());
//     for (auto kv : tickmap)
//     {
//         keys.push_back(kv.first.first);
//         ticks.push_back(kv.second);
//     }

//     std::vector<double> tocks;
//     tocks.reserve(tockmap.size());
//     for (auto kv : tockmap)
//     {
//         tocks.push_back(kv.second);
//     }
// }

// [[Rcpp::export]]
int test()
{

    int X = 50;
    int Y = 50;
    int Z = 50;

    Rcpp::Clock clock;
    arma::wall_clock timer;

    for (unsigned int x = 0; x < X; x++)
    {
        for (unsigned int y = 0; y < Y; y++)
        {
            for (unsigned int z = 0; z < Z; z++)
            {
                clock.tick("Z action");
                arma::vec tmp(100, arma::fill::randu);
                clock.tock("Z action");
            }
        }
    }

    timer.tic();
    clock.stop("times");
    double n = timer.toc();
    arma::cout << "number of seconds: " << n << arma::endl;

    return 0;
}
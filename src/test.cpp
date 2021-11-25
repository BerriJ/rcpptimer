#include <RcppArmadillo.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

// #include <RcppClock.h>
typedef std::map<std::pair<std::string, int>, double> TimesMap;

// [[Rcpp::export]]
void test(Rcpp::CharacterVector tick_names,
          Rcpp::CharacterVector tock_names,
          arma::vec tick_times,
          arma::vec tock_times)
{

    /* We dont need this in RcppClock.h since we already have std::vector's */
    std::vector<std::string> tick_namesc = Rcpp::as<std::vector<std::string>>(tick_names);
    std::vector<std::string> tock_namesc = Rcpp::as<std::vector<std::string>>(tock_names);
    std::vector<double> tick_timesc = arma::conv_to<std::vector<double>>::from(tick_times);
    std::vector<double> tock_timesc = arma::conv_to<std::vector<double>>::from(tock_times);

    std::pair<TimesMap::iterator, bool> insertTime;
    std::pair<std::string, int> key;

    /* Sort ticks and tocks by tick_name and tock_name */

    TimesMap tickmap;
    for (std::size_t i = 0; i < tick_namesc.size(); ++i)
    {
        key.first = tick_names[i];
        key.second = i;
        insertTime = tickmap.insert(
            std::pair<std::pair<std::string, int>, double>(key, tick_timesc[i]));
    }

    TimesMap tockmap;
    for (std::size_t i = 0; i < tick_namesc.size(); ++i)
    {
        key.first = tock_names[i];
        key.second = i;
        insertTime = tockmap.insert(
            std::pair<std::pair<std::string, int>, double>(key, tock_timesc[i]));
    }

    std::vector<std::string> keys;
    keys.reserve(tickmap.size());
    std::vector<double> ticks;
    ticks.reserve(tickmap.size());
    for (auto kv : tickmap)
    {
        keys.push_back(kv.first.first);
        ticks.push_back(kv.second);
    }

    std::vector<double> tocks;
    tocks.reserve(tockmap.size());
    for (auto kv : tockmap)
    {
        tocks.push_back(kv.second);
    }
}
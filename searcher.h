/* 
* Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
* This file is part of solution of test task described in README.md.
*/
#pragma once

#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <tuple>
#include <regex>
#include <functional>

namespace mtfind
{
    class searcher
    {
    public:
        explicit searcher(
              std::function<std::tuple<bool, size_t, std::string>()> get_next
            , const std::string & pattern
            , unsigned int n_threads
        );
        searcher(const searcher & orig) = delete;
        virtual ~searcher();
        
        std::list<std::tuple<size_t, unsigned int, std::string>> get();

    private:
        void thread_func(
              std::function<std::tuple<bool, size_t, std::string>()> get_next
            , const std::regex pattern
        );

        void join_all_threads();

    private:
        std::list<std::thread> threads;
        std::list<std::tuple<size_t, unsigned int, std::string>> result;
        std::mutex mutex;
    };
}

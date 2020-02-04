/* 
* Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
* This file is part of solution of test task described in README.md.
*/
#include "searcher.h"

namespace mtfind
{
    searcher::searcher(
          std::function<std::tuple<bool, size_t, std::string>()> get_next
        , const std::string & pattern
        , unsigned int n_threads
    )
    {
        while (n_threads--)
        {
            threads.push_back(std::thread(
                  &searcher::thread_func
                , this
                , get_next
                , std::regex(pattern)
            ));
        }
    }

    searcher::~searcher()
    {
        join_all_threads();
    }
    
    std::list<std::tuple<size_t, unsigned int, std::string>> searcher::get()
    {
        join_all_threads();

        result.sort(
            [](const std::tuple<size_t, unsigned int, std::string>& lhs,  
               const std::tuple<size_t, unsigned int, std::string>& rhs) -> bool
            { 
                return (std::get<0>(lhs) < std::get<0>(rhs)); 
            } 
        );

        return result;
    }

    void searcher::join_all_threads()
    {
        for (auto & thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    void searcher::thread_func(
          std::function<std::tuple<bool, size_t, std::string>()> get_next
        , const std::regex pattern
    )
    {
        while (true)
        {
            auto [success, num, str] = get_next();
            if (!success)
                break;

            std::smatch match;
            if (std::regex_search(str, match, pattern))
            {
                std::unique_lock lock(mutex);
                result.push_back(std::tuple(num, match.position(0), match.str(0)));
            }
        }
    }

}

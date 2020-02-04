/* 
* Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
* This file is part of solution of test task described in README.md.
*/
#pragma once

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

namespace mtfind
{
    class reader
    {
    public:
        explicit reader(
              std::function<std::pair<bool, std::string>()> get_line
            , unsigned int min_queue_size_
        );
        reader(const reader & orig) = delete;
        virtual ~reader();

        std::tuple<bool, size_t, std::string> get_next();

    private:
        void thread_func(std::function<std::pair<bool, std::string>()> get_line);

    private:
        std::queue<std::pair<size_t, std::string>> lines;
        std::atomic_bool eof;
        const unsigned int min_queue_size;
        
        std::thread thread;
        std::mutex  mutex;
        std::condition_variable condition_read;
        std::condition_variable condition_write;
    };
}

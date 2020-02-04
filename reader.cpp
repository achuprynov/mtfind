/* 
* Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
* This file is part of solution of test task described in README.md.
*/
#include "reader.h"

namespace mtfind
{
    reader::reader(
          std::function<std::pair<bool, std::string>()> get_line
        , unsigned int min_queue_size_
    )
    : eof(false)
    , min_queue_size(min_queue_size_)
    , thread(&reader::thread_func, this, get_line)
    {
    }

    reader::~reader()
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    
    std::tuple<bool, size_t, std::string> reader::get_next()
    {
        std::unique_lock lock(mutex);

        while (lines.empty())
        {
            if (eof)
            {
                return std::tuple(false, 0, "");
            }

            condition_read.wait(lock);
        }

        auto elem = lines.front();
        lines.pop();
        auto queue_size = lines.size();
        lock.unlock();

        if (queue_size < min_queue_size)
        {
            condition_write.notify_all();
        }

        return std::tuple(true, elem.first, elem.second);
    }

    void reader::thread_func(std::function<std::pair<bool, std::string>()> get_line)
    {
        size_t num = 0;
        size_t queue_size = 0;

        while (true)
        {
            auto [success, line] = get_line();
            if (!success)
                break;

            num++;
            {
                std::unique_lock lock(mutex);
                lines.push(std::pair(num, line));
                queue_size = lines.size();
            }
            condition_read.notify_all();

            if (queue_size > min_queue_size)
            {
                std::unique_lock lock(mutex);
                if (lines.size() > min_queue_size)
                {
                    condition_write.wait(lock);
                }
            }
        }

        eof = true;
        condition_read.notify_all();
    }
}

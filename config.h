/* 
* Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
* This file is part of solution of test task described in README.md.
*/
#pragma once

#include <string>

namespace mtfind
{
    class config 
    {
    public:
        explicit config(int argc, char** argv);
        config(const config & orig) = delete;
        virtual ~config() {}
        
        std::string  get_path()    const noexcept;
        std::string  get_pattern() const noexcept;
        unsigned int get_threads() const noexcept;
        unsigned int get_ratio()   const noexcept;

    private:
        std::string  path;
        std::string  pattern;
        unsigned int threads;
        unsigned int ratio;
    };
}

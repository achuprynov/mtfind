/* 
 * Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
 * This file is part of solution of test task described in README.md.
 */
#include <iostream>
#include <fstream>

#include "config.h"
#include "reader.h"
#include "searcher.h"

int main(int argc, char** argv)
{
    mtfind::config config(argc, argv);

    std::ifstream file(config.get_path());

    mtfind::reader reader(
        [&]() -> std::pair<bool, std::string>
        {
            if (file.eof()) {
                return std::pair(false, "");
            } else {
                std::string line;
                std::getline(file, line);
                return std::pair(true, line);
            }
        }
        , (config.get_threads() * config.get_ratio())
    );

    mtfind::searcher searcher(
        [&]() -> std::tuple<bool, size_t, std::string>
        {
            return reader.get_next();
        }
        , config.get_pattern()
        , config.get_threads()
    );

    auto result = searcher.get();

    std::cout << result.size() << std::endl;

    for (auto & elem : result)
    {
        std::cout 
            << std::get<0>(elem) << " " 
            << std::get<1>(elem) << " " 
            << std::get<2>(elem) << std::endl;
    }

    return 0;
}

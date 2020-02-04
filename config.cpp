/* 
 * Copyright (C) Alexander Chuprynov <achuprynov@gmail.com>
 * This file is part of solution of test task described in README.md.
 */
#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include "config.h"

namespace mtfind
{
    config::config(int argc, char** argv)
    {
        const char * program_name = argv[0];

        std::stringstream using_string;
        using_string << "Using: " << program_name << " [option]\nDefault option";

        boost::program_options::options_description desc(using_string.str().c_str());

        desc.add_options()
            ("help", "show this text")
            ("path", boost::program_options::value<std::string>()->default_value(""), "path to file")
            ("pattern", boost::program_options::value<std::string>()->default_value(""), "searching pattern (max 100)")
            ("threads", boost::program_options::value<int>()->default_value(10), "num of searching threads (max 100)")
            ("ratio", boost::program_options::value<int>()->default_value(10), "min lines per thread (max 1000)")
        ;

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        if (vm.find("help") != vm.end())
        {
            std::cout << desc << std::endl;
            exit(EXIT_SUCCESS);
        }

        path    = vm["path"].as<std::string>();
        pattern = vm["pattern"].as<std::string>();
        threads = vm["threads"].as<int>();
        ratio   = vm["ratio"].as<int>();

        if (path.empty() 
            || pattern.empty() || pattern.length() > 100 
            || threads < 1 || threads > 100
            || ratio < 1 || ratio > 1000
        )
        {
            std::cout << desc << std::endl;
            exit(EXIT_SUCCESS);
        }
    }

    std::string config::get_path() const noexcept
    {
        return path;
    }

    std::string config::get_pattern() const noexcept
    {
        return pattern;
    }

    unsigned int config::get_threads() const noexcept
    {
        return threads;
    }

    unsigned int config::get_ratio() const noexcept
    {
        return ratio;
    }
}

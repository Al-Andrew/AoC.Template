#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;


#include "cxxopts.hpp"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

static constexpr unsigned int DAY = 01;
static constexpr unsigned int YEAR = 2022;

long long part_one_main(std::string input)
{
    std::clog << input;
    return 1;
}


long long part_two_main(std::string input)
{
    std::clog << input;
    return 2;
}



int main(int argc, char** argv)
{
    cxxopts::Options options{"aoc", "aoc solution"};

    options.add_options()
        ("test", "if preset will run the code on the test input.", cxxopts::value<bool>()->default_value("false"))
        ("one", "run the code for part 1")
        ("two", "runt he code for part 2")
        ;

    cxxopts::ParseResult parsed_options = options.parse(argc, argv);

    std::string input;
    if(parsed_options["test"].as<bool>()) {
        std::stringstream fnss;
        fnss << "input_test_" << DAY << "_" << YEAR << ".input";
        std::string filename = fnss.str();
        
        if(fs::is_regular_file(filename)) {
            std::ifstream fin{filename};
            std::stringstream finss;
            finss << fin.rdbuf();
            input = finss.str();
        } else {
            std::clog << "No input file for day: " << DAY << " year: " << YEAR << " [" << filename << "].\n";
            return 1;
        }
    } else {
        std::stringstream fnss;
        fnss << "input_given_" << DAY << "_" << YEAR << ".input";
        std::string filename = fnss.str();
        
        if(fs::is_regular_file(filename)) {
            std::ifstream fin{filename};
            std::stringstream finss;
            finss << fin.rdbuf();
            input = finss.str();
        } else {
            // session cookie is a secret. read it from a file
            std::ifstream fin("session.cookie");
            if(!fin.is_open()) {
                std::clog << "You need a session.cookie file to automatically fetch the puzzle input.\n";
                return 1;
            }
            std::string session;
            fin >> session;

            httplib::Headers hdrs{
            {"Cookie", "session=" + session}
            };
            httplib::Client cl{"https://adventofcode.com"};

            std::stringstream remote_path;
            remote_path << "/" << YEAR << "/day/" << DAY << "/input";

            auto res = cl.Get(remote_path.str(), hdrs);
            
            input = res->body;

            std::ofstream fout(filename);
            fout << input;
        }
    }

    if(parsed_options["one"].as<bool>()) 
    {
        long long result = part_one_main(input);
        std::cout << "result: " << result << "\n";
    } 
    else if (parsed_options["two"].as<bool>())
    {
        long long result = part_two_main(input);
        std::cout << "result: " << result << "\n";    
    }
    else {
        std::clog << "You called me wrong.\n";
        return 1;        
    }

    return 0;
}

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <limits>
#include <algorithm>

using ip_struct = std::vector<std::tuple<uint32_t, std::vector<std::string>>>;

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

uint32_t ip_to_numeric(const std::vector<std::string>& ip_vector)
{
    const uint8_t ip_size = 4;
    const uint8_t ip_offset = 8;

    if (ip_vector.size() != ip_size)
        throw std::runtime_error("Invalid IP address format: Incorrect number of octets.");

    uint32_t result = 0;
    for (uint8_t i = 0; i < ip_size; ++i)
    {
        try
        {
            int octet = std::stoi(ip_vector[i]);
            if (!(octet >= std::numeric_limits<uint8_t>::min() && octet <= std::numeric_limits<uint8_t>::max()))
                throw std::runtime_error("Invalid IP address format: Octet out of range.");
            result = (result << ip_offset) | static_cast<uint32_t>(octet);
        }
        catch (const std::invalid_argument&)
        {
            throw std::runtime_error("Invalid IP address format: Non-numeric octet.");
        }
    }
    return result;
}

void ip_print(ip_struct& ip_pool)
{
    for (const auto& [ip_numeric, ip_vector] : ip_pool)
    {
        bool first = true;
        for (const auto& octet : ip_vector)
        {
            if (!first)
                std::cout << ".";
            std::cout << octet;
                first = false;
        }
        std::cout << std::endl;
    }
}

void ip_print_filter_first_byte(ip_struct& ip_pool, const uint8_t byte)
{
    const uint8_t ip_offset = 24;

    for (const auto& [ip_numeric, ip_vector] : ip_pool)
    {
        if (((ip_numeric >> ip_offset) != byte))
            continue;
        bool first = true;
        for (const auto& octet : ip_vector)
        {
            if (!first)
                std::cout << ".";
            std::cout << octet;
            first = false;
        }
        std::cout << std::endl;
    }
}

void ip_print_filter_first_and_second_byte(ip_struct& ip_pool, const uint8_t byteFirst, const uint8_t byteSecond)
{
    const uint8_t ip_offset_first = 24;
    const uint8_t ip_offset_second = 16;

    for (const auto& [ip_numeric, ip_vector] : ip_pool)
    {
        if (((ip_numeric >> ip_offset_first) != byteFirst) || (((ip_numeric >> ip_offset_second) & 0xFF) != byteSecond))
            continue;
        bool first = true;
        for (const auto& octet : ip_vector)
        {
            if (!first)
                std::cout << ".";
            std::cout << octet;
            first = false;
        }
        std::cout << std::endl;
    }
}

void ip_print_filter_any(ip_struct& ip_pool, const uint8_t byte)
{
    uint8_t ip_iter = 0;
    const uint8_t ip_size = 4;
    const uint8_t ip_offset = 8;

    for (const auto& [ip_numeric, ip_vector] : ip_pool)
    {
        bool include_byte = false;
        for (uint8_t i = 0; i < ip_size; ++i)
        {
            if (((ip_numeric >> ip_iter & 0xFF) == byte))
            {
                include_byte = true;
                continue;
            }
            ip_iter += ip_offset;
        }
        
        if (!include_byte)
            continue;

        bool first = true;
        for (const auto& octet : ip_vector)
        {
            if (!first)
                std::cout << ".";
            std::cout << octet;
            first = false;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        ip_struct ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            if (!v.empty())
            {
                std::vector<std::string> ip_vector = split(v.at(0), '.');
                try
                {
                    uint32_t ip_numeric = ip_to_numeric(ip_vector);
                    ip_pool.emplace_back(ip_numeric, ip_vector);
                }
                catch (const std::runtime_error& e)
                {
                    std::cerr << "Error processing IP address: " << e.what() << std::endl;
                    continue;
                }
            }
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& left, const auto& right)
        {
            return std::get<0>(left) > std::get<0>(right);
        });

        // Reverse lexicographically sort
        ip_print(ip_pool);
        
        // Filter by first byte and output
        ip_print_filter_first_byte(ip_pool, 1);

        // Filter by first and second bytes and output
        ip_print_filter_first_and_second_byte(ip_pool, 46, 70);

        // Filter by any byte and output
        ip_print_filter_any(ip_pool, 46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

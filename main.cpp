#include "ip_filter.h"

int main(int argc, char const* argv[])
{
    try
    {
        ip_struct ip_pool;

        for (std::string line; std::getline(std::cin, line);)
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

        // Reverse lexicographically sort
        sort(ip_pool);
        ip_print(ip_pool);

        // Filter by first byte and output
        ip_print_filter_first_byte(ip_pool, 1);

        // Filter by first and second bytes and output
        ip_print_filter_first_and_second_byte(ip_pool, 46, 70);

        // Filter by any byte and output
        ip_print_filter_any(ip_pool, 46);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
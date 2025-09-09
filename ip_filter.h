#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

using ip_struct = std::vector<std::tuple<uint32_t, std::vector<std::string>>>;

std::vector<std::string> split(const std::string& str, char d);
void sort(ip_struct& ip_pool);
uint32_t ip_to_numeric(const std::vector<std::string>& ip_vector);
void ip_print(ip_struct& ip_pool);
void ip_print_filter_first_byte(ip_struct& ip_pool, const uint8_t byte);
void ip_print_filter_first_and_second_byte(ip_struct& ip_pool, const uint8_t byteFirst, const uint8_t byteSecond);
void ip_print_filter_any(ip_struct& ip_pool, const uint8_t byte);
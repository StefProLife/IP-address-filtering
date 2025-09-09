#define GOOGLE_TEST_MODULE GTEST_IP_FILTER

#include <gtest/gtest.h>

#include "ip_filter.h"

TEST(TestIPFilter, TestSplit)
{
    const std::string inputIPStirng = "112.154.12.32";
    const std::vector<std::string> expected =
    {
        "112",
        "154",
        "12",
        "32"
    };

    auto actual = split(inputIPStirng, '.');

    ASSERT_EQ(expected.size(), actual.size());
    for (int item = 0; item < expected.size(); i++)
        ASSERT_EQ(expected[i], actual[i])
}


TEST(TestIPFilter, TestIpToNumeric)
{
    const std::vector<std::string> inputIPVector =
    {
        "112",
        "154",
        "12",
        "32"
    };
    const uint32_t expected = 1889143840;

    uint32_t actual = ip_to_numeric(inputIPVector);
    ASSERT_EQ(expected, actual);
}
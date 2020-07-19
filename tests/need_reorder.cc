/* This file is part of regetopt.
   reGetopt is licensed under GNU GPL v3 or MIT License. */

#include <string>

#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

#include "../include/regetopt.h"

BOOST_AUTO_TEST_CASE(need_reorder) {
    using namespace std::string_literals;
    int argc = 5;
    const char *argv[] = {"a.out", "abc","-fbbaz", "-z", "bar", 0};

    static struct re_option long_options[] = {
        {"foo", re_no_argument, nullptr, '1'},
        {"bar", re_required_argument, nullptr, '2'},
        {"foobar", re_required_argument, nullptr, '3'},
        {0, 0, 0, 0}};

    int opt = regetopt(argc, const_cast<char **>(argv), "fb:z:", long_options,
                       nullptr);
    BOOST_TEST(opt == 'f');

    opt = regetopt(argc, const_cast<char **>(argv), "fb:z:", long_options,
                   nullptr);
    BOOST_TEST(opt == 'b');
    BOOST_TEST(re_optarg != nullptr);
    BOOST_TEST("baz"s == re_optarg);

    opt = regetopt(argc, const_cast<char **>(argv), "fb:z:", long_options,
                   nullptr);
    BOOST_TEST(opt == 'z');
    BOOST_TEST(re_optarg != nullptr);
    BOOST_TEST("bar"s == re_optarg);

    opt = regetopt(argc, const_cast<char **>(argv), "fb:z:", long_options,
                   nullptr);
    BOOST_TEST(opt == -1);

    BOOST_TEST(re_optind == 4);
    BOOST_TEST("abc"s == argv[4]);
}

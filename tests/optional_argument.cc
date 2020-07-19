/* This file is part of regetopt.
   reGetopt is licensed under GNU GPL v3 or MIT License. */

#include <string>

#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

#include "../include/regetopt.h"

BOOST_AUTO_TEST_CASE(optional_argument) {
    using namespace std::string_literals;
    int argc = 7;
    const char *argv[] = {"a.out",     "--foo",    "abc", "--bar=def",
                          "--baz=ghi", "--foobar", "jkl", 0};

    static struct re_option long_options[] = {
        {"foo", re_required_argument, nullptr, '1'},
        {"bar", re_required_argument, nullptr, '2'},
        {"baz", re_optional_argument, nullptr, '3'},
        {"foobar", re_optional_argument, nullptr, '4'},
        {0, 0, 0, 0}};

    int opt =
        regetopt(argc, const_cast<char **>(argv), "", long_options, nullptr);
    BOOST_TEST(opt == '1');
    BOOST_TEST(re_optarg != nullptr);
    BOOST_TEST("abc"s == re_optarg);

    opt = regetopt(argc, const_cast<char **>(argv), "", long_options, nullptr);
    BOOST_TEST(opt == '2');
    BOOST_TEST(re_optarg != nullptr);
    BOOST_TEST("def"s == re_optarg);

    opt = regetopt(argc, const_cast<char **>(argv), "", long_options, nullptr);
    BOOST_TEST(opt == '3');
    BOOST_TEST(re_optarg != nullptr);
    BOOST_TEST("ghi"s == re_optarg);

    opt = regetopt(argc, const_cast<char **>(argv), "", long_options, nullptr);
    BOOST_TEST(opt == '4');
    BOOST_TEST(re_optarg == nullptr);

    opt = regetopt(argc, const_cast<char **>(argv), "", long_options, nullptr);
    BOOST_TEST(opt == -1);

    BOOST_TEST(re_optind == 6);
    BOOST_TEST("jkl"s == argv[6]);
}

#define BOOST_TEST_MODULE bulk_test_module
#include "../src/output_helper.h"
#include <boost/test/unit_test.hpp>
#include <fstream>

BOOST_AUTO_TEST_SUITE(bulk_test_suite)

BOOST_AUTO_TEST_CASE(bulk_test_1)
{
    std::vector<std::string> expectedResult = {
        "bulk: cmd1, cmd2, cmd3",
        "bulk: cmd4, cmd5"
    };
    std::stringstream testStream;
    testStream << "cmd1" << std::endl
        << "cmd2" << std::endl
        << "cmd3" << std::endl
        << "cmd4" << std::endl
        << "cmd5" << std::endl;
    std::string outputFileName;
    {
        BulkProxy bulk(3);
        testStream >> bulk;
        outputFileName = bulk.bulk()->fileName();
    }
    BOOST_CHECK(!outputFileName.empty());
    std::fstream outputFile(outputFileName, std::fstream::in);

    auto expIt = expectedResult.begin();
    for (std::string line; std::getline(outputFile, line); ) {
        BOOST_CHECK_EQUAL(*expIt, line);
        ++expIt;
    }
    BOOST_CHECK(expIt == expectedResult.end());
}

BOOST_AUTO_TEST_CASE(bulk_test_2)
{
    std::vector<std::string> expectedResult = {
        "bulk: cmd1, cmd2, cmd3",
        "bulk: cmd4, cmd5, cmd6, cmd7"
    };
    std::stringstream testStream;
    testStream << "cmd1" << std::endl
        << "cmd2" << std::endl
        << "cmd3" << std::endl
        << "{" << std::endl
        << "cmd4" << std::endl
        << "cmd5" << std::endl
        << "cmd6" << std::endl
        << "cmd7" << std::endl
        << "}" << std::endl;
    std::string outputFileName;
    {
        BulkProxy bulk(3);
        testStream >> bulk;
        outputFileName = bulk.bulk()->fileName();
    }
    BOOST_CHECK(!outputFileName.empty());
    std::fstream outputFile(outputFileName, std::fstream::in);

    auto expIt = expectedResult.begin();
    for (std::string line; std::getline(outputFile, line); ) {
        BOOST_CHECK_EQUAL(*expIt, line);
        ++expIt;
    }
    BOOST_CHECK(expIt == expectedResult.end());
}

BOOST_AUTO_TEST_CASE(bulk_test_3)
{
    std::vector<std::string> expectedResult = {
        "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6"
    };
    std::stringstream testStream;
    testStream << "{" << std::endl
        << "cmd1" << std::endl
        << "cmd2" << std::endl
        << "{" << std::endl
        << "cmd3" << std::endl
        << "cmd4" << std::endl
        << "}" << std::endl
        << "cmd5" << std::endl
        << "cmd6" << std::endl
        << "}" << std::endl;
    std::string outputFileName;
    {
        BulkProxy bulk(3);
        testStream >> bulk;
        outputFileName = bulk.bulk()->fileName();
    }
    BOOST_CHECK(!outputFileName.empty());
    std::fstream outputFile(outputFileName, std::fstream::in);

    auto expIt = expectedResult.begin();
    for (std::string line; std::getline(outputFile, line); ) {
        BOOST_CHECK_EQUAL(*expIt, line);
        ++expIt;
    }
    BOOST_CHECK(expIt == expectedResult.end());
}

BOOST_AUTO_TEST_CASE(bulk_test_4)
{
    std::vector<std::string> expectedResult = {
        "bulk: cmd1, cmd2, cmd3"
    };
    std::stringstream testStream;
    testStream << "cmd1" << std::endl
        << "cmd2" << std::endl
        << "cmd3" << std::endl
        << "{" << std::endl
        << "cmd4" << std::endl
        << "cmd5" << std::endl
        << "cmd6" << std::endl
        << "cmd7" << std::endl;
    std::string outputFileName;
    {
        BulkProxy bulk(3);
        testStream >> bulk;
        outputFileName = bulk.bulk()->fileName();
    }
    BOOST_CHECK(!outputFileName.empty());
    std::fstream outputFile(outputFileName, std::fstream::in);

    auto expIt = expectedResult.begin();
    for (std::string line; std::getline(outputFile, line); ) {
        BOOST_CHECK_EQUAL(*expIt, line);
        ++expIt;
    }
    BOOST_CHECK(expIt == expectedResult.end());
}

BOOST_AUTO_TEST_SUITE_END()

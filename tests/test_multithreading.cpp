#define BOOST_TEST_MODULE bulk_test_module
#include "../src/output_helper.h"
#include <boost/test/unit_test.hpp>
#include <fstream>
#include "test_output.h"

BOOST_AUTO_TEST_SUITE(multithreading_test_suite)

template <size_t PoolSize = 2>
void test(const std::vector<std::vector<std::string>> &testData, const std::vector<std::string> &expectedResult) {
    std::string outputFileName;
    std::shared_ptr<TestOutput> testOutput;
    {
        OutputHelper<PoolSize, TestOutput, FileOutput> out;
        testOutput = out.logger();
        for (const auto &d : testData) {
            out << d;
        }
    }
    BOOST_CHECK_EQUAL(testOutput->mProcessedUnits.size(), expectedResult.size());
    for (const auto &unit : testOutput->mProcessedUnits) {
        BOOST_CHECK(!unit.fileName.empty());
        std::fstream outputFile(unit.fileName, std::fstream::in);
        std::string line;
        std::getline(outputFile, line);
        BOOST_CHECK(!line.empty());
        BOOST_CHECK(std::any_of(expectedResult.cbegin(),
                                expectedResult.cend(),
                                [&line](const std::string &exp){ return exp==line; }));
    }
}

BOOST_AUTO_TEST_CASE(multithreading_test_1)
{
    std::vector<std::vector<std::string>> testData = {
        {"cmd1", "cmd2", "cmd3"},
        {"cmd4", "cmd5"}
    };
    std::vector<std::string> expectedResult = {
        "cmd1, cmd2, cmd3",
        "cmd4, cmd5"
    };
    test(testData, expectedResult);
}

BOOST_AUTO_TEST_CASE(bulk_test_2)
{
    std::vector<std::vector<std::string>> testData = {
        {"cmd1", "cmd2", "cmd3"},
        {"cmd4", "cmd5", "cmd6", "cmd7"},
        {"cmd8", "cmd9", "cmd10", "cmd11", "cmd12"}
    };
    std::vector<std::string> expectedResult = {
        "cmd1, cmd2, cmd3",
        "cmd4, cmd5, cmd6, cmd7",
        "cmd8, cmd9, cmd10, cmd11, cmd12"
    };
    test(testData, expectedResult);
}

BOOST_AUTO_TEST_CASE(bulk_test_3)
{
    std::vector<std::vector<std::string>> testData = {
        {"cmd1", "cmd2", "cmd3"},
        {"cmd4", "cmd5", "cmd6", "cmd7"},
        {"cmd8", "cmd9", "cmd10", "cmd11", "cmd12"},
        {"cmd13", "cmd14", "cmd15", "cmd16", "cmd17", "cmd18"}
    };
    std::vector<std::string> expectedResult = {
        "cmd1, cmd2, cmd3",
        "cmd4, cmd5, cmd6, cmd7",
        "cmd8, cmd9, cmd10, cmd11, cmd12",
        "cmd13, cmd14, cmd15, cmd16, cmd17, cmd18"
    };
    test(testData, expectedResult);
}

BOOST_AUTO_TEST_CASE(bulk_test_4)
{
    std::vector<std::vector<std::string>> testData = {
        {"cmd1", "cmd2", "cmd3"},
        {"cmd4", "cmd5", "cmd6", "cmd7"},
        {"cmd8", "cmd9", "cmd10", "cmd11", "cmd12"},
        {"cmd13", "cmd14", "cmd15", "cmd16", "cmd17", "cmd18"},
        {"cmd19", "cmd20", "cmd21", "cmd22", "cmd23", "cmd24", "cmd25"},
        {"cmd26", "cmd27", "cmd28", "cmd29", "cmd30", "cmd31", "cmd32", "cmd33"},
        {"cmd34", "cmd35", "cmd36", "cmd37", "cmd38", "cmd39", "cmd40", "cmd41"},
        {"cmd41", "cmd42", "cmd43", "cmd44", "cmd45", "cmd46", "cmd47", "cmd48"},
        {"cmd48", "cmd49", "cmd50", "cmd51", "cmd52", "cmd53", "cmd54", "cmd55"},
        {"cmd55", "cmd56", "cmd57", "cmd58", "cmd59", "cmd60", "cmd61", "cmd62"},
        {"cmd62", "cmd63", "cmd64", "cmd65", "cmd66", "cmd67", "cmd68", "cmd69"},
        {"cmd69", "cmd70", "cmd71", "cmd72", "cmd73", "cmd74", "cmd75", "cmd76"},
        {"cmd76", "cmd77", "cmd78", "cmd79", "cmd80", "cmd81", "cmd82", "cmd83"},
        {"cmd83", "cmd84", "cmd85", "cmd86", "cmd87", "cmd88", "cmd89", "cmd90"},
        {"cmd90", "cmd91", "cmd92", "cmd93", "cmd94", "cmd95", "cmd96", "cmd97"},
        {"cmd97", "cmd98", "cmd99", "cmd100", "cmd101", "cmd102", "cmd103", "cmd104"},
        {"cmd104", "cmd105", "cmd106", "cmd107", "cmd108", "cmd109", "cmd110", "cmd111"},
        {"cmd111", "cmd112", "cmd113", "cmd114", "cmd115", "cmd116", "cmd117", "cmd118"},
        {"cmd118", "cmd119", "cmd120", "cmd121", "cmd122", "cmd123", "cmd124", "cmd125"},
        {"cmd125", "cmd126", "cmd127", "cmd128", "cmd129", "cmd130", "cmd131", "cmd132"},
        {"cmd132", "cmd133", "cmd134", "cmd135", "cmd136", "cmd137", "cmd138", "cmd139"},
        {"cmd139", "cmd140", "cmd141", "cmd142", "cmd143", "cmd144", "cmd145", "cmd146"},
        {"cmd146", "cmd147", "cmd148", "cmd149", "cmd150", "cmd151", "cmd152", "cmd153"},
        {"cmd153", "cmd154", "cmd155", "cmd156", "cmd157", "cmd158", "cmd159", "cmd160"},
        {"cmd160", "cmd161", "cmd162", "cmd163", "cmd164", "cmd165", "cmd166", "cmd167"},
        {"cmd167", "cmd168", "cmd169", "cmd170", "cmd171", "cmd172", "cmd173", "cmd174"},
        {"cmd174", "cmd175", "cmd176", "cmd177", "cmd178", "cmd179", "cmd180", "cmd181"},
        {"cmd181", "cmd182", "cmd183", "cmd184", "cmd185", "cmd186", "cmd187", "cmd188"},
        {"cmd188", "cmd189", "cmd190", "cmd191", "cmd192", "cmd193", "cmd194", "cmd195"},
        {"cmd195", "cmd196", "cmd197", "cmd198", "cmd199", "cmd200", "cmd201", "cmd202"}
    };
    std::vector<std::string> expectedResult = {
        "cmd1, cmd2, cmd3",
        "cmd4, cmd5, cmd6, cmd7",
        "cmd8, cmd9, cmd10, cmd11, cmd12",
        "cmd13, cmd14, cmd15, cmd16, cmd17, cmd18",
        "cmd19, cmd20, cmd21, cmd22, cmd23, cmd24, cmd25",
        "cmd26, cmd27, cmd28, cmd29, cmd30, cmd31, cmd32, cmd33",
        "cmd34, cmd35, cmd36, cmd37, cmd38, cmd39, cmd40, cmd41",
        "cmd41, cmd42, cmd43, cmd44, cmd45, cmd46, cmd47, cmd48",
        "cmd48, cmd49, cmd50, cmd51, cmd52, cmd53, cmd54, cmd55",
        "cmd55, cmd56, cmd57, cmd58, cmd59, cmd60, cmd61, cmd62",
        "cmd62, cmd63, cmd64, cmd65, cmd66, cmd67, cmd68, cmd69",
        "cmd69, cmd70, cmd71, cmd72, cmd73, cmd74, cmd75, cmd76",
        "cmd76, cmd77, cmd78, cmd79, cmd80, cmd81, cmd82, cmd83",
        "cmd83, cmd84, cmd85, cmd86, cmd87, cmd88, cmd89, cmd90",
        "cmd90, cmd91, cmd92, cmd93, cmd94, cmd95, cmd96, cmd97",
        "cmd97, cmd98, cmd99, cmd100, cmd101, cmd102, cmd103, cmd104",
        "cmd104, cmd105, cmd106, cmd107, cmd108, cmd109, cmd110, cmd111",
        "cmd111, cmd112, cmd113, cmd114, cmd115, cmd116, cmd117, cmd118",
        "cmd118, cmd119, cmd120, cmd121, cmd122, cmd123, cmd124, cmd125",
        "cmd125, cmd126, cmd127, cmd128, cmd129, cmd130, cmd131, cmd132",
        "cmd132, cmd133, cmd134, cmd135, cmd136, cmd137, cmd138, cmd139",
        "cmd139, cmd140, cmd141, cmd142, cmd143, cmd144, cmd145, cmd146",
        "cmd146, cmd147, cmd148, cmd149, cmd150, cmd151, cmd152, cmd153",
        "cmd153, cmd154, cmd155, cmd156, cmd157, cmd158, cmd159, cmd160",
        "cmd160, cmd161, cmd162, cmd163, cmd164, cmd165, cmd166, cmd167",
        "cmd167, cmd168, cmd169, cmd170, cmd171, cmd172, cmd173, cmd174",
        "cmd174, cmd175, cmd176, cmd177, cmd178, cmd179, cmd180, cmd181",
        "cmd181, cmd182, cmd183, cmd184, cmd185, cmd186, cmd187, cmd188",
        "cmd188, cmd189, cmd190, cmd191, cmd192, cmd193, cmd194, cmd195",
        "cmd195, cmd196, cmd197, cmd198, cmd199, cmd200, cmd201, cmd202"
    };
    test<5>(testData, expectedResult);
}

BOOST_AUTO_TEST_SUITE_END()

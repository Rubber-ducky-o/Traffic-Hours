#include <gtest/gtest.h>
#include "parser.h"
#include <fstream>
#include <sstream>



TEST(parseClosureData, JsonParser)
{
    std::ifstream file("sample_json/data.json");

    ASSERT_TRUE(file.is_open());

    std::stringstream buf;
    buf << file.rdbuf();

    std::string json_file = buf.str();


    auto closures = parseClosureData(json_file);

    ASSERT_EQ(closures.size(),1);
    EXPECT_EQ(closures[0].route,"SR-1");
    EXPECT_EQ(closures[0].direction,"North");

    EXPECT_NEAR(closures[0].begin_lat,33.944099,0.000001);
    EXPECT_NEAR(closures[0].begin_lon,-118.396158,0.000001);

    EXPECT_EQ(closures[0].total_existing_lanes,4);
    EXPECT_EQ(closures[0].lanes_closed.size(),2);
    EXPECT_EQ(closures[0].lanes_closed[0],1);
    EXPECT_EQ(closures[0].lanes_closed[1],2);

    EXPECT_EQ(closures[0].start_epoch,1790398860);
    EXPECT_EQ(closures[0].end_epoch,1790434740);



}

TEST(parseClosureData, missed_data)
{
    std::ifstream file("sample_json/missing_data.json");

    ASSERT_TRUE(file.is_open());

    std::stringstream buf;
    buf << file.rdbuf();

    std::string json_file = buf.str();


    auto closures = parseClosureData(json_file);

    ASSERT_EQ(closures.size(),7);

}
TEST(parseClosureData,incorrect_data)
{
     std::ifstream file("sample_json/missing_data.json");

    ASSERT_TRUE(file.is_open());

    std::stringstream buf;
    buf << file.rdbuf();

    std::string json_file = buf.str();


    auto closures = parseClosureData(json_file);

    ASSERT_EQ(closures.size(),7);

}


TEST(parseClosureData,incorrect_type)
{
     std::ifstream file("sample_json/incorrect_type.json");

    ASSERT_TRUE(file.is_open());

    std::stringstream buf;
    buf << file.rdbuf();

    std::string json_file = buf.str();


    auto closures = parseClosureData(json_file);

    ASSERT_EQ(closures.size(),2);

}
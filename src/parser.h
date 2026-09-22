#ifndef PARSER_H
#define PARSER_H
#pragma once
#include <string>
#include <vector>


struct ClosureData
{
    std::string route;
    double begin_lat;
    double begin_lon;
    double end_lat;
    double end_lon;
    std::string direction;

    std::vector<int> lanes_closed;
    int total_existing_lanes;

    long long start_epoch;
    long long end_epoch;

    ClosureData(std::string R,
        double BLAT,
        double BLON,
        double ELAT,
        double ELON,
        std::string DIR,
        std::vector<int> LC,
        int LL,
        long long SE,
        long long EE
    ) : route(R),
    begin_lat(BLAT),
    begin_lon(BLON),
    end_lat(ELAT),
    end_lon(ELON),
    direction(DIR),
    lanes_closed(LC),
    total_existing_lanes(LL),
    start_epoch(SE),
    end_epoch(EE)
    {}
};



std::vector<int> parseLanesClosed(const std::string& lanes);



std::vector<ClosureData> grabbing_data();

std::string fetchData();

std::vector<ClosureData> parseClosureData(std::string jsondata);



#endif
#include <iostream>
#include "parser.h"
#include <curl/curl.h>
#include <json/json.h>


namespace{
    std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out
    )
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

std::vector<int> parseLanesClosed(const std::string& lanes,int total_lanes)
{
    std::vector<int> result;
    if(lanes == "All")
    {
        for (int i =1;i <=total_lanes; i++)
        {
            result.push_back(i);
        }
        return result;
    }


    std::stringstream ss(lanes);
    std::string value;

    while(std::getline(ss,value,','))
    {
        if(value.find_first_not_of("\t") == std::string::npos)
        {
            continue;
        }
        try
        {
            result.push_back(std::stoi(value));
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Skipping invalid lane value: [" << value << "]" << std::endl;
        }
    }
    return result;

}


std::string fetchData()
{

    std::cout<<"ENTERED PARSER"<<std::endl;
    std::string URL = "https://cwwp2.dot.ca.gov/data/d7/lcs/lcsStatusD07.json";


    CURL *handle = curl_easy_init();

    if (handle == nullptr)

    {
        std::cout << "Failed to initialize CURL" << std::endl;
        return "";
    }


    std::string httpData;
    long httpCode(0);

    curl_easy_setopt(handle, CURLOPT_URL,URL.c_str());

    curl_easy_setopt(handle,CURLOPT_IPRESOLVE,CURL_IPRESOLVE_V4);

    curl_easy_setopt(handle,CURLOPT_TIMEOUT,10L);

    curl_easy_setopt(handle,CURLOPT_FOLLOWLOCATION,1L);
    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,callback);

    curl_easy_setopt(handle,CURLOPT_WRITEDATA, &httpData);

    curl_easy_perform(handle);

    curl_easy_getinfo(handle,CURLINFO_RESPONSE_CODE,&httpCode);

    curl_easy_cleanup(handle);


    if(httpCode ==200)
    {
        std::cout << "Successful Response from" << URL << std::endl;

        return httpData;
    }
    std::cout << "Failed GET request. HTTP CODE: " << httpCode << std::endl;

    return "";
}


std::vector<ClosureData> parseClosureData(const std::string& jsonData){
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errors;

    std::istringstream stream(jsonData);

    Json::parseFromStream(builder,stream, &root, &errors);




    std::vector<ClosureData> closures;
    for (const auto& item : root["data"])
    {
        Json::Value record = item["lcs"];

        std::string route = record["location"]["begin"]["beginRoute"].asString();
        std::string direction = record["location"]["travelFlowDirection"].asString();
        std::string laneclosed = record["closure"]["lanesClosed"].asString();

        std::string begin_lat_str = record["location"]["begin"]["beginLatitude"].asString();
        std::string begin_lon_str =record["location"]["begin"]["beginLongitude"].asString();
        std::string end_lat_str = record["location"]["end"]["endLatitude"].asString();
        std::string end_lon_str = record["location"]["end"]["endLongitude"].asString();


        std::string total_lanes_str = record["closure"]["totalExistingLanes"].asString();



        std::string start_epoch_str = record["closure"]["closureTimestamp"]["closureStartEpoch"].asString();
        std::string end_epoch_str = record["closure"]["closureTimestamp"]["closureEndEpoch"].asString();

        if (begin_lat_str.empty() || begin_lon_str.empty() || end_lat_str.empty() || end_lon_str.empty()
            ||total_lanes_str.empty() || start_epoch_str.empty() || end_epoch_str.empty())
        {
            std::cout << "Incomplete closure data record SKIPPING" << std::endl;
            continue;
        }

        double begin_lat;
        double begin_lon;
        double end_lat;
        double end_lon;
        int totalexistinglanes;
        long long start_epoch;
        long long end_epoch;


        try{
            begin_lat = std::stod(begin_lat_str);
            begin_lon = std::stod(begin_lon_str);
            end_lat = std::stod(end_lat_str);
            end_lon = std::stod(end_lon_str);

            totalexistinglanes = std::stoi(total_lanes_str);

            start_epoch = std::stoll(start_epoch_str);
            end_epoch = std::stoll(end_epoch_str);

        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid totalExistingLanes. SKIPPING" <<std::endl;
            continue;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Out of Range in closure record. SKIPPING" << std::endl;
            continue;
        }
        auto PLC = parseLanesClosed(laneclosed,totalexistinglanes);



        ClosureData closes(route,begin_lat,begin_lon,end_lat,end_lon,direction,PLC,totalexistinglanes,start_epoch,end_epoch);
        closures.push_back(closes);
        }

    return closures;
};

std::vector<ClosureData> grabbing_data()
{
    std::string JsonData = fetchData();

    return parseClosureData(JsonData);

}
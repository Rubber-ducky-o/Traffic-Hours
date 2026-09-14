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


std::string grabbing_data(){
    std::string URL = "https://cwwp2.dot.ca.gov/data/d7/lcs/lcsStatusD07.json";

    CURL *handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL,URL.c_str());

    curl_easy_setopt(handle,CURLOPT_IPRESOLVE,CURL_IPRESOLVE_V4);

    curl_easy_setopt(handle,CURLOPT_TIMEOUT,10);

    curl_easy_setopt(handle,CURLOPT_FOLLOWLOCATION,1L);

    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,callback);

    curl_easy_setopt(handle,CURLOPT_WRITEDATA, httpData.get());

    curl_easy_perform(handle);

    curl_easy_getinfo(handle,CURLINFO_RESPONSE_CODE,&httpCode);

    curl_easy_cleanup(handle);

    if(httpCode ==200)
    {
        std::cout << "Successful Response from" << URL << std::endl;

        Json::Value root;
        Json::CharReaderBuilder builder;
        JSONCPP_STRING errors;
        std::istringstream stream(*httpData);


        Json::parseFromStream(builder,stream, &root, &errors);

        for (const std::string& key : root.getMemberNames())
        {
            std::cout << key << std::endl;
        }
        std::cout << root["data"][0] << std::endl;

    }
    else
    {
        std::cout << "Could not GET from" << handle << std::endl;
    }
    std::string complete = "yes";
    return complete;



};
#include <iostream>
#include <vector>
#include "parser.h"


int main(){

    std::cout << "STARTING MAIN" <<std::endl;

    std::vector<ClosureData> closures = grabbing_data();

    std::cout << "Parsed closures: " <<closures.size() << std::endl;

    for (size_t i= 0; i < closures.size() && i < 5; i++)
    {
        const auto& c = closures[i];
        std::cout << "Closure: " << i << std::endl;
        std::cout << "Route: " << c.route << std::endl;
        std::cout << "Start: " << c.begin_lat << ", " << c.begin_lon <<std::endl;
        std::cout << "End: " << c.end_lat << ", "<< c.end_lon <<std::endl;
        std::cout << "Direction: " << c.direction <<std::endl;
        std::cout << "Total lanes: " << c.total_existing_lanes << std::endl;

        std::cout << "Closed lanes: ";
        for (int lane : c.lanes_closed)
        {
            std::cout << lane << " ";
        }

        std::cout << "\nStart epoch: " <<c.start_epoch << std::endl;
        std::cout << "End epoch: " <<c.end_epoch << std::endl;
        std::cout << " --------------- \n";

    }


    std::cout << "ENDING MAIN" << std::endl;
    return 0;
}
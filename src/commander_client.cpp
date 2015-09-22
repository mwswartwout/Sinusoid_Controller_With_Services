#include <ros/ros.h>
#include <Sinusoid_Controller_With_Services/sinecontrol.h>
#include <iostream>
#include <string>

int main (int argc, char **argv) {
    ros::init( argc, argv, "commander_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<Sinusoid_Controller_With_Services::sinecontrol>("sine_control");
    Sinusoid_Controller_With_Services::sinecontrol message;
    std::string type;
    double value;

    while (ros::ok()) {
        std::cout << std::endl;
        std::cout << "Are you editing amplitude or frequency?";
        std::cout << std::endl;
        std::cin >> type;
        std::cout << std::endl;
        std::cout << "What value would you like to set the " << type << " to?";
        std::cout << std::endl;
        std::cin >> value;
        std::cout << std::endl;

        message.request.type = type;
        message.request.value = value;

        if (client.call(message)) {
           if (message.response.set) {
                std::cout << "The " << message.request.type << " was set to " << message.request.value;
                std::cout << std::endl;
            }
            else {
                std::cout << message.request.type << " was an invalid type and could not be set";
                std::cout << std::endl;
            }
        }
        else {
            ROS_ERROR("Failed to call service sine_control"); 
            return 1;
        }
    }

    return 0;
}

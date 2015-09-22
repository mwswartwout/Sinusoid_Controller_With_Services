#include <ros/ros.h>
#include <Sinusoid_Controller_With_Services/sinecontrol.h>
#include <iostream>
#include <string>

int main (int argc, char **argv) {
    ros::init( argc, argv, "commander_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<Sinusoid_Controller_With_Services::sinecontrol>("sine_control");
    
    //Sinecontrol message request has a type (amplitude or frequency) and a value
    Sinusoid_Controller_With_Services::sinecontrol message;
    std::string type; 
    double value;

    while (ros::ok()) {
        std::cout << std::endl;
        std::cout << "Are you editing amplitude or frequency? (x to quit)";
        std::cout << std::endl;
        std::cin >> type; // Get which variable user wants to change and save in type
        std::cout << std::endl;
        if (type.compare("x") == 0) {
            return 0; // Exit if user typed "x"
        }
        std::cout << "What value would you like to set the " << type << " to?";
        std::cout << std::endl;
        std::cin >> value; // Get what value user wants to change variable to
        std::cout << std::endl;

        message.request.type = type; // Store user input in message request
        message.request.value = value;

        if (client.call(message)) { // Send request
           if (message.response.set) { // If request was successful
                ROS_INFO( "The %s was set to %f" , message.request.type.c_str(), message.request.value); // Print what happened
                std::cout << std::endl;
            }
            else { // Else if message failed
                ROS_INFO( "%s was an invalid type and could not be set", message.request.type.c_str()); // Tell user the type they entered is invalid
                std::cout << std::endl;
            }
        }
        else {
            ROS_ERROR("Failed to call service sine_control"); // Declare error if service call failed
            return 1;
        }
    }

    return 0;
}

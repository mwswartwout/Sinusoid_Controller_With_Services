#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <Sinusoid_Controller_With_Services/sinecontrol.h>

double amplitude;
double frequency;

bool callback(Sinusoid_Controller_With_Services::sinecontrolRequest& request, Sinusoid_Controller_With_Services::sinecontrolResponse& response) {
    std::string type(request.type);
    
    if (type.compare("frequency") == 0) {
        frequency = request.value;
        response.set = true;
    }
    else if (type.compare("amplitude") == 0) {
        amplitude = request.value;
        response.set = true;
    }
    else {
        response.set = false;
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "services_commander"); // services_commander node
    ros::NodeHandle n;
    ros::Publisher command_publisher = n.advertise<std_msgs::Float64>("vel_cmd", 1); // publish to vel_cmd topic
    ros::ServiceServer service = n.advertiseService("sine_control", callback);
    ros::Rate naptime(10); // update @ 10hz

    amplitude = 0; // amplitude value for sine wave
    frequency = 0; // frequency value for sine wave
    double pi = 3.14159; // value of pi
    double t = 0; // current time in calculation
    double dt = 0.1; // timestep for calculation
    double sine; // sine output
    std_msgs::Float64 output; // message wrapper for sine output

    while (ros::ok()) {
        sine = amplitude * sin(2*pi*frequency*t); // Calculate sine value
        output.data = sine; // Store sine value in proper message format
        command_publisher.publish(output); // Publish value to vel_cmd topic
        t += dt; // Increment t by timeset dt
        ros::spinOnce();
        naptime.sleep();
    }
}

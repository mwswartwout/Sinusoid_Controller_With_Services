cmake_minimum_required(VERSION 2.8.3)
project(Sinusoid_Controller_With_Services)

## This is where you put all of the dependencies for the package.
## When using catkin_create_pkg, this is one of the places where 
## the dependencies are auto-placed.  If you need to add more later
## on, you need to put them in manually. 

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Tell catkin about your services here so it will properly generate
## the required header files

add_service_files(
	FILES
	sinecontrol.srv
)

## Message / service dependencies go here!  Ie, if you have a 
## geometry_msgs/Twist in your message / service, you should
## put 'geometry_msgs' here.
generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## This stuff tells catkin to compile your node!
add_executable(services_commander src/services_commander.cpp)
add_executable(commander_client src/commander_client.cpp)

target_link_libraries(services_commander ${catkin_LIBRARIES})
target_link_libraries(commander_client ${catkin_LIBRARIES})

cmake_minimum_required(VERSION 2.8.3)
project(sinusoid_controller_with_services)
find_package(catkin_simple REQUIRED)
catkin_simple()

#Executables
cs_add_executable(sinsusoid_controller_with_services src/services_commander.cpp)

cs_install()
cs_export()

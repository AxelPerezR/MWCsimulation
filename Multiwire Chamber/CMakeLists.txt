cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all) #Este es para visulizar

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc) 
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh) 

add_executable(sim sim.cc ${sources} ${headers}) #Creaciòn del ejecutable
target_link_libraries(sim ${Geant4_LIBRARIES}) #Para que encuentre las librerias

add_custom_target(Simulation DEPENDS sim)

cmake_minimum_required(VERSION 3.8)
project(Cchat)



set(CMAKE_CXX_STANDARD 11)
add_executable(JSON ChatBrain.c model.h uuid_test.c)


#add_executable(Client client.c Model.h)
#add_executable(Client2 client.c)
#add_executable(Server servidor.c)
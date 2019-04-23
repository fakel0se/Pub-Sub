cmake_minimum_required(VERSION 2.8)

project(pub-sub)

add_executable(publisher publisher.cpp)
add_executable(subscriber subscriber.cpp)

set(SOURCE_LIB uv amqpcpp pthread)

target_link_libraries(publisher ${SOURCE_LIB})
target_link_libraries(subscriber ${SOURCE_LIB})

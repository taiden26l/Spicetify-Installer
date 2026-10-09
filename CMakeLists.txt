cmake_minimum_required(VERSION 4.3)
project(Spicetify_Installer C)

set(CMAKE_C_STANDARD 23)
if(WIN32)
    set(RESOURCE_FILES "icon.rc")
endif()

add_executable(Spicetify_Installer main.c ${RESOURCE_FILES})

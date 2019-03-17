#项目名称
project(DawnOfTheCircle)
#代码路径
aux_source_directory(. DIR_TOOT_SRCS)
#允许gdb调试
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})

#生成可执行的文件
add_executable(${PROJECT_NAME} ${DIR_TOOT_SRCS})
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})



#find_package(SDL2 REQUIRED)


#引入外部头文件
#INCLUDE_DIRECTORIES(
#D:/work/C++/SDL2-devel-2.0.9-mingw/SDL2-2.0.9/i686-w64-mingw32/include/SDL2
#D:/work/C++/SDL2_image-devel-2.0.4-mingw/SDL2_image-2.0.4/i686-w64-mingw32/include/SDL2
#)

#引入的头文件所在的lib文件未知
#link_directories(
#D:/work/C++/SDL2-devel-2.0.9-mingw/SDL2-2.0.9/i686-w64-mingw32/lib
#D:/work/C++/SDL2_image-devel-2.0.4-mingw/SDL2_image-2.0.4/i686-w64-mingw32/lib 
#)

#生成可执行的文件
#add_executable(${PROJECT_NAME} ${DIR_TOOT_SRCS})



#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

#添加链接库,相同于指定-l参数
#target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image)
# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             lame

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
        src/main/cpp/lame.c
        src/main/cpp/util.c
        src/main/cpp/psymodel.c
        src/main/cpp/fft.c
        src/main/cpp/tables.c
        src/main/cpp/encoder.c
        src/main/cpp/newmdct.c
        src/main/cpp/quantize_pvt.c
        src/main/cpp/reservoir.c
        src/main/cpp/bitstream.c
        src/main/cpp/VbrTag.c
        src/main/cpp/version.c
        src/main/cpp/takehiro.c
        src/main/cpp/quantize.c
        src/main/cpp/vbrquantize.c
        src/main/cpp/gain_analysis.c
        src/main/cpp/id3tag.c
        src/main/cpp/set_get.c
        src/main/cpp/presets.c)

include_directories(src/main/cpp src/main/cpp/include)

add_definitions(-DHAVE_CONFIG_H -DSTDC_HEADERS -DHAVE_MEMCPY -DHAVE_STRCHR)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       lame

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )


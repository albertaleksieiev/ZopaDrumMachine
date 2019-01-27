# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/)
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp
        src/main/cpp/bridge/oscillator.cpp
        src/main/cpp/bridge/drum-machine.cpp
        src/main/cpp/bridge/piano.cpp
        src/main/cpp/bridge/media-player.cpp
        src/main/cpp/utils/kiss_fft.c
        src/main/cpp/AudioEngine.cpp
        src/main/cpp/instruments/SimpleOscillator.cpp
        src/main/cpp/instruments/MultiFrequencyOscillator.cpp
        src/main/cpp/instruments/DrumMachine.cpp
        src/main/cpp/instruments/Piano.cpp
        src/main/cpp/instruments/MediaPlayer.cpp
        src/main/cpp/google/SoundRecording.cpp
        src/main/cpp/effects/SimpleDelay.cpp
        src/main/cpp/google/Mixer.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

set(OBOE_DIR /Users/albert/android/oboe)

add_subdirectory(${OBOE_DIR} ./oboe)
include_directories(${OBOE_DIR}/include)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.


target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} oboe android)




TSTSRL will be an open source (like Linux) cross-platform (android/windows/linux/mac) twin-stick (like Geometry Wars) tactical shooter (like Rainbox Six) rogue-like (like Rogue)

Current TSTSRL is only an SDL window that only appears on windows, linux, and android. So there's a ways to go...

## Build Dependencies ##
This list will be fleshed out as we go. Currently:
* SDL2
* Platform specific build tools (gcc, make, ant, etc depending on platform)

## Build Instructions ##

There is a convenience script that automates the following steps called doit. To perform a build for a given platform simply run `./doit [platform]`, or `./doit [platform] run`.

Examples:
    ./doit l run # Build and run the linux version

    ./doit a run # Build and run the android version

    ./doit w run # Build and run the windows version

### Linux ###
    mkdir project
    cd project
    cmake ..
    make

Run with:
    bin/Linux/tstsrl

### Android ###
    mkdir project
    cd project
    cmake ..
    cd ../platform_specific/android
    ndk-build
    ant debug

Run with:
    adb install platform_specific/android/bin/SDLActivity-debug.apk
    adb shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity

### Windows ###
No instructions yet. Windows is not running from cmake or SDL2 yet.
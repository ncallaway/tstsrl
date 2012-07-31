#!/usr/bin/ruby
target_os = "linux"
run = false

if ARGV.length > 0
    if "linux".start_with?(ARGV[0])
        target_os = "linux"
    elsif "android".start_with?(ARGV[0])
        target_os = "android"
    elsif "windows".start_with?(ARGV[0])
        target_os = "windows"
    else
        puts "Desired target #{ARGV[0]} not understood. Defaulting to #{target_os}."
    end
end

if ARGV.length > 1
    if "run".start_with?(ARGV[1])
        run = true
    elsif "norun".start_with?(ARGV[1])
        run = false
    end
end

Dir.mkdir "project" unless File.directory? "project"
Dir.chdir "project"

if target_os == "linux"
    puts "Beginning linux build...\n"
    system 'cmake ..'
    system 'make'

    if run
        Dir.chdir "../bin/Linux"
        exec './tstsrl'
    end
end

if target_os == "android"
    puts "Beginning android build...\n"
    system 'cmake ..'
    Dir.chdir "../platform_specific/android"
    system 'ndk-build'
    system 'ant debug'
    system 'adb install -r bin/SDLActivity-debug.apk'

    if run
        system 'adb shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity'
    end
end

if target_os == "windows"
    puts "Beginning windows build...\n"
    system 'vcvars32 x86 & cmake -G "NMake Makefiles" ..'
    system 'vcvars32 x86 & nmake'
    
    if run
        Dir.chdir "../bin/windows"
        exec 'tstsrl.exe'
    end
end



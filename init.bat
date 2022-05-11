@echo off
set VCPKG_DEFAULT_TRIPLET=x64-windows-static
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
git checkout 0d7603c4efc351da97b43c1952ba943e76f9b35f
call bootstrap-vcpkg.bat
vcpkg install glfw3 glm nlohmann-json assimp stb magic-enum fmt crossguid
rmdir /s /q .git
cd ..
pause
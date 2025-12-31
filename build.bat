@echo off
cmake -B build
cmake --build build --config Release
cmake --install build --prefix ./Release
rmdir /s /q build
echo Done! Check the 'Release' folder
pause
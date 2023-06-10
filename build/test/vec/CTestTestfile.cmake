# CMake generated Testfile for 
# Source directory: C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec
# Build directory: C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/vec
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[specVecTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/vec/Debug/specVecTests.exe")
  set_tests_properties([=[specVecTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[specVecTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/vec/Release/specVecTests.exe")
  set_tests_properties([=[specVecTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[specVecTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/vec/MinSizeRel/specVecTests.exe")
  set_tests_properties([=[specVecTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[specVecTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/vec/RelWithDebInfo/specVecTests.exe")
  set_tests_properties([=[specVecTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/vec/CMakeLists.txt;0;")
else()
  add_test([=[specVecTests]=] NOT_AVAILABLE)
endif()

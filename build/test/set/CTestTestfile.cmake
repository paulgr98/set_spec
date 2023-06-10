# CMake generated Testfile for 
# Source directory: C:/Users/Pawel/Desktop/C++/specjalizacja/test/set
# Build directory: C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/set
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[speSetTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/set/Debug/speSetTests.exe")
  set_tests_properties([=[speSetTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[speSetTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/set/Release/speSetTests.exe")
  set_tests_properties([=[speSetTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[speSetTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/set/MinSizeRel/speSetTests.exe")
  set_tests_properties([=[speSetTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[speSetTests]=] "C:/Users/Pawel/Desktop/C++/specjalizacja/build/test/set/RelWithDebInfo/speSetTests.exe")
  set_tests_properties([=[speSetTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;14;add_test;C:/Users/Pawel/Desktop/C++/specjalizacja/test/set/CMakeLists.txt;0;")
else()
  add_test([=[speSetTests]=] NOT_AVAILABLE)
endif()

# CMake generated Testfile for 
# Source directory: /home/alex/Projects/quicklog
# Build directory: /home/alex/Projects/quicklog/buildresults
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[qkl-unittests]=] "/home/alex/Projects/quicklog/buildresults/tests/unittests/unittests")
set_tests_properties([=[qkl-unittests]=] PROPERTIES  DEPENDS "qkl-unittests-build" _BACKTRACE_TRIPLES "/home/alex/Projects/quicklog/CMakeLists.txt;83;add_test;/home/alex/Projects/quicklog/CMakeLists.txt;0;")
add_test([=[qkl-unittests-build]=] "/home/alex/opt/cmake-3.21.1-linux-x86_64/bin/cmake" "--build" "/home/alex/Projects/quicklog/buildresults" "--target" "unittests")
set_tests_properties([=[qkl-unittests-build]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/alex/Projects/quicklog/CMakeLists.txt;84;add_test;/home/alex/Projects/quicklog/CMakeLists.txt;0;")
subdirs("tests/unittests")
subdirs("tests/speed_test")

if(EXISTS "/home/plaiseek/Projects/mippp/build_mingw/test/cli_grb_test[1]_tests.cmake")
  include("/home/plaiseek/Projects/mippp/build_mingw/test/cli_grb_test[1]_tests.cmake")
else()
  add_test(cli_grb_test_NOT_BUILT cli_grb_test_NOT_BUILT)
endif()

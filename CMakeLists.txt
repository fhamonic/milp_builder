cmake_minimum_required(VERSION 3.12)

project(
  mippp
  VERSION 1.0
  DESCRIPTION
    "A modern interface for linear programming solvers using C++20 ranges and concepts."
  LANGUAGES CXX)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# ################### Options ####################
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTING "Enable Test Builds" OFF)
option(LINK_CBC "Link CBC" OFF)
option(LINK_GUROBI "Link Gurobi" OFF)
option(LINK_CPLEX "Link CPLEX" OFF)
option(LINK_SCIP "Link SCIP" OFF)

# ################### Modules ####################
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_MODULE_PATH})
include(GNUInstallDirs)
include(CompilerWarnings)

# ################### Packages ###################
find_package(range-v3)

if(${LINK_CBC})
  set(CBC_DIR "C:/Users/Plaiseek/Documents/Softwares/Cbc-releases.2.10.11-x86_64-w64-mingw64")
  set(CBC_INCLUDE_DIR "C:/Users/Plaiseek/Documents/Softwares/Cbc-releases.2.10.11-x86_64-w64-mingw64/include")
  find_package(CBC REQUIRED)
endif()
if(${LINK_GUROBI})
  find_package(GUROBI REQUIRED)
endif()  
if(${LINK_CPLEX})
  find_package(CPLEX REQUIRED)
endif()
if(${LINK_SCIP})
  find_package(SCIP REQUIRED)
endif()

# ############### Exported target ################
add_library(mippp INTERFACE)
target_include_directories(mippp
                           INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(mippp INTERFACE range-v3::range-v3)
# silence false positive warinings from range-v3 invoke.hpp
target_compile_options(mippp INTERFACE -Warray-bounds=0)
target_compile_options(mippp INTERFACE -fconcepts-diagnostics-depth=30)

# target_compile_definitions(mippp INTERFACE MIPPP_PREFERED_SOLVER=MIPPP_COIN)

if(${LINK_CBC})
  add_library(cbc_backend INTERFACE)
  target_compile_definitions(cbc_backend INTERFACE MIPPP_LINK_COINOR)
  target_include_directories(cbc_backend INTERFACE ${CBC_INCLUDE_DIR})
  target_link_libraries(cbc_backend INTERFACE ${CBC_LIBRARIES})

  target_link_libraries(mippp INTERFACE cbc_backend)
endif()
if(${LINK_GUROBI})
  add_library(gurobi_backend INTERFACE)
  target_compile_definitions(gurobi_backend INTERFACE MIPPP_LINK_GUROBI)
  target_include_directories(gurobi_backend INTERFACE ${GUROBI_INCLUDE_DIR})
  target_link_libraries(gurobi_backend INTERFACE ${GUROBI_LIBRARIES})

  target_link_libraries(mippp INTERFACE gurobi_backend)
endif()
if(${LINK_CPLEX})
  add_library(cplex_backend INTERFACE)
  target_compile_definitions(cplex_backend INTERFACE MIPPP_LINK_CPLEX)
  target_include_directories(cplex_backend INTERFACE ${CPLEX_INCLUDE_DIR})
  target_link_libraries(cplex_backend INTERFACE ${CPLEX_LIBRARIES})

  target_link_libraries(mippp INTERFACE cplex_backend)
endif()
if(${LINK_SCIP})
  add_library(scip_backend INTERFACE)
  target_compile_definitions(scip_backend INTERFACE MIPPP_LINK_SCIP)
  target_include_directories(scip_backend INTERFACE ${SCIP_INCLUDE_DIR})
  target_link_libraries(scip_backend INTERFACE ${SCIP_LIBRARIES})

  target_link_libraries(mippp INTERFACE scip_backend)
endif()

# ################### TESTS ######################
if(${ENABLE_TESTING} AND NOT ${CMAKE_CROSSCOMPILING})
  enable_testing()
  message("Building Tests.")
  set_project_warnings(mippp)
  add_subdirectory(test)
endif()

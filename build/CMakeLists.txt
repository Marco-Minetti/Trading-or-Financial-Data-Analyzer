cmake_minimum_required(VERSION 3.10)
project(FinancialDataAnalyzer)

set(CMAKE_CXX_STANDARD 17)

add_executable(FinancialDataAnalyzer main.c query_interface.c data_structures.c analytics.c)

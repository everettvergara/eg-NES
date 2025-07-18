﻿
project(eg_m6502)

# Ensure vcpkg integration is recognized
#if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#    set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/vcpkg-master/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
#endif()


#find_package(CURL REQUIRED)
find_package(Catch2 REQUIRED)


# Libs
# --
add_library(eg_m6502 STATIC
	"src/cycle.cpp"
	"src/mem.cpp"
	"src/m6502.cpp"
	"src/m6502_ins_lda.cpp"
	"src/m6502_ins_ldx.cpp"
	"src/m6502_ins_ldy.cpp"
	"src/m6502_ins_nop.cpp"
	"src/m6502_ins_inc.cpp"
	"src/m6502_ins_dec.cpp"
	"src/m6502_ins_dex.cpp"
	"src/m6502_ins_dey.cpp"
	"src/m6502_ins_inx.cpp" 
	"src/m6502_ins_iny.cpp"
	"src/m6502_ins_jmp.cpp"
	"src/m6502_ins_adc.cpp"

	"src/reg.cpp"
	"src/sr.cpp")
target_include_directories(eg_m6502 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")


# Test eg_m6502.lib
# --

add_executable (eg_m6502_run_test 
	"m6502_run_test.cpp"
	"test/src/m6502_tins_lda.cpp"
	"test/src/m6502_tins_ldx.cpp"
	"test/src/m6502_tins_ldy.cpp"
	"test/src/m6502_tins_nop.cpp"
	"test/src/m6502_tins_inc.cpp"
	"test/src/m6502_tins_dec.cpp"
	"test/src/m6502_tins_inx.cpp"
	"test/src/m6502_tins_iny.cpp"
	"test/src/m6502_tins_dex.cpp"
	"test/src/m6502_tins_dey.cpp"
	"test/src/m6502_tins_jmp.cpp"
	"test/src/m6502_tins_adc.cpp"

	"test/src/m6502_generic.cpp")

target_link_libraries(eg_m6502_run_test PRIVATE 
	eg_m6502 
	Catch2::Catch2WithMain)

target_include_directories(eg_m6502_run_test PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/include" 
	"${CMAKE_CURRENT_SOURCE_DIR}/test/include")


# Set C++20
# --
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET eg_m6502 PROPERTY CXX_STANDARD 20)
  set_property(TARGET eg_m6502_run_test PROPERTY CXX_STANDARD 20)
endif()

cmake_minimum_required(VERSION 2.8.8)
project(vtkProjTest)

set(VTK_REQUIRED_COMPONENTS
  vtkRenderingCore
  vtkRenderingOpenGL
  vtkCommonCore
  vtkGeovisCore
  vtkIOLegacy
  )

find_package(VTK NO_MODULE REQUIRED COMPONENTS ${VTK_REQUIRED_COMPONENTS})

file(COPY continents.vtk DESTINATION "${CMAKE_BINARY_DIR}")

include(${VTK_USE_FILE})

set(SOURCES main.cpp)

add_executable(run ${SOURCES})
target_link_libraries(run ${VTK_LIBRARIES})

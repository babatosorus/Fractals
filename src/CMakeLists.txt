		
set(FRACTALS_SRCS
  colour.cpp
  fractalGenerator.cpp
  mandelbrot.cpp
  viewport.cpp 
  bitmap.cpp 
)

add_library(Fractals ${FRACTALS_SRCS})

target_link_libraries(Fractals )

target_include_directories(
  Fractals
  PUBLIC
    ${INC_ROOT}
  PRIVATE
) 


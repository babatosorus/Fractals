		
set(FRACTALS_SRCS
  colour.cpp
  mandelbrot.cpp
  viewport.cpp 
  abstractImageWriter.cpp
  bitmapWriter.cpp 
  ${INC_ROOT}/fractalBuilder.h
)

add_library(Fractals ${FRACTALS_SRCS})

target_link_libraries(Fractals )

target_include_directories(
  Fractals
  PUBLIC
    ${INC_ROOT}
  PRIVATE
) 


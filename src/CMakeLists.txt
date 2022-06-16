		
set(FRACTALS_SRCS
  colour.cpp
  fractalBuilder.cpp
  mandelbrot.cpp
  viewport.cpp 
  abstractImageWriter.cpp
  bitmapWriter.cpp 
)

add_library(Fractals ${FRACTALS_SRCS})

target_link_libraries(Fractals )

target_include_directories(
  Fractals
  PUBLIC
    ${INC_ROOT}
  PRIVATE
) 


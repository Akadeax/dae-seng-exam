# Define sources and add executable
set(SOURCES
	"GameWinMain.h" "GameWinMain.cpp"
	"GameEngine.h" "GameEngine.cpp"
	"AbstractGame.h" "AbstractGame.cpp"
	"Game.h" "Game.cpp"
)

# the engine uses UNICODE, but _UNICODE is also used :(
add_compile_definitions(_UNICODE)
add_compile_definitions(UNICODE)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  lua::lua
  sol2::sol2
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Set output directories
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy lua folder to build output
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/lua
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/lua
)

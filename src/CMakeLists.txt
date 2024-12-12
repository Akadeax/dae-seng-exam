

# Define sources and add executable
set(SOURCES
	"GameWinMain.h" "GameWinMain.cpp"
	"GameEngine.h" "GameEngine.cpp"
	"AbstractGame.h" "AbstractGame.cpp"
	"Game.h" "Game.cpp"
)

add_compile_definitions(_UNICODE)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

# Set output directories
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

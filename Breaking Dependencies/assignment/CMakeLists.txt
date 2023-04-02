
add_executable(assignment program.cpp logger.cpp main.cpp itime_source.h
        itext_writer.h system_time_source.cpp
        system_time_source.h
        console_writer.cpp stream_writer.cpp
        )

list(APPEND TARGETS assignment)
set(TARGETS ${TARGETS} PARENT_SCOPE)

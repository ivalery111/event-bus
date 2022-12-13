function(set_compiler_flags target)
    option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

    set(COMMON_FLAGS
        -Wall                       # reasonable and standard
        -Wextra                     # reasonable and standard
        -Wshadow                    # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor          # warn the user if a class with virtual functions has a non-virtual destructor
        -pedantic                   # warn on language extensions
        -Wold-style-cast            # warn for c-style casts
        -Wcast-align                # warn for potential performance problem casts
        -Wunused                    # warn on anything being unused
        -Woverloaded-virtual        # warn if you overload (not override) a virtual function
        -Wpedantic                  # warn if non-standard C++ is used
        -Wconversion                # warn on type conversions that may lose data
        -Wsign-conversion           # warn on sign conversions
        -Wformat=2                  # warn on security issues around functions that format output (i.e., printf)
    )

    set(GCC_FLAGS ${COMMON_FLAGS}
        -Wmisleading-indentation    # warn if identation implies blocks where blocks do not exist
        -Wduplicated-cond           # warn if if / else chain has duplicated conditions
        -Wduplicated-branches       # warn if if / else branches have duplicated code
        -Wlogical-op                # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast              # warn if you perform a cast to the same type
        -Wnull-dereference          # warn if a null dereference is detected
        -Wuseless-cast              # warn if you perform a cast to the same type
        -Wdouble-promotion          # 
    )

    set(CLANG_FLAGS ${COMMON_FLAGS}
        -Wlifetime                  # shows object lifetime issues
        -Wimplicit-fallthrough      # warns when case statements fall-through. (Included with -Wextra in GCC, not in clang)
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message("[+]: Using GNU Compiler Flags")
        set(PROJECT_FLAGS ${GCC_FLAGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message("[+]: Using Clang Compiler Flags")
        set(PROJECT_FLAGS ${CLANG_FLAGS})
    endif()

    target_compile_options(${target} INTERFACE ${PROJECT_FLAGS})

endfunction()

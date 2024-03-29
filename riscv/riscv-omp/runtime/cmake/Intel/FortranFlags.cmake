#
#//===----------------------------------------------------------------------===//
#//
#//                     The LLVM Compiler Infrastructure
#//
#// This file is dual licensed under the MIT and the University of Illinois Open
#// Source Licenses. See LICENSE.txt for details.
#//
#//===----------------------------------------------------------------------===//
#

# This file holds Intel(R) C Compiler / Intel(R) C++ Compiler / Intel(R) Fortran Compiler (icc/icpc/icl.exe/ifort) dependent flags
# The flag types are:
#   1) Fortran Compiler flags

#########################################################
# icc Fortran Compiler flags (for creating .mod files)
function(append_fortran_compiler_specific_fort_flags input_fort_flags)
    set(local_fort_flags)
    #set(CMAKE_Fortran_FLAGS      "$ENV{FFLAGS}"   CACHE STRING "Fortran flags"  FORCE)
    #set(CMAKE_Fortran_FLAGS_RELEASE          ""   CACHE STRING "Fortran flags"  FORCE)
    #set(CMAKE_Fortran_FLAGS_DEBUG            ""   CACHE STRING "Fortran flags"  FORCE)
    #set(CMAKE_Fortran_FLAGS_RELWITHDEBINFO   ""   CACHE STRING "Fortran flags"  FORCE)
    if(${WINDOWS})
        append_fort_flags("-Qdiag-disable:177,5082")
        append_fort_flags("-Qsox")
        append_fort_flags("-nologo")
        append_fort_flags("-GS")
        append_fort_flags("-DynamicBase")
        append_fort_flags("-Zi")
        # On Linux and Windows Intel(R) 64 architecture we need offload attribute
        # for all Fortran entries in order to support OpenMP function calls inside device contructs
        if(${INTEL64})
            append_fort_flags("/Qoffload-attribute-target:mic")
        endif()
    else()
        if(${MIC})
            append_fort_flags("-mmic")
        endif()
        if(NOT ${MAC})
            append_fort_flags("-sox")
            if(${INTEL64} AND ${LINUX})
                append_fort_flags("-offload-attribute-target=mic")
            endif()
        endif()
    endif()
    set(${input_fort_flags} ${${input_fort_flags}} "${local_fort_flags}" PARENT_SCOPE)
endfunction()

# Project name.
LIB_NAME = cxx-general

# Version information.
LIB_VER_INTERFACE = 0
LIB_VER_MINOR     = 0

# Prefixes/Suffixes.
SUF_OBJ  = .o
SUF_SOBJ = .os
PRE_SHLIB = lib
SUF_SHLIB = .so

# ArbInt.
ARBINT_NAME  = ArbInt
ARBINT_DIR   = ${ARBINT_NAME}
ARBINT_ONAME = ${ARBINT_NAME}${SUF_OBJ}
ARBINT_SNAME = ${ARBINT_NAME}${SUF_SOBJ}
ARBINT_OFILE = ${ARBINT_DIR}/${ARBINT_ONAME}
ARBINT_SFILE = ${ARBINT_DIR}/${ARBINT_SNAME}

# Arb.
ARB_NAME  = Arb
ARB_DIR   = ${ARB_NAME}
ARB_ONAME = ${ARB_NAME}${SUF_OBJ}
ARB_SNAME = ${ARB_NAME}${SUB_SOBJ}
ARB_OFILE = ${ARB_DIR}/${ARB_ONAME}
ARB_SFILE = ${ARB_DIR}/${ARB_SNAME}

# Timestamp.
TIMESTAMP_NAME  = Timestamp
TIMESTAMP_DIR   = ${TIMESTAMP_NAME}
TIMESTAMP_ONAME = ${TIMESTAMP_NAME}${SUF_OBJ}
TIMESTAMP_SNAME = ${TIMESTAMP_NAME}${SUF_SOBJ}
TIMESTAMP_OFILE = ${TIMESTAMP_DIR}/${TIMESTAMP_ONAME}
TIMESTAMP_SFILE = ${TIMESTAMP_DIR}/${TIMESTAMP_SNAME}

# POSIXFile.
POSIXFILE_NAME  = POSIXFile
POSIXFILE_DIR   = ${POSIXFILE_NAME}
POSIXFILE_ONAME = ${POSIXFILE_NAME}${SUF_OBJ}
POSIXFILE_SNAME = ${POSIXFILE_NAME}${SUF_SOBJ}
POSIXFILE_OFILE = ${POSIXFILE_DIR}/${POSIXFILE_ONAME}
POSIXFILE_SFILE = ${POSIXFILE_DIR}/${POSIXFILE_SNAME}

# Library config.
LIB_SONAME = ${PRE_SHLIB}${LIB_NAME}${SUF_SHLIB}
LIB_OBJS = "${ARBINT_SFILE}" "${ARB_SFILE}" "${TIMESTAMP_SFILE}" "${POSIXFILE_SFILE}"

# Files to clean.
CLEAN_TARGETS += "${LIB_SONAME}"

# Phony targets.
.PHONY : clean

# The library itself.
${LIB_SONAME} : ${LIB_OBJS}
	g++ -o ${LIB_SONAME} ${LIB_OBJS}

# Clean up.
clean :
	rm -f ${CLEAN_TARGETS}

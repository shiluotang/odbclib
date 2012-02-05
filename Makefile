#MinGW 5.1.6
.PHONY:clean tidy rebuild
SRCDIR		=	src
LIBDIR		=	lib
DOCSDIR		=	docs
BUILDDIR	=	build

CC		=	g++
SRCEXT		=	cpp
DEPEXT		=	depend
RM		=	del /f /q
MKDIR		=	mkdir
RMDIR		=	rmdir /q /s
FLAGS		=	-Wall -O3 #-save-temps
LINKFLAGS	=	-static-libgcc -static-libstdc++ 
INCS		=
LIBPATHS	=	-L"${LIBDIR}"
LIBS		=	-lodbc32
EXTERNLIBS	=	${patsubst ${LIBDIR}/%,${BUILDDIR}/%,${wildcard ${LIBDIR}/*.dll}}
SRCT		=	*.${SRCEXT}
SRCS		+=	${SRCT}
SRCS		+=	*/${SRCT}
SRCS		+=	*/*/${SRCT}
SRCS		+=	*/*/*/${SRCT}
SRCS		+=	*/*/*/*/${SRCT}
SRCS		+=	*/*/*/*/*/${SRCT}
SRC		=	${wildcard ${addprefix ${SRCDIR}/,${SRCS}}}
OBJ		=	${patsubst ${SRCDIR}/%.${SRCEXT},${BUILDDIR}/%.o,${SRC}}
DEP		=	${patsubst ${SRCDIR}/%.${SRCEXT},${BUILDDIR}/%.${DEPEXT},${SRC}}
BIN		=	${BUILDDIR}/${notdir ${CURDIR}.exe}

build: ${BIN} ${EXTERNLIBS}
rebuild: tidy build
${BUILDDIR}/%.dll:${LIBDIR}/%.dll
	@echo copy lib ${<}	
	@copy ${subst /,\,${<}} ${subst /,\,${@}} /Y
${BIN}: ${OBJ}
	@echo make target: ${BIN}
	@${CC} ${LINKFLAGS} $^ ${LIBPATHS} ${LIBS} ${INCS} -o $@
prepare:
	@echo prepare folders
	@if not exist ${BUILDDIR} (${MKDIR} ${BUILDDIR} && @echo make directory: ${BUILDDIR})
	@if not exist ${DOCSDIR} (${MKDIR} ${DOCSDIR} && @echo make directory: ${DOCSDIR})
	@if not exist ${subst /,\,${dir ${@}}} (${MKDIR} ${subst /,\,${dir ${@}}} && @echo make directory: ${subst /,\,${dir ${@}}})
	@xcopy ${SRCDIR} ${BUILDDIR} /T /E
clean:
	@echo remove build directory and docs directory
	@if exist ${BUILDDIR} (@${RMDIR} ${BUILDDIR})
	@if exist ${DOCSDIR} (@${RMDIR} ${DOCSDIR})
tidy:
	@echo tidy dependencies, objects and binaries only
	${foreach file,${subst /,\,${OBJ}},@if exist ${file} (${RM} ${file}) &&}@echo on
	${foreach file,${subst /,\,${DEP}},@if exist ${file} (${RM} ${file}) &&}@echo on

sinclude ${DEP}
${BUILDDIR}/%.${DEPEXT}:${SRCDIR}/%.${SRCEXT}
	@if not exist ${BUILDDIR} (${MKDIR} ${BUILDDIR} && @echo make directory: ${BUILDDIR})
	@if not exist ${subst /,\,${dir ${@}}} (${MKDIR} ${subst /,\,${dir ${@}}} && @echo make directory: ${subst /,\,${dir ${@}}})
	@echo make dependency for ${patsubst ${SRCDIR}/%.${SRCEXT},${BUILDDIR}/%.o,${<}}
	@${CC} -MM -MT ${patsubst ${SRCDIR}/%.${SRCEXT},${BUILDDIR}/%.o,${<}} ${<} > ${@}
	@echo		@@echo make object: ${patsubst ${SRCDIR}/%.${SRCEXT},${BUILDDIR}/%.o,${<}} >> ${@}
	@echo		@@$${CC} $${FLAGS} $${INCS} -c -o $$@ $${filter %%.${SRCEXT},$$^^} >> ${@}


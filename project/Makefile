
SRC=src
INC=include
BIN=bin
DOCS=docs

HDRS=$(wildcard ${INC}/*.h)
SRCS=$(wildcard ${SRC}/*.cpp)
OBJS=$(patsubst ${SRC}/%.cpp, ${BIN}/%.o, ${SRCS})
TARGET_BINARY=${BIN}/starter1

CXX ?= clang++
CXXFLAGS += -I${INC} -g -std=c++14 -pedantic-errors -Wall -Wextra
CXXFLAGS += -Wsign-conversion -Wno-unused -Wno-delete-non-virtual-dtor
all: ${TARGET_BINARY}

${TARGET_BINARY}: ${OBJS}
	${CXX} ${OBJS} -o $@ -L/usr/X11R6/lib -lm -lpthread -lX11 ${LDFLAGS}

${BIN}/%.o: ${SRC}/%.cpp ${HDRS}
	${CXX} ${CXXFLAGS} -c $< -o $@

.PHONY: clean
clean:
	${RM} ${OBJS}
	${RM} ${TARGET_BINARY}

CC = g++
#---------------------------------------------------------
CPPFLAGS=-I../include
LDFLAGS=-pthread
#---------------------------------------------------------
MAIN="concurrent_example"
#---------------------------------------------------------
all: ${MAIN}

${MAIN}: 
	${CC} ${MAIN}.cpp -o ${MAIN} ${CPPFLAGS} ${LDFLAGS}


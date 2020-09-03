CC=clang++
INCLUDES=-I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -I${WELD_HOME}/weld-capi

LDFLAGS=-L${WELD_HOME}/target/release/
LIBS=-lweld

.PHONY: all clean jar

all:
	${CC} ${INCLUDES} ${LDFLAGS} ${LIBS} -mavx2 -O3 -shared lib.cpp -fPIC -o libweld_java.so

jar:
	ls

clean:
	rm -rf *.so


GLEWLIB= -lGLEW

OS := $(shell uname)
ifeq ($(OS), Darwin)
# Run MacOS commands
OPENGLLIB= -framework OpenGL
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
else
# check for Linux and run other commands
OPENGLLIB= -lGL
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
endif

LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-g -I/usr/local/include -std=c++11

BIN=cg_san
SRC_MAIN=cg_san.cpp 

INCLUDES_FW=gl_framework.hpp
SRC_FW=gl_framework.cpp 
OBJ_FW=gl_framework.o

INCLUDES_SU=shader_util.hpp
SRC_SU=shader_util.cpp 
OBJ_SU=shader_util.o

INCLUDES_OBJ=object.hpp
SRC_OBJ=object.cpp
OBJ_OBJ=object.o

INCLUDES_CHAR1=character1.hpp
SRC_CHAR1=character1.cpp
OBJ_CHAR1=character1.o

INCLUDES_CHAR2=character2.hpp
SRC_CHAR2=character2.cpp
OBJ_CHAR2=character2.o

INCLUDES_TEXTURE=texture.hpp
SRC_TEXTURE=texture.cpp
OBJ_TEXTURE=texture.o

all: $(BIN)

$(OBJ_FW): $(INCLUDES_FW) $(SRC_FW)
	g++ -c $(CPPFLAGS) $(SRC_FW) $(LDFLAGS) $(LIBS)

$(OBJ_SU): $(INCLUDES_SU) $(SRC_SU)
	g++ -c $(CPPFLAGS) $(SRC_SU) $(LDFLAGS) $(LIBS)

$(OBJ_OBJ): $(INCLUDES_OBJ) $(SRC_OBJ)
	g++ -c $(CPPFLAGS) $(SRC_OBJ) $(LDFLAGS) $(LIBS)

$(OBJ_CHAR1): $(INCLUDES_CHAR1) $(SRC_CHAR1) 
	g++ -c $(CPPFLAGS) $(SRC_CHAR1) $(LDFLAGS) $(LIBS)

$(OBJ_CHAR2): $(INCLUDES_CHAR2) $(SRC_CHAR2) 
	g++ -c $(CPPFLAGS) $(SRC_CHAR2) $(LDFLAGS) $(LIBS)

$(OBJ_TEXTURE): $(INCLUDES_TEXTURE) $(SRC_TEXTURE) 
	g++ -c $(CPPFLAGS) $(SRC_TEXTURE) $(LDFLAGS) $(LIBS)

$(BIN): $(OBJ_FW) $(OBJ_SU) $(OBJ_OBJ) $(OBJ_CHAR1) $(OBJ_CHAR2) $(OBJ_TEXTURE) $(SRC_MAIN) 
	g++ $(CPPFLAGS) $(SRC_MAIN) $(OBJ_FW) $(OBJ_SU) $(OBJ_OBJ) $(OBJ_CHAR1) $(OBJ_CHAR2) $(OBJ_TEXTURE) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)

# Compila programas do curso de OpenGL
# digite: make teste-make
# para executar: teste-make

CC = g++
CFLAGS = -O2
XLIBS = -L/usr/X11/lib -L/usr/X11R6/lib -lX11 

##### MACROS #####

INCDIR = /usr/include
LIBDIR = /usr/lib

GL_LIBS = -L$(LIBDIR) -lglut -lGLU -lGL -lm -lpng $(XLIBS)

LIB_DEP = $(LIBDIR)/$(GL_LIB)

##### RULES #####

.SUFFIXES:
.SUFFIXES: .c .cpp

.c: $(LIB_DEP)
	$(CC) -I$(INCDIR) $(CFLAGS) $< -o $@ $(GL_LIBS)

##### TARGETS ######

clean:
	-rm *.o *~
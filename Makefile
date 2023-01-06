######### Default action
.DEFAULT_GOAL:= build

######### Compiler option
CC:=/usr/bin/gcc
CFLAGS:=-Wall
LDLIBS:=-lm

######### Directories section
SRCDIR=src
OBJDIR=build
DISTDIR=dist

######### Target
TARGET=serialSwitch

INCS = $(wildcard *.h $(foreach fd, $(SRCDIR), $(fd)/*.h))
SRCS = $(wildcard *.c $(foreach fd, $(SRCDIR), $(fd)/*.c))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:c=o)) 
INC_DIRS = $(addprefix -I, $(SRCDIR))

######### Executable linking
$(TARGET): $(OBJS)
	$(CC) -o $(DISTDIR)/$(TARGET) $(OBJS)

######### Objects compiling
$(OBJDIR)/%.o: %.c $(INCS)	
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(SRCDIR)

prepare: 
	@echo "Create output directories"	
	mkdir build
	mkdir dist
	
build: prepare $(TARGET)
	@echo "Building..... target wil be in ./dist"
	
clean:
	@echo "Cleaning compiled files and executables"
	rm -Rf ${OBJDIR}
	rm -Rf $(DISTDIR)

install:
	@echo "Copy in /usr/local/bin"
	cp ./dist/serialSwitch /usr/bin/serialSwitch

uninstall:
	@echo "Remove from /usr/local/bin"
	rm -f /usr/bin/serialSwitch
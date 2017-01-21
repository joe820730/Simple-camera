OBJDIR = ./obj
OBJECTS = easycam.o
OBJ := $(foreach obj, $(OBJECTS), $(OBJDIR)/$(obj))

CC = g++
FLAGS = -Wall -g -O3 -std=c++11
LIBS = -lraspicam -lraspicam_cv -lm -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_highgui 

TARGET = bin/main.exec

vpath %.cpp ./

all: create_folders $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(FLAGS) 

$(OBJDIR)/%.o: %.cpp
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)

create_folders:
	mkdir -p bin/
	mkdir -p obj/

clean:
	rm -f obj/*.o
	rm -f bin/*.exec

.PHONY: all clean

CC=g++
CFLAGS=-c -Wall
AR=ar
ARFLAGS=rcs
OUTPUT_DIR=obj
SOURCES=source/document.cpp source/element.cpp  source/exception.cpp
OBJECTS=$(SOURCES:.cpp=.o) source/cJSON.o
#_OBJECTS=$(SOURCES:.cpp=.o) source/cJSON.o
#OBJECTS=$(patsubst source/%,$(OUTPUT_DIR)/%,$(_OBJECTS))
LIBRARY=source/libjv_json.a

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

all: $(SOURCES) $(LIBRARY)

source/cJSON.o: source/cJSON/cJSON.c 
	gcc -c $(CFLAGS) source/cJSON/cJSON.c -o $*.o

# compile and generate dependency info
%.o : %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d

# link to a library
$(LIBRARY): $(OBJECTS) 
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

# remove compilation products
clean:
	del /f source\libjv_json.a 
	del /f source\*.o 
	del /f source\*.d

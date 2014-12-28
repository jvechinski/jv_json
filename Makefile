CC=g++
CFLAGS=-Wall 
CPPFLAGS=$(CFLAGS) -Wno-c++0x-compat
AR=ar
ARFLAGS=rcs
OUTPUT_DIR=obj
SOURCES=source/document.cpp \
        source/element.cpp  \
        source/element_array.cpp \
        source/element_boolean.cpp \
        source/element_iterator.cpp \
        source/element_object.cpp \
        source/exception.cpp \
        source/native_type.cpp 
OBJECTS=$(SOURCES:.cpp=.o) source/cJSON.o
#_OBJECTS=$(SOURCES:.cpp=.o) source/cJSON.o
#OBJECTS=$(patsubst source/%,$(OUTPUT_DIR)/%,$(_OBJECTS))
LIBRARY=source/libjv_json.a

all: $(SOURCES) $(LIBRARY)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

source/cJSON.o: source/cJSON/cJSON.c 
	gcc -c $(CFLAGS) source/cJSON/cJSON.c -o $*.o

# compile and generate dependency info
%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $*.cpp -o $*.o
	$(CC) -MM $(CPPFLAGS) -MQ $*.o $*.cpp > $*.d

# link to a library
$(LIBRARY): $(OBJECTS) 
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

# remove compilation products
clean:
	del /f source\libjv_json.a 
	del /f source\*.o 
	del /f source\*.d

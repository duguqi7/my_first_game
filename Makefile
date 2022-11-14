PREFIX = 
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++

SOURCE_DIRS = .
SOURCE_DIRS += src

SOURCES  = $(foreach dir, $(SOURCE_DIRS), $(wildcard $(dir)/*))
CSOURCES = $(filter %.c, $(SOURCES))
CXXSOURCES = $(filter %.cpp, $(SOURCES))

INCLUDE_DIRS = -I ./include
LIBS_DIRS = -L 
CFLAGS = -g -Wall
CXXFLAGS = -g -Wall
LDFLAGS = -lpthread

TARGET = game
COBJECTS  =$(patsubst %.c,%.o,$(CSOURCES))
CXXOBJECTS  =$(patsubst %.cpp,%.o,$(CXXSOURCES))

$(TARGET):$(COBJECTS) $(CXXOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS_DIRS) $(LDFLAGS)
$(COBJECTS):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)
$(CXXOBJECTS):%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_DIRS)

.PHONY:clean
clean:
	rm -rf $(COBJECTS) $(CXXOBJECTS) $(TARGET)
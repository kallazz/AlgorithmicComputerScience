CXX = g++
CXXFLAGS = -std=c++23 -Wall -O3
TARGET = compressionTool
OBJS = main.o codes.o compression.o lzw.o entropy.o fileUtils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp codes.hpp compression.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

codes.o: codes.cpp codes.hpp compression.hpp lzw.hpp entropy.hpp fileUtils.hpp
	$(CXX) $(CXXFLAGS) -c codes.cpp

compression.o: compression.cpp compression.hpp
	$(CXX) $(CXXFLAGS) -c compression.cpp

lzw.o: lzw.cpp lzw.hpp
	$(CXX) $(CXXFLAGS) -c lzw.cpp

entropy.o: entropy.cpp entropy.hpp
	$(CXX) $(CXXFLAGS) -c entropy.cpp

fileUtils.o: fileUtils.cpp fileUtils.hpp
	$(CXX) $(CXXFLAGS) -c fileUtils.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
LDFLAGS := -fopenmp
CXXFLAGS := -fopenmp -Wall -g
OPTFLAGS := -O1

mc_test: $(OBJ_FILES)
	g++ $(CXXFLAGS) $(OPTFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) $(OPTFLAGS) -c $@ $<


clean: 
	\rm -f *.o mc_test

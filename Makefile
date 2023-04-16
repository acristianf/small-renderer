SRC_DIR := ./src/
BUILD_DIR := ./build/

FILES := $(wildcard $(SRC_DIR)*.cpp)

INC_DIRS := $(SRC_DIR)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))
# DEPS = $(INC_DIR)tgaimage.h

CPP_FLAGS := $(INC_FLAGS) -Wall -MMD -MP -O3 

small-renderer: $(FILES)
	g++ $(CPP_FLAGS) $(FILES) -o $(BUILD_DIR)main.exe

run: small-renderer
	$(BUILD_DIR)main.exe

profile: $(FILES)
	g++ -no-pie -pg $(CPP_FLAGS) $(FILES) -o $(BUILD_DIR)main.exe
	$(BUILD_DIR)main.exe
	gprof -b -p $(BUILD_DIR)main.exe gmon.out

clean:
	rm $(BUILD_DIR)*.*

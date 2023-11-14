RUST_LIB_DIR := rust
RUST_LIB_NAME := my_library
RUST_LIB := target/debug/lib$(RUST_LIB_NAME).a
CPP_SRC := test.cpp
CPP_EXE := test
CPP_FLAGS := -std=c++11

.PHONY: all rust_lib cpp_program clean

all: rust_lib cpp_program

rust_lib:
	cd $(RUST_LIB_DIR) && cargo build

cpp_program:
	g++ $(CPP_FLAGS) -o $(CPP_EXE) $(CPP_SRC) -L$(RUST_LIB_DIR)/target/debug -l$(RUST_LIB_NAME) -ldl

clean:
	cd $(RUST_LIB_DIR) && cargo clean
	rm -f $(CPP_EXE)
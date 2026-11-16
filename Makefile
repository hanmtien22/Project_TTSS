# Makefile cho Linux/WSL va Git Bash tren Windows (MSYS2 g++ + mingw32-make).
# Tren cmd thuan cua Windows thi dung build.bat.
#
#   make            # build tat ca chuong trinh co trong src/dot, src/matmul
#   make dot        # chi build tich vo huong
#   make matmul     # chi build nhan ma tran
#   make clean
#
# Quy uoc ten file: *_mpi.cpp va *_hybrid.cpp duoc build kem MPI,
# cac file con lai chi can g++ + OpenMP.

CXX       ?= g++
CXXFLAGS  ?= -O2 -std=c++17 -Wall -Wextra
OMPFLAGS  := -fopenmp
SIMDFLAGS := -mavx2 -mfma
INC       := -Iinclude

BIN := bin
OBJ := build

# ---- MPI -------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
  EXE    := .exe
  MPICXX ?= $(CXX)
  ifdef MSMPI_INC
    # MS-MPI SDK tu dat bien MSMPI_INC, MSMPI_LIB64 khi cai dat.
    # Doi \ thanh / de dau \ cuoi duong dan khong nuot mat dau ".
    MPIFLAGS ?= -I"$(subst \,/,$(MSMPI_INC))" -L"$(subst \,/,$(MSMPI_LIB64))" -lmsmpi
  else
    # Goi mingw-w64-ucrt-x86_64-msmpi cua MSYS2 da co san header va lib.
    MPIFLAGS ?= -lmsmpi
  endif
else
  EXE    :=
  MPICXX ?= mpicxx
  MPIFLAGS ?=
endif

# ---- Danh sach chuong trinh -----------------------------------------------
DOT_SRC    := $(wildcard src/dot/*.cpp)
MATMUL_SRC := $(wildcard src/matmul/*.cpp)
KERNEL_SRC := $(wildcard src/kernels/*.cpp)

DOT_PROGS    := $(patsubst src/dot/%.cpp,$(BIN)/%$(EXE),$(DOT_SRC))
MATMUL_PROGS := $(patsubst src/matmul/%.cpp,$(BIN)/%$(EXE),$(MATMUL_SRC))
KERNEL_OBJS  := $(patsubst src/kernels/%.cpp,$(OBJ)/kernels/%.o,$(KERNEL_SRC))

HEADERS := $(wildcard include/*.h)

# $(call is_mpi,ten) -> khac rong neu ten chua _mpi hoac _hybrid
is_mpi = $(or $(findstring _mpi,$1),$(findstring _hybrid,$1))
# $(call compile,src,out,extra) -> chon g++ hoac MPI theo ten file
compile = $(if $(call is_mpi,$(notdir $1)),\
	$(MPICXX) $(CXXFLAGS) $(OMPFLAGS) $(INC) $1 $3 -o $2 $(MPIFLAGS),\
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) $(INC) $1 $3 -o $2)

.PHONY: all dot matmul clean

all: dot matmul

dot: $(DOT_PROGS)

matmul: $(MATMUL_PROGS)

$(BIN)/%$(EXE): src/dot/%.cpp $(HEADERS)
	@mkdir -p $(BIN)
	$(call compile,$<,$@,)

$(BIN)/%$(EXE): src/matmul/%.cpp $(KERNEL_OBJS) $(HEADERS)
	@mkdir -p $(BIN)
	$(call compile,$<,$@,$(KERNEL_OBJS))

# Kernel nhan khoi duoc build rieng voi co AVX2/FMA
$(OBJ)/kernels/%.o: src/kernels/%.cpp $(HEADERS)
	@mkdir -p $(OBJ)/kernels
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) $(SIMDFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(BIN) $(OBJ)

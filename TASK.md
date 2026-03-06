# TASK

## Objective

Create the **initial MVP project skeleton** for the FusionANNS repository.

The goal is to produce a **minimal, clean, compilable C++20 codebase**
that demonstrates a simple vector search example.

This task is about **structure**, not optimization.

---

# Requirements

The implementation must:

- use **C++20**
- use **CMake**
- build successfully on Linux
- contain a minimal runnable example
- have a clean directory structure
- avoid unnecessary dependencies

Do NOT implement advanced ANN algorithms yet.

---

# Project structure

The repository should contain the following files.

```

CMakeLists.txt

include/fusionanns/vector.h  
include/fusionanns/distance.h  
include/fusionanns/index.h

src/vector.cpp  
src/distance.cpp  
src/flat_index.cpp  
src/main.cpp

tests/basic_test.cpp

```

Do not add additional directories unless necessary.

---

# Component specifications

## Vector

File:

```

include/fusionanns/vector.h  
src/vector.cpp

```

Implement a simple vector class.

Example structure:

```

class Vector {  
public:  
Vector(size_t dim);  
Vector(const std::vector& data);

```
size_t dim() const;
float operator[](size_t i) const;
```

private:  
std::vector data_;  
};

```

Responsibilities:

- store float vector data
- return dimension
- allow element access

Do NOT add SIMD or fancy memory optimizations.

---

# Distance functions

Files:

```

include/fusionanns/distance.h  
src/distance.cpp

```

Provide functions:

```

float l2_distance(const Vector& a, const Vector& b);  
float inner_product(const Vector& a, const Vector& b);

```

Implementation should be simple loops.

---

# Index interface

File:

```

include/fusionanns/index.h

```

Define a small abstract interface:

```

class Index {  
public:  
virtual ~Index() = default;

```
virtual void add(const Vector& v) = 0;

virtual size_t search(
const Vector& query,
size_t k,
std::vector<size_t>& results
) const = 0;
```

};

```

This interface will allow multiple index implementations later.

---

# Flat index implementation

File:

```

src/flat_index.cpp

```

Implement a brute-force index that:

- stores vectors
- performs linear scan search

Use L2 distance.

The search function should:

1. compute distances to all stored vectors
2. return the indices of the k nearest vectors

Use a simple partial sort or priority queue.

No performance optimizations are required.

---

# Example program

File:

```

src/main.cpp

```

The program should:

1. create several vectors
2. insert them into the index
3. perform a query
4. print the nearest neighbors

Example flow:

```

create index  
add vectors  
query vector  
print results

```

The program should compile to an executable named:

```

fusionanns

```

---

# CMake requirements

The project must use a minimal CMake configuration.

Requirements:

- C++20 standard
- create library target for core code
- create executable target
- compile tests

Example targets:

- `fusionanns_core`
- `fusionanns`

---

# Tests

File:

```

tests/basic_test.cpp

```

Add a minimal test that:

- creates vectors
- computes a distance
- runs a simple search

The test can simply print results if no test framework is used.

Do not add heavy test frameworks.

---

# Definition of Done

The task is complete when:

- the project builds successfully
- the executable runs
- a small vector search example works
- the code structure matches the specification
- the repository remains small and readable

---

# Constraints

Do NOT add:

- SIMD
- OpenMP
- GPU code
- advanced ANN algorithms
- external dependencies
- complex template systems

Those will be added later.

Focus only on creating a **clean starting point**.
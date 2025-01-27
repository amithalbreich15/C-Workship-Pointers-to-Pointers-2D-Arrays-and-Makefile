# Pointers-to-Pointers-2D-Arrays-and-Makefile
### Advanced Matrix Operations Library

---

### Overview  

This project involves implementing a C library to support advanced operations on two-dimensional arrays (matrices) of type `double`. The library focuses on both functionality and efficiency, allowing the creation of matrices, concatenation by rows/columns, element access by indices, slicing submatrices, and more.  

All functionality is based on a defined `matrix` structure, which includes:  
- A dynamic two-dimensional array (`double** data`) for storing matrix values.  
- Fields for the number of rows (`n_rows`) and columns (`n_columns`).  

---

### Key Features  

1. **Matrix Creation:**  
   - A function to create a new matrix, initializing all elements to `0.0`. Handles errors such as invalid dimensions or memory allocation failures.  

2. **Element Access:**  
   - Retrieve a pointer to an element at a specified row and column index. Returns error messages for invalid indices.  

3. **Matrix Slicing:**  
   - Extract a submatrix based on row and column index ranges.  

4. **Matrix Concatenation:**  
   - Concatenate two matrices horizontally or vertically. Ensures compatibility of dimensions before merging.  

5. **Transpose Operation:**  
   - Return a new matrix that is the transpose of the input matrix.  

6. **Matrix Flattening:**  
   - Convert a matrix into a dynamically allocated 1D array, preserving row-major order.  

7. **Memory Management:**  
   - Free allocated memory to avoid leaks, ensuring no dangling pointers.  

---

### Additional Requirements  

- Implementations must avoid modifying the original matrix structure (`struct matrix`).  
- Ensure the absence of memory leaks, validated with tools like `valgrind`.  
- All functions should handle `NULL` pointers gracefully.  
- No use of global variables or magic numbers; leverage `#define` where necessary.  

---

### Compilation and Testing  

- Use a `Makefile` to automate compilation:  
  - Compile `ex3.c` into `matrix_lib.o` using appropriate flags.  
  - Ensure compatibility with provided headers (`ex3.h`).  

- Submission includes:  
  - `Makefile`, `ex3.c`, and `ex3.h`.  
  - Verify functionality using a custom `main` program and School Solution (`school_solution_x.o`).  

- Compilation flags:  
  ```
  gcc -Wextra -Werror -Wall -Wvla -std=c99 ex3.c main.c -o ex3
  ```  

---

### Pre-Submission Checklist  

- Ensure the code compiles without warnings or errors using the specified flags.  
- Test with the provided School Solution files to validate behavior.  
- Run the pre-submission script on the school servers for final checks:  
  ```
  ~labcc/presubmit/ex3/run <path to ex3.tar>
  ```  

---

By following these instructions and implementing the required functionality, you will create a robust and efficient library for matrix operations in C.

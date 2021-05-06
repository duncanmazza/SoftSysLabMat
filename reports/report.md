# LabMat

Taking inspiration from MATLAB’s admirable qualities and peculiar idiosyncrasies.

## Team Members

Junwon Lee, Duncan Mazza

## Goals

We [Junwon and Duncan] are both well versed with the MATLAB programming language and, between us, have used it in the contexts of digital signal processing, computer vision algorithm prototyping, solving ODEs, robotics, and more.
Through our experiences with MATLAB we have developed an affinity for some aspects of MATLAB, particularly regarding the first-class nature of the matrix data structure and complex numbers, abundance of matrix operations, and excellent documentation. However, when compared to other programming languages such as Python, it deviates from programming language norms and is missing nice-to-have features. For example, MATLAB matrix indexing is 1-indexed, whereas in nearly every other language, array indexing is 0-indexed. Additionally, r-values of matrix-equivalent data structures in Python (e.g., Numpy arrays) support invocation of their associated methods, whereas MATLAB does not. For example:

```python
# This is valid:
mat = np.random.randn(3)
mat.transpose()
```

```matlab
% This is not possible:
mat = randn([3, 1]);
mat.transpose();
```

This combination of characteristics has inspired us to create a new programming language that combines some of the best (in our opinion) features of MATLAB and traditional programming languages. Additionally, between both of us, our first SoftSys projects included a language interpreter and a signal processing library. The combination of both of these projects provides a natural jumping-off point for this project.

Our goal is to create a programming language based on C so that we could define matrices and constants and run operations with these like basic arithmetic. We also wanted to implement at least 1 function from the signal processing library by adapting it to work with matrix data structures.  Our stretch goal was to implement multi-threading for matrix operations and add extra math operations like complex numbers and trig/exponetial functions.

### MVP

Building off of Duncan’s first SoftSys project (Lisp interpreter):
* Define language grammar/syntax
* Implement the language grammar into the mpc abstract syntax tree builder.
* Implement evaluation of expressions from the command line

* Implement the ability to create variables that are matrices.
* Implement basic matrix operations (addition, multiplication). Supported as both dot-operations on matrix variables and as stand-alone functions.
* Be conscious of CPU caching (e.g., being smart about what lines of memory are loaded into the cache).
* Incorporate Junwon’s first SoftSys project: Implement at least 1 function from the signal processing library by adapting it to work with the matrix data structure.

### Stretch Goals
* Implement multi-threading for matrix operations
* Data I/O (reading from CSV files, for example).
* Define complex numbers & math functions (sine, cosine, exp, Pi, etc).
* Implement some matrix generation functions (e.g., matrix generation with values randomly sampled from a standard normal distribution).
* Ensure exactly zero memory leakage with memory profiling tools.

## Learning Goals

### Junwon

I would like to learn how to write custom programming languages. I also want to be more conscious of memory/cache usage when writing code. I hope that by implementing signal processing functions with custom languages I could be introduced to other criteria for writing efficient codes like runtime operation.

### Duncan

Building off of my first project, I am interested in learning more about how interpreted programming languages operate under the hood. I intend to use this project as a vehicle to increase my skills in general software topics, such as multi-threading, computation time optimization, etc. Because I have experience in signal processing applications, I hope for this project to reinforce my understanding of the relevant mathematical theory. If we are able to implement the MVP with time to spare, then implementing complex numbers, for example, will definitely progress me towards this goal.

## Project Outcomes

We have successfully implemented a minimal language interpreter that can assign numbers and matrices to variables and perform basic arithmetics and matrix operations on them. 

### Syntax of LabMat

Our LabMat syntax allows variable definitions like the following:
```
m = 1 + 2;
```
For each variable definition, a height n tree is constructed. The height depends on the number of operations involved in the expression. The parent of the tree will be the operation that needs to happen, and the children of the parent would be the numbers or matrices involved in the operation. For instance, in the sample code, the parent would be the addition operation, and the children would be two integers 1 and 2. The code will do operation on those two values (addition in this case) and substitute the parent with the result.

All lines must end with a semicolon.

#### Strings

Variables can store strings. To define, strings must start and end with double quotation marks (" ").

For instance, this is a valid syntax.
```
m = "Hello World";
```

These are not valid.
```
m = 'Hello World';
m = `hello world`;
```

#### Numbers

Any real numbers can be defined.
```
// all these lines are valid
a = 2;
a = -1;
a = 2.2343;
a = 2/3;
```

#### Matrices

Matrix definition follows similarly to MATLAB's syntax, but not exactly as shown below.

```
// All of these are considered valid.
a = [1, 2;3, 4];
a = [1,2;3,4;];

// This is not valid. 
a = [1,2;3]; // invalid matrix definition. 
// This is not valid (even though this works in MATLAB).
a = [1 2;3 4];
```

There must be commas separating elements in each row. Semicolons separate each row.

#### Arithmetics

Basic arithmetics can be done with matrices and numbers.
* Addition: `+`
* Subtraction: `-`
* Multiplication: `*`
* Division `/` (except between matrices)
* Modulo: `%`
  Note that there are rules that must be followed for matrix operations (ex) restrictions on matrix dimensions, etc.)
  You may write multiple operations in one line as long as they are valid.

```
// Any of these are considered valid.
a = 1 + 2;
b = 2 + [1,1;1,1]; // this will add 2 to all elements.
c = [1,1;1,1] * [1;1]; // Multiplying 2*2 matrix with 2*1 matrix is valid.
d = [1,1;1,1] / 2; // This will divide all elements by 2.
e = 5 - 1 + 2; 

// These are not valid;
a = [1 2;3 4] / [1;1] // This is impossible. You can't divide matrices.
b = 2 / [1,1;1,1]; // This is impossible

```

#### Transposition

In addition, matrices can be transposed.

```
m = transpose[1,2,3;4,5,6];
n = m.transpose();
```

### Syntax and Object Tree Creation and Parsing

When an expression is written for these variables, a height 2 tree is constructed. The parent of the tree would represent the expression in the line, and the children would be either another operation or a number/matrix. 

For instance, in an expression: 
```
m = 1 + 2;
```

The following tree would depict the expression above. 
(insert diagram here)

Another example: 
```
a = 5 * 2 + 1;

```

The following tree would depict the expression above. 
(insert diagram here)

#### Modularity

### Evaluation

To evaluate the result, we first run the operation based on the children. For instance, in the expression: 

```
m = 1 + 2;
```

The children are 1, +, and 2. Therefore, the result of the addition of 1 and 2, which is 3. That 3 will be substituted into  
#### Recursive Implementation

#### Variable Binding

#### Function Binding

### Matrices

For this project, we implemented a 2D matrix data structure that is a first-class citizen - that is, matrix literals (à la MATLAB's matrix literals) are supported along with matrix operations like transposition and multiplication.

#### Matrix Structure

In matrix.c & matrix.h, there are functions that define matrices and perform addition and multiplications on them. When we made these matrices, we were 

```c
// matrix.h
typedef struct matrix {
    int rows;
    int cols;
    float **data;
} matrix;
```

We decided to use a 2D array (`float **data`) to store the matrix; this is as opposed to a 1D array (like what Python's Numpy uses) where two-dimensional coordinates need to be explicitly converted into a single index. Because our implementation is not parallelized, this is to the benefit of performance in functions like `matrix_add` where the second dimension of the array is iterated through by the inner `for` loop (i.e., the inner for loop exhibits spatial locality).  

```c
// matrix.c
matrix *matrix_add(matrix *mat1, matrix *mat2) {
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols) {
        return NULL;
    }
    matrix *total = make_matrix(mat1->rows, mat1->cols);
    for (int x = 0; x < total->rows; x++) {
        for (int y = 0; y < total->cols; y++) {
            total->data[x][y] = mat1->data[x][y] + mat2->data[x][y];
        }
    }
    return total;
}
```

#### Matrix Literals

An important feature of LabMat is support for matrix literals. Matrix literals are converted into `matrix` structures in when parsing the abstract syntax tree. We adopted the same matrix literal syntax used in MATLAB which enables efficient creation of matrices inline. Incorrect matrix dimensions are detected as a static semantic error and reported accordingly. Thanks to the `mpc` library's integration of regex, we implemented the grammar such that white space serves a column delimiter along with a comma - just as in MATLAB.

```
m = [1, 2; 3, 4];        // Valid
m = [1 2; 3       4;];   // Also valid
m = [1, 2, 3; 4];        // Invalid dimensions reported

```

## Reflection

We were able to achieve some of our original learning goals. We are happy that we got to the point where we could perform basic arithmetics on both numbers and matrices. We learned how to define matrices and make syntax design choices for LabMat. We also learned how interpreted languages are operated with tree structures.

However, we didn't get to define signal processing functions with our LabMat. We spent too much time making basic functions for matrices and implementing arithmetic functions in LabMat that we didn't get to create syntax for signal processing functions like convolution and Fourier Transform. We know that if we had more time then we could've defined functions in LabMat that perform signal processing functions.

## Resources

We have read documentations for some functions in MATLAB and Python to compare how they operate differently, along with other resources to create mpc abstract syntax tree builder:

* Numpy documentation
* MATLAB documentation
* Language interpreter resources: https://aosabook.org/en/500L/a-python-interpreter-written-in-python.html \[This and other similar resources on the Python interpreter will be helpful references on interpreter design and implementation\]
* http://www.buildyourownlisp.com/ \[from Duncan’s first SoftSys project\]
https://www.gnu.org/software/octave/index \[Octave is an open-source IDE + programming language that borrows heavily from MATLAB, so it can be used as a reference for how to implement the MATLAB-like features we are desiring\]
* Sestoft, Peter. Programming Language Concepts. Springer London, 2012. EBSCOhost, search.ebscohost.com/login.aspx?direct=true&db=edshlc&AN=edshlc.013282898.7&site=eds-live.
* Lee, Kent D. ..author. Foundations of Programming Languages. 2014. EBSCOhost, search.ebscohost.com/login.aspx?direct=true&db=edshlc&AN=edshlc.014293420.8&site=eds-live.
* Cache/Memory efficiency in matrix operation https://people.eecs.berkeley.edu/~demmel/cs267_Spr99/Lectures/Lect_02_1999b.pdf
* https://cs.brown.edu/courses/cs033/lecture/18cacheX.pdf

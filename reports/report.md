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

We have successfully implemented a minimal language interpreter that can assign numbers and matrices to variables and perform basic arithmetic and matrix operations on them.

### Syntax of LabMat

LabMat is an imperative language with infix-style syntax that resembles a hybrid of Python and MATLAB. Unlike these languages, it is intentionally whitespace-agnostic (like C) and requires semi-colons to separate statements. Variables are dynamically typed and support re-assignment to different types. While operator precedence is not observed, expressions can be arbitrarily nested to enforce the order of operation:

```
>>> m = 4.5 / (2 + 3);
>>> ws

Workspace:
----------
> m (double): 0.840000

```

*A limitation of the syntax as currently implemented is that a leading expression enclosed in parentheses is interpreted as invalid syntax (e.g., `m = (2 + 3) / 4.5`; with more work on constructing the `mpc` parser, this issue could be overcome.*

Supported types include:

- Integers (`long`)
- Floating points (`double`)
- Matrices (`matrix`)
- Strings as string literals

LabMat also supports instance methods for objects. For example, a matrix can be transposed with the following syntax:

```
>>> m = [1, 2];
>>> ws

Workspace:
----------
> m (matrix):
[1 2]

>>> m.transpose();
>>> ws

Workspace:
----------
> m (matrix):
[1
 2]

>>> transpose(m);
>>> ws

Workspace:
----------
> m (matrix):
[1 2]
```

When a function is invoked as a method, the object is inserted as the first argument to the function. Because functions are pass-by-reference, `transpose(m)` is functionally identical to `m.transpose`. As implemented, the transpose function returns a copy of the reference to the original object. This enables the following behavior:

```
>>> m = transpose([1, 2]);
>>> n = m.transpose();
>>> ws

Workspace:
----------
> m (matrix):
[1 2]
> n (matrix):
[1 2]

>>> n.transpose();
>>> ws

Workspace:
----------
> m (matrix):
[1
 2]
> n (matrix):
[1
 2]
```

Currently, there is nothing that distinguishes a "method" from a "function"; i.e., the structures in C do not keep track of what functions are associated with a particular data type. This constitutes a next step for improvement if there is further work done on this project.

For a few more examples illustrating LabMat's syntax:

```
// Any of these are considered valid.
a = 1 + 2;
b = 2 + [1,1;1,1];     // this will add 2 to all elements.
c = [1,1;1,1] * [1;1]; // Multiply 2*2 matrix with 2*1 matrix
d = [1,1;1,1] / a;     // This will divide all elements by 3.
e = 5 - 1 + 2;

// These are not valid;
a = [1 2;3 4] / [1;1]  // This is impossible. You can't divide matrices.
b = 2 / [1,1;1,1];     // This is impossible
```


### Syntax and Object Tree Creation and Parsing

For every input, the `mpc` library creates an abstract syntax tree where each node is labeled according to the parsing rules that are defined in [grammar.c](src/grammar.c) and contains the matching string. The following example shows a visual representation of the abstract syntax tree constructed by the `mpc` library.

```
>>> m = transpose([1, 2]);
>
  regex
  stmt|>
    a_stmt|>
      name|regex:1:1 'm'
      regex:1:2 ' '
      assmt|char:1:3 '='
      regex:1:4 ' '
      expr|anyexpr|fexpr|>
        name|regex:1:5 'transpose'
        char:1:14 '('
        regex
        arglist|anyexpr|smpexpr|>
          mat_lit|>
            char:1:15 '['
            num|int|regex:1:16 '1'
            matcdlm|char:1:17 ','
            regex:1:18 ' '
            num|int|regex:1:19 '2'
            regex
            char:1:20 ']'
          regex
        regex
        char:1:21 ')'
    regex
    char:1:22 ';'
  regex:1:23 '
'
  regex
>>>
```

This abstract syntax tree is then parsed into an object tree:

```
>>> m = transpose([1, 2]);
> LM_LAB_MAT
  > LM_STATEMENT
    > LM_STATEMENT_ASSIGNMENT
      > m
      > =
      > LM_FUNCTION_CALL_EXPRESSION
        > transpose
        > LM_SIMPLE_EXPRESSION
          >
[1 2]
```

The parsing functionality is contained within [otree.c](src/otree.c), where the code carries out two primary responsibilities:

1. Observing the LabMat grammar (i.e., labeling nodes correctly) while condensing the abstract syntax tree to as simple a representation as possible.
2. Converting strings representing data (i.e., numbers, matrix literals, variable names, operators, etc.) into their corresponding values in C.

### Evaluation

Evaluation (see [evaluate.c](src/evaluate.c)) is implemented recursively where base-case inputs is any object tree node with no other children. There exist several logical branches for different types of parent nodes, such as whether a node represents variable assignment or an expression. In the case of expressions and assignment statements, there is only one logical check that differentiates the interpreter's evaluation:

```c
// evaluate.c
if (otree->label != LM_STATEMENT_ASSIGNMENT)
    recurse_ret |= evaluate(otree_left);
```

In the case of assignment, `otree_left` contains the variable name; thus, this check prevents evaluation of a variable that has not yet been set.

One of this project's stretch goals was to eliminate all memory leakage. While we did not achieve this goal, we make a step in the right direction by implementing the following appraoch: whenever an expression or statement is evaluated, the child nodes are deleted, and the parent node is replaced with the result of the evaluation. Not only does this delete-as-you-go approach reduce memory leakage, but the replacement of a parent's node with the result of evaluating its children is integral to the functionality of the language.

#### Variable Binding

To support variable assignment, a hash table was implemented (see [ht.c](ht.c)). When the `ws` command is printed, under the hood, all entries in the `workspace` hash table are retrieved and printed to the command line. The hash table is simple in that it does not support re-sizing and uses a simple division-based hashing algorithm instead of universal hashing, but it appropriately serves our needs. Whenever a variable is not being assigned to, it is evaluated by querying the hash table with the variable name and updating the object's pointers to match what is stored in the hash table.

LabMat does not support scoping even syntactically, so this approach is sufficient. With a more advanced LabMat implementation that supports scopes, function definitions, and more, a single fixed-size hash table and absence of a stack would be inadequate.

#### Operator Evaluation

Operator evaluation in LabMat was built with efficiency in mind. When the abstract syntax tree is parsed, each string containing an operator is classified with an `enum` value. Exploiting the fact that C numbers `enum` values sequentially starting at 0, an array of function pointers (`binop_func_ptrs` in [binop_funcs.c](src/binop_funcs.c)) corresponding to the operator classification `enum` enables O(1) invocation of the correct operator function.

Implementing the type casting for the binary operators proved challenging. Each function includes type checking as type compatibility is not included in the static parsing. The left and right operands are then checked again for their types to enable the correct type casting; the following snippet is an example of such casting from the `binop_arith_sub` (subtraction) function:

```c
// binop_funcs.c
*(double *) ret->val = (!swap ? 1 : -1) * *(double *) new_l_val +
                       (!swap ? -1 : 1) * (new_r_type == OTREE_VAL_LONG
                                           ? ((double) *(long *) new_r_val)
                                           : (*(double *) new_r_val));
```

##### Supported operators

In addition to the assignment operator `=`, the following operators are supported:

**Arithmetic operators** (between matrices and/or numbers unless otherwise specified):

* Addition: `+`
* Subtraction: `-`
* Multiplication: `*` *(matrix multiplication dimension constraints apply)
  You may write multiple operations in one line as long as they are valid)*
* Division `/` (except between matrices)
* Modulo: `%` (only between integers)

**Logical and bit operators** (only between integers):

* Bitwise AND: `&`
* Bitwise XOR: `^`
* Bitwise OR: `|`
* Logical AND: `&&`
* Logical OR: `||`

#### Function Binding

Only one function - `transpose` - is implemented as a built-in function. Function binding happens at runtime when LabMat is launched: a hash table called `builtins` (see [builtins.c](builtins.c)) is populated such that it maps the function names to the correct function pointers, enabling O(1) invocation. Though `transpose` requires a single argument, the function binding interface was designed to provide what is essentially a variadic wrapper to any external function. As with the operators, an array of function pointers maps function names to their pointers:

```c
// builtins.c
void *(*builtins_func_ptrs[])(size_t, OTree *[]) = {
        builtin_transpose,
};

void *builtin_transpose(size_t nargs, OTree **args) {
  if (nargs != 1) {
    fprintf(stderr,
        "builtin_transpose provided with more than one argument");
    exit(-1);
  }
  OTree *mat_otree = (OTree *) args[0];
  *(matrix *) mat_otree->val = *matrix_transpose((matrix *) mat_otree->val);
  return mat_otree;
}
```

By accepting an array of `OTree` (object tree) pointers, any built-in function wrapper can support an arbitrary number of arguments.

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

An important feature of LabMat is support for matrix literals. Matrix literals are converted into `matrix` structures in when parsing the abstract syntax tree. We adopted the same matrix literal syntax used in MATLAB which enables efficient creation of matrices inline. Incorrect matrix dimensions are detected as a static semantic error and reported accordingly. Thanks to the `mpc` library's integration of regex, we implemented the grammar such that white space simultaneously serves a column delimiter along with a comma - just as in MATLAB - and can be treated as extraneous when appropriate. For example:

```
m = [1,2;3,4];           // Valid
m = [1 2; 3       4;];   // Also valid
m = [1, 2, 3; 4];        // Invalid dimensions reported
```

## Reflection

We were able to achieve many of our our learning goals and all of the originally-defined MVP with the exception of signal processing function integration. Though we didn't have the bandwidth to explore some of the stretch goals outlined, achieving the MVP was plenty challenging with implementation of basic arithmetic operations on both numbers *and* matrices as well as assigning and making use of variables. Given the infrastructure we built to support the transposition function, we see integration of signal processing functions like convolution and the fast Fourier Transform as a clear next step. We learned how to define matrices and make syntax design choices for LabMat.

### Duncan Learning Goals Reflection

I was able to achieve some of my learning goals through this project. Namely, my understanding of language interpreters grew substantially, due to both realizing the merits of LabMat's implementation and becoming aware of its downfalls relative to other language interpreters. I also grew my confidence in writing C code, especially through this project's abundant use of pointers to heap-allocated data, `enum`s, and function pointers.

This project, however, made no use of any synchronization, so I did not achieve my learning goal of learning more about threading. I had also hoped that this project would improve my knowledge of mathematical theory relevant to signal processing, but that was not achieved within the bounds of the MVP. Having seen a peer in a different class dive into the implementation of the cross-correlation function to find that, under the hood, it can be implemented in better-than-quadratic time (as would be achieved with a naive implementation) using a theorem invoking the Fourier Transform, I realized this was the kind of learning I was hoping this project would provide.

Though not all of my learning goals were achieved, I sufficiently challenged myself in this project and saw growth in SoftSys-relevant skills.

### Junwon Learning Goals Reflection

I am happy that we got to the point where we could perform basic arithmetics on both numbers and matrices. I learned how to define matrices and make syntax design choices for LabMat. I also learned how interpreted languages are operated with tree structures thanks to Duncan. One personal realization I had was that learning the concept behind interpreted languages in depth is just as important as writing C code. I thought I wasn't "learning" anything because I wasn't writing any extensive code, but I realize how much I learned about operation of language interpreters just from reading documents and code. I did not get to implement my signal processing functions in LabMat due to the lack of time, but I am personally happy with progress Duncan and I made so far in this project.  

## Resources

Following is the initial list of resources we outlined, with the bolded items having proved the most useful:

* Numpy documentation
* MATLAB documentation
* Language interpreter resources: https://aosabook.org/en/500L/a-python-interpreter-written-in-python.html \[This and other similar resources on the Python interpreter will be helpful references on interpreter design and implementation\]
* **http://www.buildyourownlisp.com/ \[from Duncan’s first SoftSys project\]**
https://www.gnu.org/software/octave/index \[Octave is an open-source IDE + programming language that borrows heavily from MATLAB, so it can be used as a reference for how to implement the MATLAB-like features we are desiring\]
* **Sestoft, Peter. Programming Language Concepts. Springer London, 2012. EBSCOhost, search.ebscohost.com/login.aspx?direct=true&db=edshlc&AN=edshlc.013282898.7&site=eds-live.**
* **Lee, Kent D. ..author. Foundations of Programming Languages. 2014. EBSCOhost, search.ebscohost.com/login.aspx?direct=true&db=edshlc&AN=edshlc.014293420.8&site=eds-live.**
* Cache/Memory efficiency in matrix operation https://people.eecs.berkeley.edu/~demmel/cs267_Spr99/Lectures/Lect_02_1999b.pdf
* https://cs.brown.edu/courses/cs033/lecture/18cacheX.pdf

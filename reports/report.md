# LabMat

Taking inspiration from MATLAB’s admirable qualities and peculiar idiosyncrasies.

## Team Members

Junwon Lee, Duncan Mazza

## Goals

We [Junwon and Duncan] are both well versed with the MATLAB programming language and, between us, have used it in the contexts of digital signal processing, computer vision algorithm prototyping, solving ODEs, robotics, and more.
Through our experiences with MATLAB we have developed an affinity for some aspects of MATLAB, particularly regarding the first-class nature of the matrix data structure and complex numbers, abundance of matrix operations, and excellent documentation. However, when compared to other programming languages such as Python, it deviates from programming language norms and is missing nice-to-have features. For example, MATLAB matrix indexing is 1-indexed, whereas in nearly every other language, array indexing is 0-indexed. Additionally, r-values of matrix-equivalent data structures in Python (e.g., Numpy arrays) support invocation of their associated methods, whereas MATLAB does not. For example:
```python
# This is valid:
mat = np.random.randn(3).transpose()
```
```matlab
% This is not possible:
mat = randn([3, 1]).transpose()
```
This combination of characteristics has inspired us to create a new programming language that combines some of the best (in our opinion) features of MATLAB and traditional programming languages. Additionally, between both of us, our first SoftSys projects included a language interpreter and a signal processing library. The combination of both of these projects provides a natural jumping-off point for this project.

Our goal is to create a programming language based on C so that we could define matrices and constants and run operations with these like basic arithmetic. We also wanted to implement at least 1 function from the signal processing library by adapting it to work with matrix data structures.  Our stretch goal was to implement multi-threading for matrix operations and add extra math operations like complex numbers and trig/exponetial functions.

## Learning Goals

### Junwon
I would like to learn how to write custom programming languages. I also want to be more conscious of memory/cache usage when writing code. I hope that by implementing signal processing functions with custom languages I could be introduced to other criteria for writing efficient codes like runtime operation.

### Duncan
Building off of my first project, I am interested in learning more about how interpreted programming languages operate under the hood. I intend to use this project as a vehicle to increase my skills in general software topics, such as multi-threading, computation time optimization, etc. Because I have experience in signal processing applications, I hope for this project to reinforce my understanding of the relevant mathematical theory. If we are able to implement the MVP with time to spare, then implementing complex numbers, for example, will definitely progress me towards this goal.

## What we have accomplished

### Matrix Definition

In Duncan's first project, variables could be defined with numerical values like float & constants. However, we wanted to implement 2D matrices in this language. Therefore, we had to create separate functions for defining matrices. In matrix.c & matrix.h, there are functions that define matrices and perform addition and multiplications on them.

### Syntax of LabMat

Our LabMat syntax allows the variable definition like the following:
```
m = 1 + 2;
```
For each variable definition, a height 2 tree is constructed. The parent of the tree will be the operation that needs to happen, and the children of the parent would be the numbers or matrices involved in the operation. For instance, in the sample code, the parent would be the addition operation, and the children would be two integers 1 and 2. The code will do operation on those two values (addition in this case) and substitute the parent with the result.

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

Any numbers can be parsed, bot positive and negative.
```
// all these lines are valid
a = 2;
a = -1;
a = 2.2343;

```

#### Matrices

Matrix definition follows similarly to MATLAB's syntax, but not exactly as shown below.
```
// Any of these are considered valid.
a = [1, 2;3, 4];
a = [1,2;3,4;];

// This is not valid (even though this works in MATLAB).
a = [1 2;3 4]

```
There must be comments separating each element in each row. When the matrix.  

#### Operations

Basic arithmetics can be done with matrices and numbers.
* Addition: +
* Subtraction: -
* Multiplication: *
* Division: /
* Modulo: %
Note that there are rules that must be followed for matrix operations (ex) restrictions on matrix dimensions, etc.)
You may write multiple operations in one line as long as they are valid.

```
// Any of these are considered valid.
a = 1 + 2;
b = 2 + [1,1;1,1]; // this will add 2 to all elements.
c = [1,1;1,1] * [1;1]; // Multiplying 2*2 matrix with 2*1 matrix is valid.
d = [1,1;1,1] / 2; // This will divide all elements by 2.

// These are not valid;
a = [1 2;3 4] / [1;1] // This is impossible. You can't divide matrices.
b = 2 / [1,1;1,1]; // This is impossible

```
## Reflection

We were able to achieve some of our original learning goals. We are happy that we got to the point where we could perform basic arithmetics on both numbers and matrices. We learned how to define matrices and make syntax design choices for LabMat. We also learned how interpreted languages are operated with tree structures.

However, we didn't get to define signal processing functions with our LabMat. We spent too much time making basic functions for matrices and implementing arithmetic functions in LabMat that we didn't get to create syntax for signal processing functions like convolution and Fourier Transform. We know that if we had more time then we could've defined functions in LabMat that perform signal processing functions.  

## Resources

Resources
We will need to read documentations for some of the functions in MATLAB and Python to compare how they operate differently:
* Numpy documentation
* MATLAB documentation
* Language interpreter resources: https://aosabook.org/en/500L/a-python-interpreter-written-in-python.html [This and other similar resources on the Python interpreter will be helpful references on interpreter design and implementation]
* http://www.buildyourownlisp.com/ [from Duncan’s first SoftSys project]
https://www.gnu.org/software/octave/index [Octave is an open-source IDE + programming language that borrows heavily from MATLAB, so it can be used as a reference for how to implement the MATLAB-like features we are desiring]
* Sestoft, Peter. Programming Language Concepts. Springer London, 2012. EBSCOhost, search.ebscohost.com/login.aspx?direct=true&db=edshlc&AN=edshlc.013282898.7&site=eds-live.
* Lee, Kent D. ..author. Foundations of Programming Languages. 2014. EBSCOhost, search.ebscohost.com/login.aspx?direct=true&db=edshlc&AN=edshlc.014293420.8&site=eds-live.
* Cache/Memory efficiency in matrix operation https://people.eecs.berkeley.edu/~demmel/cs267_Spr99/Lectures/Lect_02_1999b.pdf
* https://cs.brown.edu/courses/cs033/lecture/18cacheX.pdf

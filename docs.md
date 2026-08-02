# Source code documentation PROJECT NAME TBA

# Types

## Vector Types
### Vec3
Vec3 represents a vector with 3 components indexed 0 through 2.    

#### Constructors
Vec3() initializes the Vec3 object with 0 at all components.  
Vec3(const GLfloat, const GLfloat, const GLfloat) initializes the vector with the provided values.
Vec3(const Vec3&) initialized the vector with a deep copy of the provided Vec3&.

#### Operators
() provides array-like component access. Parantheses are used over brackets for congruency with matrix component access operator.  
\* provides component wise multiplication with a scalar if GLfloat is on lhs or rhs of the operator.  
\* provides cross dot/inner/scalar product if lhs and rhs are both of type Vec3.  
\+ provides component wise addition of 2 Vec3 objects.  
\- provides component wise subtraction of 2 Vec3 objects.  
\- (unary) returns a negated copy of the vector by component wise negation.  
\= assigns a deep copy of the rhs Vec3 object to the lhs Vec3 object.  
\== compares the lhs Vec3 to the rhs Vec3 checking for component wise equality (true if lhs(i)==rhs(i) for i={0,1,2}).  
\=! compares the lhs Vec3 to the rhs Vec3 checking for component wise inequality (true if lhs(i)!=rhs(i) for any of i={0,1,2}). 

#### Methods
GLfloat getLength() returns the length of the vector.  
Vec3 vectorProduct(const Vec3&) returns the vector/outer product of this and the provided Vec3&.  
void normalize() normalizes the Vec3 it is called on, dividing each component by the vector's length.  

## Vec4
Vec4 represents a vector with 4 components indexes 0 through 3.

#### Constructors
Vec4() initializes the Vec3 object with 0 at all components.  
Vec4(const GLfloat, const GLfloat, const GLfloat) initializes the vector with the provided values.
Vec4(const Vec4&) initialized the vector with a deep copy of the provided Vec3&.

#### Operator  
() provides array-like component access. Parantheses are used over brackets for congruency with matrix component access operator.  
\* provides component wise multiplication with a scalar if GLfloat is on lhs or rhs of the operator.  
\* provides dot/inner/scalar product if lhs and rhs are both of type Vec4.  
\+ provides component wise addition of 2 Vec4 objects.  
\- provides component wise subtraction of 2 Vec4 objects.  
\- (unary) returns a negated copy of the vector by component wise negation.  
\= assigns a deep copy of the rhs Vec4 object to the lhs Vec4 object.  
\== compares the lhs Vec4 to the rhs Vec4 checking for component wise equality (true if lhs(i)==rhs(i) for all i={0,1,2,3}).  
\=! compares the lhs Vec4 to the rhs Vec4 checking for component wise inequality (true if lhs(i)!=rhs(i) for any i={0,1,2,3}).

#### Methods
GLfloat getLength() returns the length of the vector.  
void normalize() normalizes the Vec4 it is called on, dividing each component by the vector's length.

## Matrix types

### Mat3
Mat4 represents a 3x3 matrix by storing the components in a 1-dimensional array and indexing in column major order by 
provided access operators and indexing methods.

#### Constructors
Mat3() initializes the matrix to a unity matrix.  
Mat3(const Mat3&) initializes the matrix to a deep copy of the provided Mat4&.
~Mat3() *does not* call delete[] on the arrays memory, as it is not heap-allocated

#### Operator
() provides component access with 2 size_t parameters corresponding to column, row (access in column major order).  
\* provides the matrix product of lhs and rhs.
\* provides component wise multiplication with a scalar if rhs or lhs are of type GLfloat.  
\= assigns a deep copy of the rhs Mat4 to the lhs Mat4.  
== compares the lhs Mat4 to the rhs Mat4 checking for component wise equality (true if lhs(i)==rhs(i) for all (0 <= i < 16).  
!= compares the lhs Mat4 to the rhs Mat4 checking for component wise inequality (true if lhs(i)==rhs(i) for any (0 <= i < 16). 

#### Methods
determinant() calculates the determinant of the matrix.
isInvertible() checks if the matrix is invertible (determinant != 0) and returns true if it is, false if it isnt.
invert() calculates the inverse of the matrix it is called on and sets it to the result.
invertCopy() calculates the inverse of a copy of the matrix it is called on and returns the inverted copy.
transpose() sets the matrix it is called up to its transposed form.
transposeCopy() copies and transposes the matrix it is called on, returning the transposed copy.
directPrint() prints the matrix it is called on to cout.
mIndex(col, row) can be used to translate a column major 2-value index to the 1-dimensional linear array index used internally.  

### Mat4
Mat4 represents a 4x4 matrix by storing the components in a 1-dimensional array and indexing in column major order by 
provided access operators and indexing methods.

#### Constructors
Mat4() initializes the matrix to a unity matrix.  
Mat4(const Mat4&) initializes the matrix to a deep copy of the provided Mat4&.
~Mat4() *does not* call delete[] on the arrays memory, as it is not heap-allocated

#### Operator
() provides component access with 2 size_t parameters corresponding to column, row (access in column major order).  
\* provides the matrix product of lhs and rhs.  
\* provides component wise multiplication with a scalar if rhs or lhs are of type GLfloat.  
\= assigns a deep copy of the rhs Mat4 to the lhs Mat4.  
== compares the lhs Mat4 to the rhs Mat4 checking for component wise equality (true if lhs(i)==rhs(i) for all (0 <= i < 16).  
!= compares the lhs Mat4 to the rhs Mat4 checking for component wise inequality (true if lhs(i)==rhs(i) for any (0 <= i < 16).  
\<< provides printing of the rhs matrix to an ostream on the lhs of the operator.

#### Methods
translate(Vec3&) multiplies the matrix it is called, from the rhs, with a translation matrix made from the provided Vec3 on the lhs.  
translateCopy(Vec3&) returns a copy of the matrix it is called on, that has been translated with translate(Vec3&).   

scale(Vec3&) multiplies the matrix it is called on, from the rhs, with a scaling matrix made from the provided Vec3 on the lhs.  
scaleCopy(Vec3&) returns a copy of the matrix it is called on, that has been scaled with scale(Vec3&).  

rotateX(const GLfloat&) multiplies the matrix it is called on, from the rhs with a rotation matrix that rotates around the x-axis by provided number of radians on the lhs.  
rotateY(const GLfloat&) multiplies the matrix it is called on, from the rhs with a rotation matrix that rotates around the y-axis by provided number of radians on the lhs.
rotateZ(const GLfloat&) multiplies the matrix it is called on, from the rhs with a rotation matrix that rotates around the z-axis by provided number of radians on the lhs. 

rotateCopyX(const GLfloat&) returns a copy of the matrix it is called on, that has been rotated with rotateX.  
rotateCopyY(const GLfloat&) returns a copy of the matrix it is called on, that has been rotated with rotateY.  
rotateCopyZ(const GLfloat&) returns a copy of the matrix it is called on, that has been rotated with rotateZ.

lookAt() creates a view matrix from provided parameters and multiplies this with it from the rhs (viewmatrix is lhs).
lookAtCopy() returns a copy of this that was multiplied with a viewMatrix created from the parameters.

perspective() creates a projection matrix with the provided parameters and multiplies this with it from the rhs (projection matrix is lhs).

getNormalMatrix() extracts the top left 3x3 matrix from the matrix it is called on, and computes its inverse transpose to get a normal matrix corresponding to a modelview matrix which is returned by the method

directPrint() prints the matrix it is called on to cout.
mIndex(col, row) can be used to translate a column major 2-value index to the 1-dimensional linear array index used internally.  

# Utilities

## ShaderSource
ShaderSource abstracts loading and storing the source code for shaders in an object of type Shadersource.

### Constructors
- ShaderSource() constructs an empty ShaderSource object
- ShaderSource(const string& path) constructs a ShaderSource object and loads the source code located at provided file  
path into the object
- ShaderSource(const ShaderSource& other) constructs a deep copy of other
- ~ShaderSource() does NOT call delete[] on the memory allocated for storage of the shader source code.  
Client is responsible for freeing of the memory!

### Methods
- loadSourceFile() loads a shader source code file and sets its path. Old data will be overwritten!
- readSourceFile() reads the content of a file into a newly allocated buffer pointed to in the object
- getSourceString() returns a pointer to the heap memory in which the shader source code is stored

# Tests

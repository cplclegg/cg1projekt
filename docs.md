# Source code documentation PROJECT NAME TBA

# Utilities

## ShaderSource
``ShaderSource`` abstracts loading and storing the source code for shaders in an object of type Shadersource.

### Constructors
- ``ShaderSource()`` constructs an empty ShaderSource object
- ``ShaderSource(const string& path)`` constructs a ShaderSource object and loads the source code located at provided file  
path into the object
- ``ShaderSource(const ShaderSource& other)`` constructs a deep copy of other
- ``~ShaderSource()`` does NOT call delete[] on the memory allocated for storage of the shader source code.  
Client is responsible for freeing of the memory!

### Methods
- ``loadSourceFile()`` loads a shader source code file and sets its path. Old data will be overwritten!
- ``readSourceFile()`` reads the content of a file into a newly allocated buffer pointed to in the object
- ``getSourceString()`` returns a pointer to the heap memory in which the shader source code is stored

## ShaderProgram

ShaderProgram abstracts creation, compilation, and error handling of an OpenGL program. It is meant to be constructed from two shader locations, the first for the vertex shader source,  
the second for the fragment shader source.

### Constructors

- ``ShaderProgram(const std::string& vertexLocation, const std::string& fragmentLocation)`` constructs a ShaderProgram, in the process constructing a ShaderSource for each shader, and immediately after member initialization creates a shader program with the steps shader compilation -> linking -> validation. The identifier GLuint of the created shader program is stored as a data member
- ``ShaderProgram()`` constructs an empty object
- ``ShaderProgram(const ShaderProgram& other)`` constructs a copy with deep copied ShaderSources, and copies the state (status codes and messages, program ID, exists-flag)

### Member functions

- ``void ShaderProgram::addVertexShaderSource(const std::string& path)`` adds a vertex shader source overwriting the old one, if one was already stored
- ``void ShaderProgram::addFragmetShaderSource(const std::string& path)`` adds a fragment shader source overwriting the old one, if one was already stored
- ``bool ShaderProgram::checkSuccessfulCreation() const`` returns true if all error checking flags signal positive outcome, prints limited debugging info and returns false otherwise
- ``void ShaderProgram::createProgram()`` abstracts opengl code for shader creation, compilation, linking, and validation
- ``GLuint ShaderProgram::getID() const`` returns the ID of the shaderprogram. Will return 0 is no shader proram was created.

## ObjectData
``ObjectData`` abstracts loading limited data from a .obj file. Full Wavefront .obj is not supported, only triangulated meshes may be used with this class.

### Constructors
- ``ObjectData()`` constructs an empty object
- ``ObjectData(string& path)`` constructs an ObjectData object with the data from the .obj file at path
- ``ObjectData(ObjectData& other)`` constructs a shallow copy of other
- ``~ObjectData()`` does not free any memory in case shallow copies exist

### Methods
- ``private GLfloat* ObjectData::loadObj(const char* location)`` loads the data of the .obj file at ``location``
- ``void ObjectData::importObjectData(const std::string& path)`` provides a public wrapper for ``loadObj``, allowing loading of an .obj file into an existing (empty or non-empty) ObjectData
- ``GLfloat* ObjectData::getBuffer() const`` returns a pointer to the data buffer of the object
- ``GLuint ObjectData::makeVBO() const`` abstracts creation of a VBO and data transfer to the VBO. The identifier of the VBO is returned from the function.

## TextureData

TextureData abstracts loading of image data and creation of an opengl texture object from that texture data.

### Constructors
- tba

### Member functions
- tba

## Material

Material combines a shader program, and up to four TextureData (diffuse, normal, specular, emissive) into a Material.

## Constructors
- tba

### Member functions
- tba

## Renderable

Renderable combine all the data needed for a draw call (except any planned interactions like setting of uniforms) into a single object. This includes vbo, vao, Material, and vertex count.

### Constructors
- tba

### Member functions
- tba

## SceneNode

A scene node is a composite implementation of a scenegraph. It stores a Renderable, its corresponding local transform matrix, and a ``std::vector`` of ``SceneNode`` children. It also provides a member function ``draw()``, which takes parent world transform matrix and a camera transform matrix, and combines them with the localtransform to get the final transform which is to be sent to the shaders corresponding uniform. A call of ``draw()`` is first forwarded to all children (handing through the world transform matrix *calculated from the parent world transform and the local transform* - the root SceneNode object must be given a unity matrix as parent world transform for the draw call - and the camera matrix) and then executed on the SceneNode itself. As a result, a call of ``draw()`` on the root of a scene should draw the whole scene.

### Constructors
- tba

### Member functions
- tba

## ResourceLocator

ResourseLocator provides a single static function that takes a ``std::filesystem::path`` representing a relative path to a resource (e.g. shader source file, .obj file, etc.) originating from the project root and uses a constant set by meson on building the project, which represents the absolute path to the content root on the system where meson built the project, to construct the absolute path to the resource and return it as ``std::filesystem::path``

### Member functions
- ``std::filesystem::path ResourceLocator::getResourcePath(const std::filesystem::path& relativePath)`` implements completion of relative path to user-system specific absolute path

# Types

## Vector Types
### Vec3
Vec3 represents a vector with 3 components indexed 0 through 2.    

#### Constructors
- ``Vec3()`` initializes the Vec3 object with 0 at all components.  
- ``Vec3(const GLfloat, const GLfloat, const GLfloat)`` initializes the vector with the provided values.
- ``Vec3(const Vec3&)`` initialized the vector with a deep copy of the provided Vec3&.

#### Operators
- ``()`` provides array-like component access. Parantheses are used over brackets for congruency with matrix component access operator.  
- ``*`` provides component wise multiplication with a scalar if GLfloat is on lhs or rhs of the operator.  
- ``*`` provides cross dot/inner/scalar product if lhs and rhs are both of type Vec3.  
- ``+`` provides component wise addition of 2 Vec3 objects.  
- ``-`` provides component wise subtraction of 2 Vec3 objects.  
- ``-`` (unary) returns a negated copy of the vector by component wise negation.  
- ``=`` assigns a deep copy of the rhs Vec3 object to the lhs Vec3 object.  
- ``==`` compares the lhs Vec3 to the rhs Vec3 checking for component wise equality (true if lhs(i)==rhs(i) for i={0,1,2}).  
- ``=!`` compares the lhs Vec3 to the rhs Vec3 checking for component wise inequality (true if lhs(i)!=rhs(i) for any of i={0,1,2}). 

#### Methods
- ``GLfloat getLength()`` returns the length of the vector.  
- ``Vec3 vectorProduct(const Vec3&)`` returns the vector/outer product of this and the provided Vec3&.  
- ``void normalize()`` normalizes the Vec3 it is called on, dividing each component by the vector's length.  

## Vec4
Vec4 represents a vector with 4 components indexes 0 through 3.

#### Constructors
- ``Vec4()`` initializes the Vec3 object with 0 at all components.  
- ``Vec4(const GLfloat, const GLfloat, const GLfloat)`` initializes the vector with the provided values.
- ``Vec4(const Vec4&)`` initialized the vector with a deep copy of the provided Vec3&.

#### Operator  
- ``()`` provides array-like component access. Parantheses are used over brackets for congruency with matrix component access operator.  
- ``*`` provides component wise multiplication with a scalar if GLfloat is on lhs or rhs of the operator.  
- ``*`` provides dot/inner/scalar product if lhs and rhs are both of type Vec4.  
- ``+`` provides component wise addition of 2 Vec4 objects.  
- ``-`` provides component wise subtraction of 2 Vec4 objects.  
- ``-`` (unary) returns a negated copy of the vector by component wise negation.  
- ``=`` assigns a deep copy of the rhs Vec4 object to the lhs Vec4 object.  
- ``==`` compares the lhs Vec4 to the rhs Vec4 checking for component wise equality (true if lhs(i)==rhs(i) for all i={0,1,2,3}).  
- ``=!`` compares the lhs Vec4 to the rhs Vec4 checking for component wise inequality (true if lhs(i)!=rhs(i) for any i={0,1,2,3}).

#### Methods
- ``GLfloat getLength()`` returns the length of the vector.  
- ``void normalize()`` normalizes the Vec4 it is called on, dividing each component by the vector's length.

## Matrix types

### Mat3
Mat3 represents a 3x3 matrix by storing the components in a 1-dimensional array and indexing in column major order by 
provided access operators and indexing methods.

#### Constructors
- ``Mat3()`` initializes the matrix to a unity matrix.  
- ``Mat3(const Mat3&)`` initializes the matrix to a deep copy of the provided Mat4&.
- ``~Mat3()`` *does not* call delete[] on the arrays memory, as it is not heap-allocated

#### Operator
- ``()`` provides component access with 2 size_t parameters corresponding to column, row (access in column major order).  
- ``*`` provides the matrix product of lhs and rhs.
- ``*`` provides component wise multiplication with a scalar if rhs or lhs are of type GLfloat.  
- ``=`` assigns a deep copy of the rhs Mat4 to the lhs Mat4.  
- ``==`` compares the lhs Mat4 to the rhs Mat4 checking for component wise equality (true if lhs(i)==rhs(i) for all (0 <= i < 16).  
- ``!=`` compares the lhs Mat4 to the rhs Mat4 checking for component wise inequality (true if lhs(i)==rhs(i) for any (0 <= i < 16). 

#### Methods
- ``determinant()`` calculates the determinant of the matrix.
- ``isInvertible()`` checks if the matrix is invertible (determinant != 0) and returns true if it is, false if it isnt.
- ``invert()`` calculates the inverse of the matrix it is called on and sets it to the result.
- ``invertCopy()`` calculates the inverse of a copy of the matrix it is called on and returns the inverted copy.
- ``transpose()`` sets the matrix it is called up to its transposed form.
- ``transposeCopy()`` copies and transposes the matrix it is called on, returning the transposed copy.
- ``directPrint()`` prints the matrix it is called on to cout.
- ``mIndex(col, row)`` can be used to translate a column major 2-value index to the 1-dimensional linear array index used internally.  

### Mat4
Mat4 represents a 4x4 matrix by storing the components in a 1-dimensional array and indexing in column major order by 
provided access operators and indexing methods.

#### Constructors
- ``Mat4()`` initializes the matrix to a unity matrix.  
- ``Mat4(const Mat4&)`` initializes the matrix to a deep copy of the provided Mat4&.
- ``~Mat4()`` *does not* call delete[] on the arrays memory, as it is not heap-allocated

#### Operator
- ``()`` provides component access with 2 size_t parameters corresponding to column, row (access in column major order).  
- ``*`` provides the matrix product of lhs and rhs.  
- ``*`` provides component wise multiplication with a scalar if rhs or lhs are of type GLfloat.  
- ``=`` assigns a deep copy of the rhs Mat4 to the lhs Mat4.  
- ``==`` compares the lhs Mat4 to the rhs Mat4 checking for component wise equality (true if lhs(i)==rhs(i) for all (0 <= i < 16).  
- ``!=`` compares the lhs Mat4 to the rhs Mat4 checking for component wise inequality (true if lhs(i)==rhs(i) for any (0 <= i < 16).  
- ``<<`` provides printing of the rhs matrix to an ostream on the lhs of the operator.

#### Methods
- ``translate(Vec3&)`` multiplies the matrix it is called, from the rhs, with a translation matrix made from the provided Vec3 on the lhs.  
- ``translateCopy(Vec3&)`` returns a copy of the matrix it is called on, that has been translated with translate(Vec3&).   

- ``scale(Vec3&)`` multiplies the matrix it is called on, from the rhs, with a scaling matrix made from the provided Vec3 on the lhs.  
- ``scaleCopy(Vec3&)`` returns a copy of the matrix it is called on, that has been scaled with scale(Vec3&).  

- ``rotateX(const GLfloat&)`` multiplies the matrix it is called on, from the rhs with a rotation matrix that rotates around the x-axis by provided number of radians on the lhs.  
- ``rotateY(const GLfloat&)`` multiplies the matrix it is called on, from the rhs with a rotation matrix that rotates around the y-axis by provided number of radians on the lhs.
- ``rotateZ(const GLfloat&)`` multiplies the matrix it is called on, from the rhs with a rotation matrix that rotates around the z-axis by provided number of radians on the lhs. 

- ``rotateCopyX(const GLfloat&)`` returns a copy of the matrix it is called on, that has been rotated with rotateX.  
- ``rotateCopyY(const GLfloat&)`` returns a copy of the matrix it is called on, that has been rotated with rotateY.  
- ``rotateCopyZ(const GLfloat&)`` returns a copy of the matrix it is called on, that has been rotated with rotateZ.

- ``lookAt()`` creates a view matrix from provided parameters and multiplies this with it from the rhs (viewmatrix is lhs).
- ``lookAtCopy()`` returns a copy of this that was multiplied with a viewMatrix created from the parameters.

- ``perspective()`` creates a projection matrix with the provided parameters and multiplies this with it from the rhs (projection matrix is lhs).

- ``getNormalMatrix()`` extracts the top left 3x3 matrix from the matrix it is called on, and computes its inverse transpose to get a normal matrix corresponding to a modelview matrix which is returned by the method

- ``directPrint()`` prints the matrix it is called on to cout.
- ``mIndex(col, row)`` can be used to translate a column major 2-value index to the 1-dimensional linear array index used internally.


# Tests

Functional methods of each class are tested with equivalence class tests. Each class has a main testing function that calls the method testing functions. Test source files must be added to ``test_sources`` in the ``meson.build`` file. The main testing function of a class must be called from the main function in ``/tests/unit_tests.cpp``. The signature of the main testing function of a class must be added to ``/include/tests.h``. 

## Signature for main testing function

The main testing function of a class must ``return 0`` if all the tests called from it have passed, and a non-zero integer if any of the tests have failed. To achieve this, it is recommended to have each unit test ``return 0`` on pass and ``return 1`` on fail. The main testing function can then add up all the return values and return the sum as is. If all tests have passed, the main testing function will ``return 0``, otherwise it will return an integer corresponding to the number of failed tests. 

The same strategy is used in the the main function of ``/tests/unit_tests.cpp``. The exit code returned from this main function is thus the number of total failed tests.


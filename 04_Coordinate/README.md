# Coordinate Systems
* Five coordinate systems:
	* Local space (or Object space)
	* World space
	* View space (or Eye space)
	* Clip space
	* Screen space
* Relation:
	![coordinate system](http://www.learnopengl.com/img/getting-started/coordinate_systems.png)

## Local space
* Coordinate space that is local to the object, usually start at `(0,0,0)`
* The vertices of the container we’ve been using were specified as coordinates between `-0.5` and `0.5` with `0.0` as its origin. These are local coordinates.

## World space
* Coordinates of all your vertices relative to a (game) world.
* Transformed by the **model** matrix.
* The model matrix is a transformation matrix that translates, scales and/or rotates your object to place it in the world at a location/orientation they belong to.

## View space
* Camera of OpenGL (also known as the *camera space* or *eye space*)
* Transformed by the **view** matrix

## Clip space
* Convert vertex coordinates to the range of `-1.0`, `1.0` to be visible, and do orthographic or perspective projection.
* Achieved by **projection** matrix
* Orthographic projection
* Perspective projection
	![equation](http://latex.codecogs.com/svg.latex?out%20%3D%20%5Cbegin%7Bpmatrix%7D%20x%20%2Fw%20%5C%5C%20y%20%2F%20w%20%5C%5C%20z%20%2F%20w%20%5Cend%7Bpmatrix%7D)
* [Reference](http://www.songho.ca/opengl/gl_projectionmatrix.html)
----------------------
V3D - Library. Documentation.
======================
----------------------
General consideration.
-
    1.- Typedef t_v3d, provides a struct to work with 3D vectors, defined
        by coordinates x, y and z. Coordinates defined as doubles.
    2.- enum e_coor, provides a easier way to access to axis variables
        when will be needed. X_C = 0, Y_C = 1, Z_C = 2.
    3.- Some operations and definitios can be used also with static points,
        to do so a Typedef t_point is defined over t_v3d struct.
    4.- V3D_COOR(0) and V3D_NORM(1) is also defined, especially for debug
        porpouses.
----------------------
CONCEPTS
----------------------
    v3d_algebra.c : Functions to get properties of a given set of vectors,
                    such as lenght, magnitude, sin, cos and cross product.
    v3d_arithmetics.c : Functions of basic math operations with vectors,
                    such as addition, dot, etc.
    v3d_geometry.c: Functions to operate over geometric properties of a
                    vector, such as rotation and distance between two
                    points or vectors.
    v3d_utils.c:    A set of useful functions, such as copy, normalize,
                    get a new vector, etc.

    To further information about vectors definitions and operations:
        -> https://people.math.harvard.edu/~jjchen/math21a/handouts/vector-ops.html
        -> https://www.geeksforgeeks.org/vector-operations/
        -> https://en.wikipedia.org/wiki/Vector_space
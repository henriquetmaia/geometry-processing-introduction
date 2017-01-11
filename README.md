# 00-Introduction

To get started:

```bash
git clone --recursive https://github.com/alecjacobson/geometry-processing-assignment-00
```

Welcome to Geometry Processing! The purpose of this assignment will be to get
you up and running with the two C++ libraries we will be using:
[Eigen](http://eigen.tuxfamily.org) for dense and sparse linear algebra
routines and [libigl](https://github.com/libigl/libigl) for geometry processing
routines. We will make use of the OpenGL-based viewer used by the [libigl
tutorial](http://libigl.github.io/libigl/tutorial/tutorial.html). This viewer
also depends on [glfw](http://www.glfw.org/download.html), a library for
managing windows on Linux, Mac OS X and windows.

## Prerequisite installation

On all platforms, we will assume you have installed cmake.

We also assume that you have cloned this repository using the `--recursive`
flag (if not then issue `git submodule update --init --recursive`). 

> **Note for linux users:** Many linux distributions do not include gcc and the
> basic development tools in their default installation. On Ubuntu, you need to
> install the following packages:
>
>     sudo apt-get install git
>     sudo apt-get install build-essential
>     sudo apt-get install cmake
>     sudo apt-get install libx11-dev
>     sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev
>     sudo apt-get install libxrandr-dev
>     sudo apt-get install libxi-dev
>     sudo apt-get install libxmu-dev
>     sudo apt-get install libblas-dev

-------------------------------------------------------------------------------

> **Note for windows users:** libigl only supports the Microsoft Visual Studio
> 2015 compiler in 64bit mode. It will not work with a 32bit build and it will
> not work with older versions of visual studio.

## Layout

All assignments will have a similar directory and file layout:

    00-Introduction/
      README.md
      CMakeLists.txt
      main.cpp
      include/
        function1.h
        function2.h
        ...
      src/
        function1.cpp
        function2.cpp
        ...

The `README.md` file will describe the background, contents and tasks of the
assignment.

The `CMakeLists.txt` file setups up the cmake build routine for this
assignment.

The `main.cpp` file will include the headers in the `include/` directory and
link to the functions compiled in the `src/` directory. This file contains the
`main` function that is executed when the program is run from the command line.

The `include/` directory contains one file for each function that you will
implement as part of the assignment. **_Do not change_** these files.

The `src/` directory contains _empty implementations_ of the functions
specified in the `include/` directory. This is where you will implement the
parts of the assignment.

## Compilation

This and all following assignments will follow a typical cmake/make build
routine. Starting in this directory, issue:

    mkdir build
    cd build
    cmake ..
    make 

Why don't you try this right now?

## Execution

Once built, you can execute the assignment from inside the `build/` using 

    ./00-Introduction

After [compiling according to the instructions above](#compilation), if you try
executing right now, then you'll see a bunny:

![Screenshot of viewer displaying a bunny](../images/bunny-screenshot.jpg)

You can click and drag to change the view.

Optionally, this program can input a path to a triangle mesh file (other than
the bunny):

    ./00-Introduction [path to input file]

## Background

> Every assignment, including this one, will start with a **Background**
> section. This will review the math and algorithms behind the task in the
> assignment. Students following the lectures should already be familiar with
> this material and may opt to skip this section.

Let's get familiar with the _explicit_ mesh representation of a discrete
surface immersed in $\R^3$. Throughout the course, we will store the set of
mesh vertices $V$[^](#footnoteaboutmath) and the set of triangles (a.k.a.
faces) $F$ as two matrices: `V` and `F`.

The matrix `V` is $|V|$ by 3 in size, where the ith row of this matrix contains
the x-, y- and z-coordinates of the ith vertex of the mesh. 

The matrix `F` is $|F|$ by 3 in size, where the jth row of this matrix contains
the indices into the rows of `V` of the first, second and third corners of the
jth triangle as a non-negative number (remember in C++ arrays and matrices
start with index `0`). 

The information in `V` alone is purely positional and encodes the _geometry_ of
the surface.

The information in `F` alone is purely combinatoric and encodes the _topology_
of the surface. 

By convention, the indices in each row of `F` are _ordered_ counter-clockwise
around the triangle. Using the right-hand rule, we can define the normal of
each triangle as the vector that points _most away_ from the surface.

![The right-hand rule and the counterclockwise ordering convention defines the
normal of a triangle.](data/right-hand-rule.jpg)

Each oriented triangle also defines three _directed edges_ between its three
vertices. Other triangles in the mesh may contain edges with the same incident
vertices, possible in the opposite direction.  

![Two neighboring triangles may share the same (unoriented) edge (thick black).
In a consistently oriented mesh, these triangles' corresponding half-edges
(orange) will have opposite orientation.](data/half-edges.jpg)



For example,
an edge on the boundary of an _open_ mesh will show up once (one incident
face). 


For a triangle mesh representing a manifold surface, the number of vertices
$|V|$ and number of faces $|F|$ and number of edges $|E|$ are _intimately_
related and their relationship strictly depends on the _topology_ of the
surface that the mesh represents. We capture this relationship the _Euler
Characteristic_ $χ$ of the polyhedral surface:

$$
χ = |V| - |E| + |F|.
$$

This formula is known as _Euler's Formula_. We say that the Euler
Characteristic is a _topological invariant_ to mean that $χ$ will be the same
for any mesh of any surface with the _same topology_: same number of
boundaries, holes, connected components, etc. In this way, a triangle mesh of a
coffee mug (with a handle) will have the same Euler Characteristic as a
triangle mesh of a doughnut (with a hole).

## Tasks

Every assignment, including this one, will contain a **Tasks** section. This
will enumerate all of the tasks a student will need to complete for this
assignment. These tasks will match the header/implementation pairs in the
`include/`/`src/` directories.

### Groundrules

Libigl has implemented many of the tasks you'll find in this course. As a
result, for some assignments, including this one, you'll see a **Groundrules**
section that lists which functions you can and should use from libigl and/or
lists functions you may not use (and should avoid copying your answers from).

#### Blacklist libigl functions

For this assignment you may not use

 - `igl::all_edges`
 - `igl::edge_flaps`
 - `igl::edge_topology`
 - `igl::edges`
 - `igl::exterior_edges`
 - `igl::is_boundary_edge`
 - `igl::unique_edge_map`
 - or any other libigl function that returns a list of edges.

### Edges 

From a list of triangles `F`, construct a $|E|$ by 2 matrix `E`, where the kth
row of this matrix contains the indices into the rows of `V` of the start and
end point of the kth edge in the mesh. `E` should contain every _undirected
edge_ exactly once. 

### Euler Characteristic

From a given list of vertices `V` and list of triangles `F`, and the list of
edges `E` computed from the [previous task](#edges), compute the Euler
Characteristic `X` of the triangle mesh treated as the surface of a polyehdron.

------------------------------------------------------------------------------

> #### ^ Footnote about math 
>
> This markdown document, and those for all other assignments, contains
> $\LaTeX$ math. GitHub just shows the un-evaluated LaTeX code, but other
> markdown browsers will show the typeset math. You can also generate
> `README.html` using
> [multimarkdown](http://fletcherpenney.net/multimarkdown/):
>
>     cat ../shared/header.md README.md | multimarkdown -o README.html
>
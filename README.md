# procedural-buildings

## Compilation

The source code is provided as a CMake project that generates the **procedural_buildings** binary program.
To compile it just create a build folder, run **cmake** and then **make**.


## Execution

The program expects as input a grammar that specifies how we want to generate our buildings.

In the following section, we will be showing how this grammar can be specified.


## Grammar syntax

### Instantiating Primitives

The simplest thing we can do is instantiating a primitive shape, this is done as follows:

```
X -> I ( Cube )
```

The accepted primitive shapes are:
* **Cube**
* **Cylinder**
* **Sphere**


### Rules Composition

The right side of a rule can contain non terminal shapes which can be defined later.

```
X -> A B
A -> I ( Cube )
B -> I ( Sphere )
```


### Transforming the Scope

Internally, the program works with a scope that determines the position, orientation and size of the instantiated primitives.
One can think of the scope as a bounding box that is transformed around.
Primitives are then instantiated to fit inside it.


Some operations can be used to modify this scope in order to position the primitives where we wish:

* **T ( dx dy dz )**: Translates the scope around its local space
* **S ( sx sy sz )**: Sets the size of the scope along each dimension in its local space
* **Rx ( angle )**: Rotates the scope around its local x axis
* **Ry ( angle )**: Rotates the scope around its local y axis
* **Rz ( angle )**: Rotates the scope around its local z axis

```
X -> I ( Cylinder ) T ( 0.0 2.0 0.0 ) Ry ( 45.0 ) I ( Cylinder )
```


### Popping and Pushing the Scope

The current state of the scope can be saved (push) and restored (pop) by using the characters **[** and **]** respectively.

```
X -> Building1 Building2
Building1 -> [ T ( 8.0 0.0 0.0 ) S ( 5.0 1.0 5.0 ) I ( Cube )]
Building2 -> [ T ( 0.0 0.0 0.0 ) S ( 1.0 3.0 1.0 ) I ( Cube )]
```


### Random Parameters

Any parameter of the operations that transform a scope can be randomized inside a given range.

```
X -> Building Building
Building -> [ T ( R ( 0.0 10.0 ) 0.0 0.0 ) Ry ( R ( 0.0 30.0 ) )  I ( Cube ) ]
```


### Combining Rules with Probabilities

Rules might contain more than one right side, delimited by the character **|**.
Each right side must be given a probability.

```
X -> Block : 0.5 | Ball : 0.5
Block -> I ( Cube )
Ball -> I ( Sphere )
```


### Subdiv

The **Subdiv** operation subdivides the space represented by the current scope into several parts along one of its axis.
It has the following signature:

**Subdiv ( axis n f1 f2 ... fn ) ( s1 s2 ... sn)** where:
* axis is a number between 1 and 3 indicating the axis along which the space is subdivided
* n indicates the number of partitions
* fi indicates the fraction of space the i-th partition occupies
* si indicates the shape that occupies the i-th partition

```
X -> Subdiv ( 1 3 0.33 0.34 0.33 ) ( A A A )
A -> I ( Sphere )
```

## Some Complete Examples

### Recursive Grid

```
X -> Grid
Grid -> Subdiv ( 1 2 0.5 0.5 ) ( Grid Grid ) : 0.25 | Subdiv ( 3 2 0.5 0.5 ) ( Grid Grid ) : 0.2 | Base : 0.55
Base -> Block : 0.7 | Empty : 0.3
Block -> Ry ( R ( 0.0 30.0 ) ) I ( Cube )
Empty ->
```
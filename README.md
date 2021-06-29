# procedural-buildings
## Description
Procedural generator based on [shape grammar](https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.112.183&rep=rep1&type=pdf) built in C++.

## Demo
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/LCQWRYQ7m2Y/0.jpg)](https://youtu.be/LCQWRYQ7m2Y)

## Compilation

The source code is provided as a CMake project that generates the **procedural_buildings** binary program.
To compile it just create a _build_ folder, run **cmake** and then **make**.


## Execution

The program expects as input a grammar that specifies how we want to generate our buildings. This is specified in the [test.grammar](test.grammar) file.
The output model is written in the same _build_ folder named as **test.ply**. For easy visualization, an option could be to load it in an [online viewer](https://www.creators3d.com/online-viewer).

In the following section, we will be showing how this grammar can be specified.


## Grammar syntax

### Instantiating Primitives

The simplest thing we can do is instantiating a primitive shape, this is done as follows:

```
X -> I ( Cube )
```
**IMPORTANT:** spaces must be respected as in the proposed examples. Otherwise, the grammar will not be parsed correctly.

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

* **T ( dx dy dz )**: Translates the scope with *dx,dy,dz* being the translation vector in global coordinates.
* **Tr ( dx dy dz )**: Translates the scope with *dx,dy,dz* being the translation vector in local coordinates.
* **S ( sx sy sz )**: Sets the size of the scope along each dimension with respect to its parent scope.
* **Rx ( angle )**: Rotates the scope around its local x axis
* **Ry ( angle )**: Rotates the scope around its local y axis
* **Rz ( angle )**: Rotates the scope around its local z axis

```
X -> I ( Cylinder ) T ( 0.0 2.0 0.0 ) Rx ( 45.0 ) I ( Cylinder )
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

**Subdiv ( axis n f1 f2 ... fn ) ( s1 s2 ... sn )** where:
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

### City
```
X -> [ Floor ] T ( -50 0 5 ) City
City -> S ( 120 1 120 ) Subdiv ( 3 10 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 ) ( Street Street Street Street Street Street Street Street Street Street )
Street -> [ S ( 0.008 1 0.008 ) S ( 1 1 10 ) StreetBlocks ]
Floor -> S ( 120 0.1 120 ) I ( Cube )
StreetBlocks -> [ AddBuilding ] : 0.25 | [ AddBuilding ] [ Tr ( R ( 6 12 ) 0 0 ) StreetBlocks ] : 0.75

AddBuilding -> Block : 0.9 | Dome : 0.1 
Block ->  S ( 1 R ( 0.5 1.0 ) 1 ) [ BuildingOffset ] [ CornerOffset ] [ Ry ( 90 ) BuildingOffset ] [ Ry ( 90 ) CornerOffset ] [ Ry ( 180 ) BuildingOffset ] [ Ry ( 180 ) CornerOffset ] [ Ry ( 270 ) BuildingOffset ] [ Ry ( 270 ) CornerOffset ]
CornerOffset -> [ Tr ( -2 0 0 ) BuildingOffset ] [ Tr ( 2 0 0 ) BuildingOffset ]
BuildingOffset -> Tr ( 0 0 2 ) Building
Building -> S ( 2 R ( 9 10 ) 2 ) I ( Cube ) [ WindowsX ] [ Sidewings ]

Sidewings ->  Tr ( 0 0 0.5 ) Subdiv ( 1 3 0.2 0.4 0.4 ) ( Sidewing Sidewing Sidewing )
Sidewing -> Tr ( 0.5 0 0 ) S ( 1 R ( 0.2 0.5 ) 0.3 ) I ( Cube ) : 0.4 | Empty : 0.6

WindowsX -> Tr ( 0 0.2 0.5 ) Subdiv ( 2 4 0.25 0.25 0.25 0.25 ) ( Window Window Window Window )
Window -> S ( 0.1 0.1 0.1 ) I ( Cube )

Dome -> [ S ( R ( 5 6 ) R ( 30 35 ) R ( 5 6 ) ) I ( Sphere ) DomeDoors ]
DomeDoors -> [ Tr ( 0.5 0 0 ) Door ] [ Tr ( -0.5 0 0 ) Door ] [ Tr ( 0 0 0.5 ) Door ] [ Tr ( 0 0 -0.5 ) Door ]
Door -> [ S ( 0.07 0.03 0.07 ) I ( Cube ) ]

Empty -> 
```

More test samples can be found in [samples/grammar_samples](samples/grammar_samples).
  
  
## Work distribution
During the project we have discussed every step so that both of us know the details of the whole project. Still, we have delegated tasks in terms of design and implementation:  
- **Guillem Pérez**: Generation of primitives. Design and implementation of the rule substitution engine.
- **Santi Gonzalez**: Implementation of most available operations. File parsing, rule generation, and procedural application.


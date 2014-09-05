# anidmap

This is a small library that will be used primarily in the [Alux Operating System](https://github.com/unixpickle/alux). It facilitates the allocation of unique identifiers and the association of these identifiers with objects.

In the context of operating systems, this could be used to allocate file descriptors, process IDs, outgoing TCP/UDP port numbers, and more.

## Maps

anidmap includes a fixed-size hashmap structure ***HashMap*** for mapping objects to their identifiers. This is a subclass of the ***Map*** abstract class. In the future, I may create other methods of ID-object association, such as structures based on binary trees.

## Identifiers

An ***IdAllocator*** subclass can be used to allocate unique identifiers. Currently, there are two subclasses of this:

 * The ***PoolIdAllocator*** uses an expanding memory pool to track identifiers that have been freed.
 * The ***StepIdAllocator*** continually increments a counter until it needs to wrap around. To wrap around the identifier counter, *StepIdAllocator* finds a chunk of unused identifiers in **O(n^2)** time (with a hash-map backing).

## Identifier Maps

The ***IdMap*** class can be used to join the functionality of an *IdAllocator* with that of a *Map*. Since allocators may depend on a map to find unused IDs, you must use a specialized *IdMap* subclass for the type of *IdAllocator* you would like to use.

Currently, the *StepIdMap* and *PoolIdMap* classes serve as *IdMap* subclasses.

# Dependencies

**anidmap** is based on [ansa](https://github.com/unixpickle/ansa), a standalone structure for a standard library.

# Configuration

You must create an include (by whatever means necessary) that goes by the name of `<anidmap/lock>`. This header must define a class called `anidmap::Lock` that is a subclass of `ansa::Lock`. The `anidmap::Lock` class will be used for all synchronization in the library.

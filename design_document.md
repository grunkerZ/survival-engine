# High-Level Vision

* **Game Concept:** A 2D Arena Survival Game, Akin to games such as *Vampire Survivors*.
* **Technical Objective:** Maintain 60FPS while simulating thousands of active entities on the screen simultaneously.
* **Core Technology:** C++, SDL2 (for windowing, hardware rendering, and input polling)



## Memory Management Architecture

To maintain 60FPS under heavy entity load, the engine will not use dynamic allocation such as new/malloc during the core game loop

* **Object Pools:** All entities will be pre-allocated at startup into contiguous memory pools.
* **Cache Alignment:** Pool capacities will be in powers of two (e.g. 512) to optimize memory boundaries.
* **Justification:** This eliminates OS allocation overhead and prevents heap fragmentation, allowing for stable performance during when massive amounts of entities spawn.



## Core Engine Architecture

To maximize CPU Cache utilization the engine relies on a **Data-Oriented Design** rather than traditional Object-Oriented designs.

* **Entity Component System (ECS):** Logic is separated from the data to prevent cache misses.

  * **Entities:** Represented as integer IDs.
  * **Components:** Pure Data structures stored in contiguous arrays.
  * **Systems:** Logic loops that iterate linearly over component arrays, maximizing CPU Cache hits.



### Optimizations

* **Spatial Partitioning:** To optimize the collision detection. The game engine will divide the world into a spatial grid. Entities will only run collision checks against other entities occupying the same or adjacent grid partitions, reducing O(N^2) to near O(N).


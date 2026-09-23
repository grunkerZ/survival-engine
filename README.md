A custom-built 2D Game Engine and physics simulation written from scratch in C++ and SDL2. This project was built to explore Data-Oriented Design (DOD) and stress-test custom engine architecture against massive entity counts.

 ## Core Architecture & Design Document Rules

    This engine was built under a strict set of Technical Design constraints to maximize CPU performance and maintain a stable frame rate under extreme load:

    * **Zero-Dynamic-Allocation Memory Policy:** The custom Entity Component System (ECS) uses a pre-allocated `Registry` struct acting as a memory pool. By removing all runtime `new`/`delete` calls, the engine avoids memory fragmentation and handles rapid bullet/enemy spawning with zero stutter.
    * **Spatial Partitioning & Pushing Collisions:** To prevent the horde from perfectly stacking on top of each other, the engine uses a flocking separation algorithm. To prevent this $O(N^2)$ algorithm from dropping the frame rate, the engine hashes all entities into a 64x64 Spatial Grid every frame, reducing collision checks to $O(N)$.
    * **Dynamic Texture Registry:** Assets are loaded completely dynamically outside of runtime into an `AssetManager` map, allowing the engine to instantly share texture pointers across thousands of entities without duplicate hard drive I/O.
    * **Variable Delta-Time Loop:** Physics and cooldowns are entirely decoupled from the frame rate using a strict `dt` timestep, ensuring stable player speeds and auto-attack cooldowns regardless of hardware performance.

    ## Stress Testing
    * **Performance:** Sustains a stable 60 FPS with **4,000+ active entities** spread across the camera view.
    * **Degeneration Testing:** The engine was stress-tested by clustering ~3,000 entities directly on top of the player. The frame rate elegantly drops to ~30 FPS due to expected Spatial Grid bucket degeneration, proving the limits of the $O(N)$ partitioning when entities share the exact same grid cell.

    ## Gameplay Features
    * Infinite scrolling world with relative camera tracking.
    * *Vampire Survivors* style auto-shooting weapon that target the nearest enemy.
    * Core gameplay loop: Health arrays, XP drop spawning, and distance-based magnetic vacuum collection.

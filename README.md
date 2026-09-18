# cShip

Park a little wedge in a yellow bay. That’s the whole game.

Framebuffer only (`/dev/fb0`). 480×320. No X, no terminal UI.

## Build

```bash
make
./cDock
```
Do note, if you're on an ARM CPU, you'll need to execute,

```
rm -f *.o cDock
```

Look at the **device screen**, not the SSH window.

## Fly

| Key | What |
|-----|------|
| `W` ↑ Space | main engine |
| `A` `D` ← → | yaw |
| `J` `L` | RCS left / right |
| `I` `K` | RCS forward / back |
| `S` | kill spin |
| `R` | retry |
| `N` | next level (after a dock) |
| `P` | pause |
| `Q` | quit |

Nose of the triangle is where the fire comes out. Exhaust means you are spending fuel.

## Dock

Yellow rectangle = the bay.  
Gray box = the station. Do not hit it.

Hold inside the bay, slow, and roughly lined up for half a second. The HUD says **DOCKED**. Crash the hull or leave the map and it says **CRASH**.

Five short approaches. Last one spins and has a little gravity.

## Log

`/home/cdock.log` — wiped when you launch, left when you quit.



#### Why it exists
 Sepetember 2026 friends & I hosted a game jam, this is that. Very minimal Ai was used, mostly on the comments for the code and revising this readme!

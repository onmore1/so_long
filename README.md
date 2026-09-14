# so_long

A small 2D adventure game built for **42 School** using [MLX42](https://github.com/codam-coding-college/MLX42) and C. Explore the map, collect every coin, and escape through the exit — the exit only opens once all collectibles are gathered.

## Gameplay

- Move the player with **WASD** or the **arrow keys**.
- Press **ESC** to close the window.
- Every valid move is counted and printed to the terminal.
- Collect **all coins** to unlock the exit, then step onto it to win.

## Map Format

Maps are plain-text `.ber` files composed of the following characters:
*there is one map for you to test in maps folder

| Character | Meaning |
| --- | --- |
| `1` | Wall |
| `0` | Floor |
| `C` | Collectible |
| `E` | Exit |
| `P` | Player start |

Example:

```javascript
111111
1P0C01
100001
1C00E1
111111
```

A valid map must:

- Be rectangular (all lines the same length).
- Be fully surrounded by walls.
- Contain exactly **one** player start (`P`) and **one** exit (`E`).
- Contain at least **one** collectible (`C`).
- Contain only the valid characters above.
- Be beatable: every collectible and the exit must be reachable from the player's starting position (verified with a flood-fill).

Invalid maps are rejected with a descriptive error message and no memory leaks.

## Installation & Usage

### Requirements

- `cc` compiler with `-Wall -Wextra -Werror` support
- `cmake`, `make`, `git`
- `glfw` development libraries (`-lglfw`, `-ldl`, `-pthread`, `-lm`)

### Build

```bash
make            # builds MLX42 (cloned automatically), libft and the game
```

### Run

```bash
./so_long maps/map.ber
```

### Clean

```bash
make clean      # remove object files
make fclean     # remove objects + binaries + MLX42 build
make re         # full rebuild
```

## Project Structure

```javascript
so_long/
├── Makefile
├── so_long.h
├── so_long.c
├── Map/            # map parsing & validation (walls, symbols, playability)
├── Game/           # rendering, input handling, player/exit/coin init
├── Utils/          # helper & cleanup utilities
├── Bonus/          # bonus part (coin animation, frame pre-rendering, timer)
├── libft/          # custom C library incl. ft_printf & get_next_line
├── assets/         # sprites: idle/run animations, coins, tiles, exit
└── maps/           # .ber map files
```

## Bonus Features

- Animated coin sprites (pre-rendered frames swapped on a timer).
- Animated idle and run sprite sheets for the player.
- Smooth animation loop driven by MLX42's `mlx_loop_hook` and `get_time_ms()` timing.
- On-screen move counter.

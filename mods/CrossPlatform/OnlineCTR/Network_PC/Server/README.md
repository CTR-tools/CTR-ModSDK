### Compiling

For Windows open `SV_main.c` with VisualStudio.
For [Mingw](https://www.mingw-w64.org/)/Linux/Darwin use the `CMakeList.txt`.
[Nix](https://nixos.org/download/#download-nix) users can use `flake.nix`or `./build-native-gcc.nix` instead.

You can also serve via Docker with the following command (run from Server directory):

```sh
docker compose up --build
```

To build the container, run:
```SH
docker build env_ping -t env_ping_dock
```

To run the container on windows powershell, run (--rm: kill container if it exists, -i: interactive mode, -t: allocate a terminal to the container):
```SH
docker run --rm -it -v "${pwd}:/root/env" env_ping_dock
```

For linux run:
```SH
docker run --rm -it -v "$(pwd):/root/env" env_ping_dock
```

Once inside the container, simply run make to compile the project.

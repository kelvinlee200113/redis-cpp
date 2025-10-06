# Redis-CPP

A Redis-like in-memory key-value store implementation in C++.

## Overview

This project implements a Redis-like server from scratch to learn:
- Network programming with sockets
- Data structures (hash tables, AVL trees, heaps)
- Event loops for concurrent connections
- Protocol parsing and implementation
- Thread pools and asynchronous tasks

## Features

This implementation will include:
- [ ] TCP server with socket programming
- [ ] Event loop for handling multiple clients
- [ ] Basic Redis commands (GET, SET, DEL)
- [ ] Hash table implementation
- [ ] AVL tree for sorted sets
- [ ] Protocol parsing
- [ ] Thread pool for async operations

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./redis-server
```

## Tutorial Progress

Following the chapters from [Build Your Own Redis with C/C++](https://build-your-own.org/redis/):

- [ ] Chapter 1: Introduction
- [ ] Chapter 2: Socket Programming
- [ ] Chapter 3: Event Loop
- [ ] Chapter 4: Protocol Parsing
- [ ] Chapter 5: Data Structures
- [ ] Chapter 6: Hash Table
- [ ] Chapter 7: AVL Tree
- [ ] Chapter 8-14: Advanced Topics

## License

MIT License

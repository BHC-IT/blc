[![Actions Status](https://github.com/BHC-IT/blc/workflows/C%2FC++%20CI/badge.svg)](https://github.com/BHC-IT/blc/actions)
[![Actions Status](https://github.com/BHC-IT/blc/workflows/cpplint/badge.svg)](https://github.com/BHC-IT/blc/actions)
[![Coverage Status](https://coveralls.io/repos/github/BHC-IT/blc/badge.svg?branch=master)](https://coveralls.io/github/BHC-IT/blc?branch=master)
# BLC
library with useful tools

## Motivation
Provide wrappers for lowe-level syscalls/algorithms, with a high level interface.
Interfaces are as close as possible to STL or share a common interface with blc

# Important objects
## blc::pipe
Pipe without using a syscall in a multithreaded context
## blc::socket
Wrap C sockets with STL-like interface based on blc::stream
## blc::server
master interface for quickly implementing server like logic
## blc::actor
master interface for implementing actors (without group logic)

# Coding Style
_ in front of private class attributes

# BFC
Actor oriented framework
## Motivation
Multithreaded programs where threads can communicate safely via pipe

## Runtime Overview
bfc::flags // contains argv flags

## custom actors (virtual functions)
 1. make your actor inherit bfc::actor. constructor is `actor(blc::tools::pipe pipe, std::string name)` You must call this->start() at the end of the constructor, to launch a thread containing this actor.
 2. define `void tick()` // function called every few milliseconds throughout prog
 3. define `void masterProto()` // contains all behaviors of the actor depending on communications with masterThread. You can add a protocolFactory to `this->_masterProto` here. you should call this at actor construction yourself

`blc::pipe`: You can communicate with static functions that return an end of the pipe
One end is privately owned by the actor.
Note. blc::actor is a parent of bfc::actor

`blc::protocolFactory<int, std::string> _masterProto`

bfc::initActor() // called first, initialize your actor here
bfc::masterThread::readActor // what to do when someone writes to this actor
bfc::masterThread::tick() // called regularly (every few milliseconds) throughout prog
bfc::closure()  // called at program exit
bfc::factory(std::string name, Args&& args) // create an actor

## Architecture of a program using bfc
.
|-- dep/ dependencies
|-- dev/ your project sources
|-- bfc/ bfc headers
`-- src/ bfc cpp files
`

## TODO
inter-actor signals
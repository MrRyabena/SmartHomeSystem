#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  An abstract class describing a process,
  i.e. an entity that can be started, cycled, and stopped.
*/


namespace shs
{
    class Process;
};

class shs::Process
{
public:
    virtual ~Process() = default;

    virtual void start() = 0;
    virtual void tick() = 0;
    virtual void stop() = 0;
};

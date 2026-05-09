#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — Function names have been changed.
    v2.3.0 — updated docs.
*/

namespace shs
{
    class Process;
};

/**
 * @brief Abstract process interface for entities that can be started, ticked, and stopped.
 */
class shs::Process
{
public:
    /**
    * @brief Destroys the process interface.
     */
    virtual ~Process() = default;

    /**
     * @brief Starts the process lifecycle.
     */
    virtual void start() = 0;

    /**
     * @brief Advances the process by one cycle.
     */
    virtual void tick() = 0;

    /**
     * @brief Stops the process lifecycle.
     */
    virtual void stop() = 0;
};

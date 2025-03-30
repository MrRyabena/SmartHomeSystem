# shs_Process.h

## General Description

This file contains the definition of the `shs::Process` class, which serves as an abstract base class for processes within the Smart Home System. The class provides a framework for managing entities that can be started, cycled, and stopped, facilitating the implementation of the event loop pattern.

## Versions

- **v0.2.0** — created.
- **v1.0.0** — release.
- **v2.0.0** — function names have been changed.

---

## Class `shs::Process`

### Description

`shs::Process` is an abstract class that defines the interface for processes in the Smart Home System. It provides methods for starting, cycling (updating), and stopping processes, allowing for organized and efficient management of system components.

### Members

This class does not have any member variables, as it is intended to be a base class for derived classes that implement specific process functionality.

---

### Methods

- ##### `start()`

  ```cpp
  virtual void start() = 0;
  ```

  - ##### Description

    Starts the process. This method must be implemented by derived classes to define the specific behavior when the process is initiated.

---

- ##### `tick()`

  ```cpp
  virtual void tick() = 0;
  ```

  - ##### Description

    Updates the state of the process. This method is called in a loop to perform periodic actions. It must be implemented by derived classes to define the specific behavior during each cycle.

---

- ##### `stop()`

  ```cpp
  virtual void stop() = 0;
  ```

  - ##### Description

    Stops the process. This method must be implemented by derived classes to define the specific behavior when the process is terminated.

---

### Example Usage

```cpp
#include <shs_Process.h>

class MyProcess : public shs::Process 
{
public:
    void start() override 
    {
        // Initialization code
    }

    void tick() override 
    {
        // Code to execute on each cycle
    }

    void stop() override 
    {
        // Cleanup code
    }
};

MyProcess myProcess;
myProcess.start();              // Start the process
while (true) myProcess.tick();  // Update the process
myProcess.stop();               // Stop the process
```

---

## Conclusion

The `shs::Process` class is a fundamental component of the Smart Home System, providing a robust framework for managing processes. Its methods facilitate the implementation of the event loop pattern, ensuring efficient operation and organization of system components.

#pragma once

/* Patriot-DHT library by Ron Lisle
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

// This is your main class that users will import into their application
class PatriotDHT
{
public:
  /**
   * Constructor
   */
  PatriotDHT();

  /**
   * Example method
   */
  void begin();

  /**
   * Example method
   */
  void process();

private:
  /**
   * Example private method
   */
  void doit();
};

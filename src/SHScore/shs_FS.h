#pragma once

/*
  This is a bad version, it will be completely rewritten.
*/

/*
  Last update: v1.2.0
  Versions:
    v1.2.0 — created.
*/

#include "shs_settings_private.h"
#include "shs_FileAbstract.h"
#include "shs_FSAbstract.h"

#include <stddef.h>
#include <stdint.h>

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#include <FS.h>
#else
#include <fstream>
#include <filesystem>
#endif


namespace shs
{
  class FS;
}

class shs::FS : public shs::FSAbstract
{
public:
  explicit FS(shs::fs::FS_basic_t* fs = nullptr);

  shs::fs::FS_basic_t* fsb;

public:
  // Added methods
  bool copy(const char* from, const char* to);

  // Overridden methods
  shs::fs::File_basic_t* open(const char* path, const char* mode = shs::fs::File_Write, const bool create = false) override;
  void close(shs::FileAbstract& file) override { file.close(); }

  bool exists(const char* path) override;
  bool rename(const char* pathFrom, const char* pathTo) override;
  bool remove(const char* path) override;
  bool mkdir(const char* path) override;
  bool rmdir(const char* path) override;
};

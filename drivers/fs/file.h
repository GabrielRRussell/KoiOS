#ifndef FILE_H
#define FILE_H

typedef struct file_t {
  uint8_t permissions;      // R/W
  uint64_t seek;            // Seek as bytes
  char filename[11];        // Eight Characters, and Three Ext
  uint32_t directory_entry; // Disk Address of Directory Entry
  uint32_t file_size;       // File Size in Bytes
  void* buffer;             // File Buffer Location
} file_t;

#endif

/*
Created by Olin Gilster S'26
This work is subject to the MIT License (https://opensource.org/licenses/MIT)
*/

#ifndef OGAR_H
#define OGAR_H

#include <stdint.h>
#include <sys/types.h>

#define OGAR_MAGIC "OGAR1\n\0"
#define OGAR_MAGIC_LEN 7

/*
OGAR ARCHIVE FORMAT (HIGH-LEVEL ASCII MAP)

  +-------------------------------+
  | ogar_header_t (fixed-size)    |
  +-------------------------------+
  | record 0                      |
  |  +-------------------------+  |
  |  | ogar_record_hdr_t       |  |
  |  +-------------------------+  |
  |  | filename bytes          |  |
  |  +-------------------------+  |
  |  | ogar_meta_t             |  |
  |  +-------------------------+  |
  |  | data bytes              |  |
  |  +-------------------------+  |
  | record 1                      |
  |   ...                         |
  +-------------------------------+
  | TOC (table of contents)       |  <-- written at end
  |  uint64_t count               |
  |  repeated entries:            |
  |    name_len, name             |
  |    record_offset              |
  |    raw_size, stored_size      |
  |    mtime, comp_method         |
  |  "OTOC" footer + toc_bytes    |
  +-------------------------------+

  */

  // Marks the start of each file record in the archive.
#define OGAR_REC_MAGIC "OREC"

// Marks the TOC footer region (used to sanity-check TOC).
#define OGAR_TOC_MAGIC "OTOC"

#define OGAR_VERSION 1

typedef enum {
    OGAR_COMP_NONE = 0, // Store file bytes as-is
    OGAR_COMP_DEFLATE = 1 // zlib/deflate compression
} ogar_comp_t;

// stored metadata
typedef struct {
    uint64_t mode;     
    uint64_t uid;      
    uint64_t gid;     

    uint64_t mtime;  
    uint64_t atime;   
    uint64_t ctime;   

    uint64_t size;    
    uint64_t inode;    
    uint64_t nlink;  
} ogar_meta_t;

// Table of Contents entry
typedef struct {
    char    *name;          // Filename (malloc'd)
    uint64_t record_offset; // Byte offset where ogar_record_hdr_t begins
    uint64_t raw_size;      // Uncompressed size
    uint64_t stored_size;   // Compressed/raw stored size
    uint64_t mtime;         // For quick display/sorting
    uint8_t  comp_method;   // ogar_comp_t
} ogar_toc_entry_t;

// ogar header struct - fixed-size header written at the start of the archive
typedef struct {
    char     magic[OGAR_MAGIC_LEN]; // must match OGAR_MAGIC
    uint8_t  version;               // OGAR_VERSION

    uint16_t header_bytes;          // total header bytes (including padding)
    uint8_t  pad_bytes;             // 0..7 padding bytes after this struct
    uint8_t  reserved0;             // reserved (set to 0)

    uint64_t toc_offset;            // byte offset of TOC start (0 if no TOC yet)
    uint64_t toc_bytes;             // total size of TOC section in bytes (0 if no TOC yet)
} ogar_header_t;

// ogar record header struct
typedef struct {
    char     rec_magic[4];    // "OREC"
    uint32_t name_len;        // filename length (no null terminator)

    uint8_t  comp_method;     // ogar_comp_t
    uint8_t  reserved1[3];    // explicit padding

    uint32_t crc32;           // CRC32 of raw (uncompressed) bytes
    uint64_t raw_size;        // uncompressed size
    uint64_t stored_size;     // bytes stored in archive (compressed or raw)
    uint32_t meta_bytes;      // metadata block size (usually sizeof(ogar_meta_t))
} ogar_record_hdr_t;

#endif // OGAR_H
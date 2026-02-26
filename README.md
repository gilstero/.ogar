Got it — here is a **fully copy-paste ready `README.md` in pure Markdown**.

You can paste this directly into `README.md`.

---

# OGAR – A Custom Archive Format in C

Created by Olin Gilster S’26
Licensed under the MIT License

---

## Overview

**OGAR** is a custom archive framework written in C, inspired by the Unix `ar` utility but redesigned with:

* A distinct binary format
* Optional compression (zlib / deflate)
* Richer metadata storage than `ar`
* An explicit Table of Contents (TOC)
* Append-friendly record layout

This project explores low-level systems programming concepts including:

* Binary file layout design
* Manual struct serialization
* File offset management
* Metadata preservation
* Compression integration
* Archive indexing

OGAR is intentionally designed from scratch to better understand how archive formats work internally.

---

## Features

* Create archive files
* Append individual files
* Append files older than 10 days
* Extract individual files
* Extract all files
* List archive contents
* Optional per-file compression
* Rich metadata preservation

---

## Build

Requires:

* macOS or Linux
* `clang` or `gcc`
* `zlib`

Build using Make:

```bash
make
```

Or manually:

```bash
clang -Wall -Wextra -O2 ogar.c ogar_utils.c -lz -o ogar
```

---

## Usage

```
./ogar -c archive.ogar            # Create archive
./ogar -q archive.ogar file1      # Append file
./ogar -a archive.ogar            # Append files older than 10 days
./ogar -v archive.ogar            # List contents
./ogar -x archive.ogar file1      # Extract single file
./ogar -X archive.ogar            # Extract all files
```

Optional flags:

```
-z   Enable deflate compression
```

---

## OGAR File Format

### High-Level Layout

```
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
```

---

## Header Structure

The archive begins with a fixed-size header:

* Magic bytes (`"OGAR1\n\0"`)
* Version
* TOC offset
* TOC size

The header allows:

* Fast TOC lookup
* Format versioning
* Archive validation
* Future extensibility

---

## Record Structure

Each file stored in the archive consists of:

1. Record header
2. Filename bytes
3. Metadata block
4. File data (raw or compressed)

The record header stores:

* Compression method
* Raw file size
* Stored size
* Metadata size
* (Optional) checksum

Records are append-only, making the archive efficient for incremental updates.

---

## Stored Metadata

For each file, OGAR stores:

* File mode (permissions + type)
* User ID
* Group ID
* Modification time
* Access time
* Change time
* Original file size
* Inode
* Link count

This allows accurate reconstruction during extraction.

---

## Compression

OGAR supports per-file compression:

* `OGAR_COMP_NONE`
* `OGAR_COMP_DEFLATE` (zlib)

Compression is optional and applied independently to each file.

---

## Design Philosophy

* Explicit binary layout
* No reliance on implicit compiler padding
* Append-only record structure
* Offset-based TOC
* Clean format versioning
* Educational focus on systems-level thinking

---

## Future Improvements

Potential extensions:

* CRC32 validation for corruption detection
* Solid (multi-file) compression blocks
* Deduplication using file hashes
* Encryption layer
* Streaming extraction mode
* Cross-platform endianness handling
* Multi-threaded compression

---

## License

MIT License
[https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT)

---
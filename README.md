1. Project Overview

This project implements a command-line based MP3 Tag Reader and Editor using the C programming language.
It allows users to view and modify ID3v2 metadata present in MP3 audio files by performing low-level binary file operations.

The project focuses on understanding:

Binary file formats

Endianness handling

Structured data parsing

Safe file modification techniques

2. Objectives

To understand the internal structure of MP3 (ID3v2) metadata

To implement binary file read/write operations using C

To safely edit metadata without corrupting the MP3 file

To gain hands-on experience with file offsets and endian conversion

3. Features Implemented
3.1 MP3 Validation

Verifies the presence of the ID3 identifier

Confirms whether the given file is a valid MP3 file

3.2 View MP3 Tags

Displays the following ID3v2 frames:

TIT2 – Title

TPE1 – Artist

TALB – Album

TYER – Year

TCON – Content/Genre

COMM – Comment

3.3 Edit MP3 Tags

Allows modification of individual tags using command-line options while preserving:

Frame structure

Frame alignment

Remaining metadata and audio data

4. Technologies & Concepts Used

Language: C

Operating System: Linux / WSL

Compiler: GCC

Core Concepts:

Binary file handling (fread, fwrite, fseek)

Big-endian to little-endian conversion

ID3v2 frame parsing

File pointer management

Temporary file replacement strategy

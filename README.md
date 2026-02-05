# MP3 Tag Reader and Editor in C

## Description
A simple C-based MP3 metadata reader and editor that allows you to view and modify ID3v2 tags such as Title, Artist, Album, Year, Genre, and Comment directly from the terminal.
This project was built to understand binary file handling, endianness, and low-level file manipulation in C.

## Technologies Used
- Language: C
- Concepts:
    - File handling (fread, fwrite, fseek)
    - Binary mode I/O
    - Endianness conversion
    - ID3v2 frame structure
- Platform: Linux / WSL / GCC

## Features
### 1.MP3 Validation
- Verifies the presence of the ID3 identifier
- Confirms whether the given file is a valid MP3 file

### 2.View MP3 Tags
Displays the following ID3v2 frames:
1. TIT2 – Title
2. TPE1 – Artist
3. TALB – Album
4. TYER – Year
5. TCON – Content/Genre
6. COMM – Comment

### 3.Edit MP3 Tags
Allows modification of individual tags using command-line options while preserving:
1. Frame structure
2. Frame alignment
3. Remaining metadata and audio data

## snapshots
<img width="877" height="187" alt="image" src="https://github.com/user-attachments/assets/5f7ca36a-95cf-4754-9410-bb20fdde8ed4" />
<img width="887" height="343" alt="image" src="https://github.com/user-attachments/assets/e65e1a43-51b9-4d15-8219-fdabd082a057" />
<img width="887" height="247" alt="image" src="https://github.com/user-attachments/assets/f8ac78d0-ff24-44d1-a752-ffa1cfd8e4d1" />
<img width="892" height="283" alt="image" src="https://github.com/user-attachments/assets/3385db5f-76e2-474d-855b-901105a61f21" />


## ▶ How to Run
```bash
gcc *.c 
./a.out -v original.mp3 (View MP3 Metadata)
./a.out -e -t "New Title" original.mp3 (Edit MP3 Metadata)
./a.out --help (help menu)





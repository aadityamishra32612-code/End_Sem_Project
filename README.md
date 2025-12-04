# Mini Text Editor in C

## Project Overview
This project is a **Mini Text Editor** implemented in the C programming language.  
It allows users to **open, view, edit, insert, delete, and save text files** directly through a console-based interface.  
The project demonstrates the practical use of **C fundamentals, arrays, functions, structures, pointers, dynamic memory allocation, file handling**, and **preprocessor macros**.  
It also includes modular design practices that can be extended using **static and shared libraries**.

---

##  Developers
- **Aditya Mishra (B-78) 590029219**
- **Shashwat Agrawal (B-78) 590029107**

---

## Aim of the Project
To design and implement a lightweight text editor in C that supports essential file editing operations while demonstrating core programming concepts such as dynamic memory management, pointers, file operations, and modular programming.

---

##  Features
* Open/Load a text file  
* Display file contents with line numbers  
* Insert a new line at any position  
* Delete a line from the file  
* Save the edited content to a file  
* Dynamic memory allocation using `malloc`, `realloc`, and `free`  
* Full pointer-based text buffer management  
* Clean and modular code structure  

---

## Core Concepts Used
| Concept | Usage |
| **Structures** | Stores dynamic text buffer and metadata |
| **Pointers** | Handles array of lines and memory operations |
| **Dynamic Memory Allocation** | Grows buffer size using `malloc` & `realloc` |
| **File Handling** | Uses `fopen`, `fgets`, `fputs`, `fclose` |
| **Arrays & Strings** | Stores and processes text lines |
| **Functions** | Modular operations like insert, delete, display |
| **Preprocessor Macros** | Constants like buffer sizes |
| **Memory Management** | Manual freeing of each allocated line |

---

## System Design
The program is built around a `TextBuffer` structure:

```c
typedef struct {
    char **lines;
    int line_count;
    int capacity;
    char filename[256];
} TextBuffer;
```

## How to Compile and Run
Compile:
```
gcc main.c -o text_editor
```
Run:
```
./text_editor
```
## File Operations Supported

### * load_file() – Reads file into memory

### * display_buffer() – Prints all lines

### * insert_line() – Inserts text at a chosen position

### * delete_line() – Removes a line

### * save_file() – Writes buffer contents back to disk

## Future Enhancements

### 🔹 Add undo/redo feature
### 🔹 Implement search & replace
### 🔹 Add support for static and shared libraries
### 🔹 Implement a small command-line scripting mode

## Conclusion

### This Mini Text Editor demonstrates how powerful the C language can be for memory-efficient applications.
### It successfully integrates multiple core concepts of programming and provides a functional, easy-to-use text editing tool.

### Project developed by Aditya Mishra and Shashwat Agrawal (B-78).

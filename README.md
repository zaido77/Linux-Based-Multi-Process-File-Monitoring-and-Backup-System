# Linux-Based Multi-Process File Monitoring and Backup System

## Overview
The **Linux-Based Multi-Process File Monitoring and Backup System** is a low-level systems programming project designed to automate the detection and archiving of text-based data. 

The system leverages a parent-child concurrent architecture to separate concerns between file system scanning and event logging. By utilizing Unix Pipes (IPC) and signal handling, the system provides a robust environment for monitoring file changes in real-time, validating file integrity, and maintaining backup repository.

## System Architecture
The system is divided into four main functional components:

### Parent Process (Producer)
The primary execution thread responsible for directory traversal. It utilizes `dirent.h` to scan the target path, filters for `.txt` extensions, and extracts metadata via the `stat` system call.

### Child Process (Consumer)
A concurrent process spawned via `fork()`. It remains in a waiting state until data is received through the IPC layer, at which point it logs the metadata and writes to the system report.

### IPC Layer (Unix Pipe)
A unidirectional communication channel that facilitates the transfer of the `FileInfo` structure from the Parent to the Child. This ensures that the two processes remain synchronized without shared memory conflicts.

### Backup & Logic Layer
A specialized module that performs physical file duplication using `read/write` buffers. It includes validation logic to skip empty files and handle directory permission errors.

## Key Features
* **Multi-Process Concurrency:** Efficient separation of scanning and logging tasks using `fork()`.
* **Inter-Process Communication:** Robust data streaming via Unix Pipes.
* **Dynamic Memory Management:** Efficient heap allocation for file tracking using `malloc` and `free`.
* **Automated Backup Logic:** Intelligent filtering and duplication of text files to a secure directory.
* **System-Level Debugging:** Built-in support for GDB (GNU Debugger) and Valgrind memory analysis.
* **Signal Handling:** Graceful shutdown and interrupt management using `SIGINT`.

## Project Structure
* `src/main.c` — Entry point; handles process synchronization and IPC setup.
* `src/scanner.c` — Logic for directory traversal and metadata extraction.
* `src/backup.c` — File duplication and backup validation logic.
* `src/logger.c` — Child process logic for generating the `report.txt`.
* `src/FileInfoStruct.h` — Definition of the shared data structure used in IPC.
* `scripts/run_system.sh` — Automation script for building and executing the system.
* `logs/report.txt` — The final system-generated activity log.

## Setup Instructions
1. **Prepare Environment:** Ensure you are using a Linux-based environment (Ubuntu, Kali, or WSL).
2. **Install Dependencies:** Ensure `gcc`, `make`, and `gdb` are installed via `sudo apt install build-essential gdb`.
3. **Configure Permissions:** Run `chmod +x scripts/run_system.sh` to make the automation script executable.
4. **Build and Run:** Execute the system by running `./scripts/run_system.sh`.
5. **Review Logs:** Check the `logs/report.txt` file for a detailed summary of the monitoring session.

## Authors
Zaid Irsheid.
Mohammad Touqan.
Khaled Mohammed.
Yousuf Nasser.

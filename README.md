# Dynamic Array Processing in C

## Overview

This project implements a C program that processes records from a file (`dataloger.txt`) containing data from a measurement module. The program performs various commands entered by the user through standard input, such as opening files, creating dynamic arrays, validating data, and generating outputs.

## Commands

- **`v`**: Opens the data file (`dataloger.txt`) and reads its content into dynamically allocated memory. If the file cannot be opened, it prints `Neotvoreny subor`.

- **`o [module] [type]`**: Sorts and displays records based on the given measurement module and type. The data is ordered by time and date. The module can be one of `A1`, `A2`, or `A11`, and the type can be one of `R1`, `R2`, `R3`, `U1`, `U2`, or `U3`. If the module and type are not found, it prints `Pre dany vstup neexistuje zaznam`.

- **`n`**: Creates dynamic arrays to store data entries. If the dynamic arrays have already been created, it prints `Pole je uz vytvorene`.

- **`c`**: Validates the data for correctness. This includes checking the format and ranges of the values. If any incorrect data is found, it prints a list of errors.

- **`s [module] [type]`**: Saves the sorted data for the specified module and type to a file named `vystup_S.txt`. The data is ordered by time and date. It prints `Pre dany vstup je vytvoreny txt subor`.

- **`h [type]`**: Generates a histogram for the given type. The type can be one of `R1`, `R2`, `R3`, `U1`, `U2`, or `U3`. The histogram is displayed in the console.

- **`r`**: Displays measurement times in a reduced time format (hours and minutes only) instead of the full timestamp.

- **`z [ID]`**: Deletes records for the specified ID. The ID must be an existing record identifier. It prints the number of deleted records.

- **`k`**: Deallocates all dynamically allocated memory, closes any open files, and exits the program. It ensures a clean termination of the program.

# University Ranking System

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Data Structure](#data-structure)
6. [Algorithms](#algorithms)
7. [File Structure](#file-structure)
8. [Contributing](#contributing)
9. [License](#license)

## Introduction

This University Ranking System is a C++ application designed to manage and analyze university rankings. It provides functionalities for both customers and administrators to interact with university data, manage user accounts, and handle feedback.

## Features

### For Customers:
- User registration and login
- View and sort universities based on various criteria
- Search for universities by institution name or location
- Save and view favorite universities
- Send feedback and view replies

### For Administrators:
- View and modify user details
- Delete inactive user accounts
- Navigate and reply to customer feedback
- Generate reports on top universities

### General Features:
- Display all universities
- Sort universities using different algorithms
- Search universities using different search methods

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/university-ranking-system.git
   ```
2. Navigate to the project directory:
   ```
   cd university-ranking-system
   ```
3. Compile the program:
   ```
   g++ app.cpp -o university_ranking_system
   ```

## Usage

Run the compiled program:
```
./university_ranking_system
```

Follow the on-screen prompts to navigate through the system's functionalities.

## Data Structure

The project uses several data structures:

1. `LinkedList`: For managing user accounts
2. `BinarySearchTree`: For efficient university lookups
3. `HashTable`: For quick user authentication
4. `Vector`: For storing and manipulating university data

## Algorithms

The system implements various algorithms:

1. Sorting Algorithms:
   - Bubble Sort
   - Quick Sort

2. Search Algorithms:
   - Linear Search
   - Binary Search

## File Structure

- `app.cpp`: Main application file containing all the code
- `universities.csv`: CSV file containing university ranking data
- `README.md`: This file, containing project documentation

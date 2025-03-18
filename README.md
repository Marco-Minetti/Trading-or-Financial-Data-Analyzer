# Financial Data Analyzer

## Overview
The **Financial Data Analyzer** is a C-based tool designed to efficiently process and analyze large stock market datasets. It can read historical trading data, compute key financial metrics like moving averages and volatility, and provide a simple command-line interface for querying stock prices.

## Features
- **Efficient CSV Parsing:** Reads large stock market datasets.
- **Data Structures:** Utilizes linked lists, hash tables, or trees for optimized data handling.
- **Computations:** Calculates moving averages, max/min prices, and volatility.
- **Filtering:** Users can filter data by date range or stock symbol.
- **Parallel Processing (Optional):** OpenMP for faster calculations.
- **Command-line Queries:** Allows users to search stock prices by date.

## Project Structure
```
financial_data_analyzer/
│── src/                   # Source code directory
│   ├── main.c             # Main program
│   ├── csv_reader.c       # CSV file handling
│   ├── csv_reader.h
│   ├── data_structures.c  # Linked list, hash table, tree for data storage
│   ├── data_structures.h
│   ├── analytics.c        # Moving averages, volatility calculations
│   ├── analytics.h
│   ├── query_interface.c  # Command-line queries
│   ├── query_interface.h
│   ├── parallel_processing.c # OpenMP parallelization (optional)
│   ├── parallel_processing.h
│── data/                  # Sample CSV stock data
│── tests/                 # Unit tests
│── docs/                  # Documentation
│── Makefile               # Compilation instructions
│── README.md              # Project overview & usage
│── .gitignore             # Ignore compiled files
```

## Installation & Compilation
1. Clone the repository:
   ```sh
   git clone <your-repo-url>
   cd financial_data_analyzer
   ```
2. Compile the project using Makefile:
   ```sh
   make
   ```

## Usage
To run the program and analyze a stock data CSV file:
```sh
./analyzer TODO: put the line
```
Example command-line query:
```sh
./analyzer TODO: put the line
```

## License
This project is open-source and free to use for educational purposes.


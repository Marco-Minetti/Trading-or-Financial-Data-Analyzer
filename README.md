# 📊 Trading or Financial Data Analyzer

## Overview

**Trading or Financial Data Analyzer** is a C-based tool for analyzing both historical and live stock-market data.  
It reads CSVs or fetches live data via the Finnhub API, computes metrics (SMA, min/max, volatility), supports advanced filtering, and offers binary save/load—all via a CLI.

---

## ✨ Features

- 📄 CSV parsing of historical data  
- 🌐 Live data fetching (Finnhub API)  
- 📚 Dynamic data structures (linked lists, hash tables, trees)  
- 📈 Financial metrics: SMA, min/max prices, volatility  
- 🔎 Filters: date range, symbol, price ranges, positive/negative changes  
- 💾 Binary file save/load  
- 🏎️ (Optional) OpenMP parallelism  
- 🖥️ Full CLI interface  

---

## 📂 Project Structure

```
Trading-or-Financial-Data-Analyzer/
│
├── src/                # All C source & header files
│   ├── main.c
│   ├── binary_io.c
│   ├── binary_io.h
│   ├── data_structures.c
│   ├── data_structures.h
│   ├── analytics.c
│   ├── analytics.h
│   ├── query_interface.c
│   ├── query_interface.h
│
├── data/               # Example CSVs
│   └── stock_data.csv
│
├── bin/                # Generated binary files (optional)
│   └── stock_data.bin
│
├── docs/               # Additional documentation
│
├── tests/              # Unit tests
│
├── Makefile            # Build script
├── README.md           # ← You are here
├── program             # Compiled executable (git-ignored)
└── .gitignore
```

---

## 🛠️ Installation & Compilation

```bash
git clone https://github.com/Marco-Minetti/Trading-or-Financial-Data-Analyzer.git
cd Trading-or-Financial-Data-Analyzer
make
```

This produces the `analyzer` executable.

---

## 🚀 Usage

```bash
./bin/analyzer -m <mode> [options]
```

### Modes

| Mode  | Description                                         |
|:-----:|:----------------------------------------------------|
| `csv` | Analyze historical data from a CSV file             |
| `live`| Fetch & analyze live data from the Finnhub API      |

---

### Options

#### CSV Mode (`-m csv`)

| Option           | Description                          |
|:-----------------|:-------------------------------------|
| `-f <csv_file>`  | Path to input CSV file               |
| `-b`             | Save parsed data to a binary file    |
| `-r`             | Read data from an existing binary    |

#### Live Mode (`-m live`)

| Option             | Description                                      |
|:-------------------|:-------------------------------------------------|
| `-t <duration>`    | Seconds to fetch live data                       |
| `-y <symbol>`      | Stock symbol (default: AAPL)                     |

#### Common Options

| Option            | Description                                                      |
|:------------------|:-----------------------------------------------------------------|
| `-s <start_date>` | Filter analysis starting at this date                            |
| `-e <end_date>`   | Filter analysis ending at this date                              |
| `-c <+ or ->`     | Change filter: `+` for positive changes, `-` for negative changes |
| `-p <min:max>`    | Closing price range filter                                      |
| `-h <min:max>`    | High price range filter                                         |
| `-l <min:max>`    | Low price range filter                                          |
| `-w <window>`     | SMA window size (default: 5)                                    |
| `-H`              | Display help message                                            |

---

## Example Commands

```bash
# Analyze CSV from 2024, 20-day SMA
./analyzer -m csv -f data/stock_data.csv -s 2024-01-01 -e 2024-12-31 -w 20

# Save CSV data to binary
./analyzer -m csv -f data/stock_data.csv -b

# Load from binary
./analyzer -m csv -r -f bin/stock_data.bin

# Fetch live TSLA data for 60s
./analyzer -m live -t 60 -y TSLA
```

---

## 📜 License

Licensed under the [MIT License](https://opensource.org/licenses/MIT).  
Use, modify, and distribute freely; provided “as-is” with no warranty.

---

## 🤝 Contributing

Fork, branch, and PR. Issues and suggestions welcome at the [GitHub repo](https://github.com/Marco-Minetti/Trading-or-Financial-Data-Analyzer/issues).

---

## 📬 Contact

Maintained by **Marco Minetti**.  
Questions? Open an issue!

# 🇵🇸 Palestinian Cities Road Network - MST Project (COMP2421 Project #3)

## 📌 Overview

This project focuses on building a **Minimum Spanning Tree (MST)** to efficiently connect a group of Palestinian cities and towns with the lowest possible road construction cost. It implements and compares two classic algorithms used for MST generation:

- **Prim's Algorithm**
- **Kruskal's Algorithm**

The objective is to find the most optimized way to construct a road network and to analyze the performance of both algorithms by calculating their execution time.

---

## 🗂️ Key Features

- 📥 Load city connections and distances from an external file (`cities.txt`)
- 🧠 Dynamically build an undirected weighted graph representing cities and roads
- ⚙️ Apply both **Prim's** and **Kruskal's** MST algorithms
- 💵 Display the resulting MST along with its total cost
- ⏱️ Measure and display the execution time for each algorithm
- 📊 Provide a side-by-side performance comparison
- 🖥️ Easy-to-use **menu-based command-line interface**

---

## 🧪 Sample Input Format (`cities.txt`)

Akka#Haifa#35
...

---

## 🖥️ Program Menu

When the program is executed, the following options are displayed to the user:

1. **Load Cities**  
   → Reads the data from `cities.txt`, constructs the graph, and shows its size and number of cities.

2. **Apply Prim’s Algorithm**  
   → Asks the user for a source city, then applies Prim’s algorithm and displays the MST with its total cost and execution time.

3. **Apply Kruskal’s Algorithm**  
   → Runs Kruskal’s algorithm to generate the MST, showing total cost and time.

4. **Compare the Two Algorithms**  
   → Outputs a comparison of both algorithms based on cost and performance.

5. **Exit**  
   → Ends the program.

---

## ⏱️ Measuring Execution Time

Execution time is tracked using the `clock()` function from the C standard library `<time.h>`:


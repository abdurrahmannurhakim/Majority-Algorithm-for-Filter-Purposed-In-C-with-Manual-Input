# Majority and Minority Selection Algorithm for Filtering 🧮

This project implements a **Majority and Minority Selection Algorithm** using **C programming**. The algorithm filters and manipulates values by identifying majority and minority elements, where the minority values are replaced with the average of the majority values. The algorithm can also detect outliers and allows customization of the threshold for defining majority-minority groups.

## Features
- **Manual Input**: Users can manually input each element into the algorithm.
- **Majority and Minority Detection**: The algorithm identifies majority and minority values based on a user-defined threshold.
- **Outlier Detection**: The algorithm detects outliers in the dataset and classifies them as minority values.
- **Minority Value Replacement**: Minority values are replaced by the calculated average of the majority values.
- **Makefile for Automation**: Compiling and running the program is automated using a **Makefile** with bash scripting.

## How It Works

1. **Input**: Users provide a series of numbers manually, along with a threshold to define how much difference constitutes an outlier.
2. **Majority and Minority Detection**: The algorithm sorts the input data and identifies majority and minority values based on the threshold.
3. **Outlier Handling**: Outliers are classified as minority values, and their positions in the data array are stored.
4. **Minority Value Manipulation**: The minority values are replaced by the calculated average of the majority values.
5. **Output**: The manipulated array of values is printed out, along with the majority and minority values, their positions, and the final average of the filtered data.

### Input
- **Enter** the number of elements: 5
- **Insert** the element: 1
- **Insert** the element: 1
- **Insert** the element: 1
- **Insert** the element: 2
- **Insert** the element: 3
- **Insert** the threshold value: 1

### Output
- **Raw Data**: 1 1 1 2 3
- **Majority**: 1 1 1 
- **Minority**: 2 3 
- **List Majority**: 0 1 2 
- **List Minority**: 3 4 
- **The whole data after manipulated**: 1 1 1 1 1 
- **Final average data**: 1.00
- **Final filtered value (mode filter)**: 1.00


# Huffman-File-Compression
File compression tool using Huffman Coding in C++.

## 📌 Project Description
This project implements a file compression technique using Huffman Coding. 
It reduces the size of text data by assigning shorter binary codes to frequently 
occurring characters and longer codes to less frequent ones.

## 🛠 Technologies Used
- C++
- File Handling
- Data Structures (Trees, Priority Queue)
- Git & GitHub

## ⚙️ How It Works
1. Reads input text from a file
2. Calculates frequency of each character
3. Builds a Huffman Tree
4. Generates binary codes for characters
5. Compresses the input text into a binary string

## 📊 Example
- Original size: 33 bytes (264 bits)
- Compressed size (logical): 112 bits
- Compressed size (stored as text): 112 bytes

> Note: Logical compression is achieved. Storing bits as characters increases file size.

## 🚀 Future Improvements
- Store compressed data in binary format (.bin)
- Implement decompression
- Improve compression ratio for large files



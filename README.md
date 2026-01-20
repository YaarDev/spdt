# Structured Programming and Defensive Technologies (SPDT)
## Semester 2 – University Student & Event Management System

This repository contains a **C program** developed as part of the **Semester 2 (Sem 2)** coursework for the subject  
**Structured Programming and Defensive Technologies (SPDT)**.

The program implements a **University Student & Event Management System** that demonstrates core concepts of structured programming, data organization, and defensive coding practices in C.

---

## 📌 Problem Overview

The university requires a software system to manage:
- Student details
- Event participation
- Performance tracking
- Result computation and ranking

All functionality is implemented within a **single, menu-driven C program**.

---

## 🧩 Features Implemented

### 1️⃣ Student Registration
Each student record includes:
- Roll Number
- Name
- Age
- Contact Information (Phone & Email)

Students can participate in **multiple events** such as:
- Cultural
- Sports
- Technical

---

### 2️⃣ Event Management
For each event, the system stores:
- Event Name
- Event Type
- Maximum Marks
- Score obtained by participating students

---

### 3️⃣ Performance Recording
- Tracks marks obtained by each student per event
- Ensures **only one score type per event**
  - Sports score **OR**
  - Cultural/Technical score

---

### 4️⃣ Core Operations
The system supports:
- Adding new students
- Adding event details
- Computing:
  - Total marks
  - Average marks
  - Grade for each student
- Ranking students based on total marks
- Searching a student by roll number
- Displaying a **leaderboard** with:
  - Student name
  - Total marks
  - Grade

---

### 5️⃣ String Operations
The program performs string operations on:
- Student names
- Event names

Including:
- Concatenation
- Reversal
- Comparison

---

### 6️⃣ Structured & Defensive Programming Concepts
The design demonstrates:
- Efficient data organization using `struct`
- Use of `typedef` for clarity
- Use of `enum` for event types
- Use of `union` where mutually exclusive scores are required
- Input validation and defensive checks
- Clear separation of logic using functions

---

## 🛠️ Technologies Used
- Language: **C**
- Compiler: `gcc`
- Platform: macOS / Linux / Windows (terminal-based)

---

## ▶️ How to Compile and Run

```bash
gcc src/01_hello-world.c -o spdt_program
./spdt_program

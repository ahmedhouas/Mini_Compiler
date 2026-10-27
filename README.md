# Mini Compiler

## 📖 Overview

This repository contains a **Mini Compiler** project developed for educational purposes as part of compiler design and construction studies.

The project explores the fundamental stages of compilation, including lexical analysis, syntax analysis, and parsing. It provides practical experience with compiler construction tools and the implementation of language rules.

## 🎯 Objectives

- Understand the fundamental principles of compiler design.
- Implement a lexical analyser using **Flex**.
- Define grammar rules and build a parser using **Bison**.
- Recognise tokens and validate the syntax of source code.
- Detect and report lexical and syntax errors.
- Practise the implementation of programming language grammars.

## ⚙️ Technologies

- **C** — Implementation of compiler components.
- **Flex** — Lexical analysis and token recognition.
- **Bison** — Grammar definition and syntax analysis.
- **Linux** — Development and execution environment.
- **GCC** — Compilation of C source files.

## 🔄 Compilation Process

The compiler follows the main stages of a traditional compilation process:

1. **Lexical Analysis:** Reads the source code and identifies tokens such as keywords, identifiers, operators, and constants.
2. **Syntax Analysis:** Checks whether the sequence of tokens follows the grammar rules of the language.
3. **Error Detection:** Identifies invalid tokens and syntax errors and reports them to the user.

Additional stages depend on the features implemented in the project.

## 📂 Repository Structure

```text
Mini_Compiler/
├── README.md
├── lexer.l          # Flex rules, if applicable
├── parser.y         # Bison grammar, if applicable
├── *.c              # C source files
├── *.h              # Header files, if applicable
└── test_cases/      # Input examples, if included
```

*Note: This is an illustrative structure. Actual filenames and directories may differ.*

## 🛠️ Prerequisites

On Ubuntu or another Debian-based Linux distribution, install the required tools:

```bash
sudo apt update
sudo apt install gcc flex bison make
```

Verify the installations:

```bash
gcc --version
flex --version
bison --version
```

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/ahmedhouas/Mini_Compiler.git
```

### 2. Enter the project directory

```bash
cd Mini_Compiler
```

### 3. Build the compiler

If the repository contains a `Makefile`, follow the build instructions defined in it. Otherwise, adapt the following commands to the actual names of your Flex and Bison files:

```bash
bison -d parser.y
flex lexer.l
gcc -o mini_compiler parser.tab.c lex.yy.c -lfl
```

### 4. Run the compiler

```bash
./mini_compiler
```

Provide source code using the input method implemented by the project, such as standard input or a source file.

**Important:** The build commands above assume the files are named `parser.y` and `lexer.l`, and that the generated parser and lexer can be compiled together. Adjust the commands if your project uses different filenames or additional source files.

## 🧪 Testing

Use the available test cases to verify that the compiler correctly handles valid and invalid input.

Suggested test categories include:

- Valid expressions and statements.
- Correctly formed programs.
- Invalid tokens.
- Syntax errors.
- Grammar edge cases.

## 🎓 Academic Context

- **Project:** Mini Compiler
- **Subject:** Compiler Design and Construction
- **Purpose:** Educational project and practical exploration of compiler implementation.

## 👤 Author

Ahmed Houas

## 📄 License

This project is intended for educational purposes. No specific open-source licence is declared here; check the repository for licensing information before redistributing the code.

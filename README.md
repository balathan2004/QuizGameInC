
# Quiz Application in C

This is a simple command-line quiz application written in C that loads questions from a JSON file. The user can answer multiple-choice questions, and the program calculates their score at the end.

## Features

- Loads questions and options from a JSON file.
- Provides a quiz with multiple-choice options.
- Calculates the user's score based on correct answers.
- Validates user input to ensure correct answer choices.

---

## How to Use

### Prerequisites

- **C Compiler**: Ensure you have a C compiler like `gcc` installed.
- **cJSON Library**: This application uses the `cJSON` library for JSON parsing. You must install the `cJSON` library before compiling the code. You can download it from [https://github.com/DaveGamble/cJSON](https://github.com/DaveGamble/cJSON) or install it using your system's package manager.

  **For Linux (Ubuntu/Debian)**:
  ```bash
  sudo apt-get install libcjson-dev
  ```

  **For macOS (using Homebrew)**:
  ```bash
  brew install cjson
  ```

### Compilation & Execution

This project includes a `Makefile` to simplify the compilation and execution process.

1. Clone the repository or copy the C source file to your local machine.
2. Ensure the `cJSON` library is correctly linked to your project.

### Build the Project

To compile the project, simply run the following command in the terminal:

```bash
make
```

This will compile the source code and output the executable file into the `./build/out` directory.

### Run the Program

After building the project, execute the program with:

```bash
./build/out
```

---

## JSON File Format

The application expects the questions to be stored in a **strict format** in a JSON file named `data.json`. The format must strictly follow the structure shown below:

#### Example of `data.json`:

```json
{
  "questions": [
    {
      "qno": 1,
      "question": "What is the capital of France?",
      "options": ["Berlin", "Madrid", "Paris", "Rome"],
      "answer": 3
    },
    {
      "qno": 2,
      "question": "Which planet is known as the Red Planet?",
      "options": ["Earth", "Mars", "Venus", "Jupiter"],
      "answer": 2
    },
    {
      "qno": 3,
      "question": "Who is the current president of the United States?",
      "options": ["Joe Biden", "Donald Trump", "Barack Obama", "George Bush"],
      "answer": 1
    }
  ]
}
```

### Key Points:
- **"qno"**: The question number (integer).
- **"question"**: The actual question (string).
- **"options"**: An array of 4 strings representing the multiple-choice options.
- **"answer"**: The correct answer (integer, representing the index of the correct option starting from 1).

### Important Notes:

- Ensure that the `data.json` file follows the exact structure as shown above for proper parsing.
- If the file is missing or improperly formatted, the application will fail to load questions and will print an error message.

---

## License

This project is open-source and available under the MIT License.

---

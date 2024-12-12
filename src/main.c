#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *question;
  char options[4][50];
  int qno;
  int answer;
} Question;

Question AllQuestions[100];

int count;

void PrintQuestion(Question *ques, int *marks) {

  int UserAnswer;

  printf("\n\n\n%d.%s?\n", ques->qno, ques->question);
  printf("Options:\n");
  for (int i = 0; i < 4; i++) {
    printf("%d.%s\t", i + 1, ques->options[i]);
  }

  printf("\nEnter Your Answer: ");

  if (scanf("%d", &UserAnswer) != 1 || UserAnswer < 1 || UserAnswer > 4) {
    printf("Invalid input. Please enter a number between 1 and 4.\n");
    // Clear input buffer in case of invalid input
    while (getchar() != '\n')
      ;
    return;
  }

  if (UserAnswer == ques->answer) {
    printf("You answered right\n");
    (*marks)++;
  } else {
    printf("wrong answer\n");
  }
}

char *readFile() {

  FILE *file = fopen("data.json", "r");

  if (file == NULL) {
  perror("Error opening file");
  exit(EXIT_FAILURE);
}
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = (char *)malloc(length + 1);

  if (content == NULL) {
    printf("Memory allocation failed.\n");
    fclose(file);
    free(content);
    return NULL;
  }
  if (fread(content, 1, length, file) != length) {
    printf("Error reading file.\n");
    fclose(file);
    free(content);
    return NULL;
  }

  content[length] = '\0';
  fclose(file);
  return content;
}

void parser() {

  char *data = readFile();
  cJSON *jsonData = cJSON_Parse(data);
  if (jsonData == NULL) {
  printf("Error parsing JSON.\n");
  exit(EXIT_FAILURE);
}
  free(data);

  cJSON *questions = cJSON_GetObjectItem(jsonData, "questions");

  if (cJSON_IsArray(questions)) {
    int len = cJSON_GetArraySize(questions);
    for (int i = 0; i < len; i++) {
      cJSON *questionObject = cJSON_GetArrayItem(questions, i);

      char *question =
          (cJSON_GetObjectItem(questionObject, "question"))->valuestring;
      int questionNo =
          (cJSON_GetObjectItem(questionObject, "qno"))->valuedouble;
      int answer = (cJSON_GetObjectItem(questionObject, "answer"))->valuedouble;
      cJSON *optionsArray = cJSON_GetObjectItem(questionObject, "options");

      AllQuestions[count].question = strdup(question);

      AllQuestions[count].answer = answer;
      AllQuestions[count].qno = questionNo;

      if (cJSON_IsArray(optionsArray)) {

        int arraySize = cJSON_GetArraySize(optionsArray);

        for (int j = 0; j < arraySize; j++) {
          cJSON *singleOption = (cJSON_GetArrayItem(optionsArray, j));
          char *optionString = singleOption->valuestring;

          strncpy(AllQuestions[count].options[j], optionString,
                  sizeof(AllQuestions[count].options[j]) - 1);
          AllQuestions[count]
              .options[j][sizeof(AllQuestions[count].options[j]) - 1] = '\0';
        }
        count++;
      }
    }
  }
  cJSON_Delete(jsonData);
}

void QuizHandler() {
  parser();

  if (count <= 0) {
    printf("No questions available. Exiting.\n");
    return; // Exit the function if there are no questions
  }
  int cursor = 0;
  int marks = 0;

  printf("Hello World\n");

  do {
    PrintQuestion(&AllQuestions[cursor], &marks);
    cursor++;

  } while (cursor < count);

  for (int i = 0; i < count; i++) {
    free(AllQuestions[i].question);
  }
  printf("\n  your marks =%d/%d", marks, count);
}

int main() {

  QuizHandler();

  return 0;
}

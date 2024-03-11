#include <iostream>
#include <string.h>
#include <sys/types.h>

class InputBuffer
{
    public:
        char* buffer;
        size_t buffer_length;

    InputBuffer() : buffer(nullptr), buffer_length(0) {}

    ~InputBuffer()
    {
        delete[] buffer;
    }
};

void print_prompt()
{
    std::cout << "wind_db > ";
}

void read_input(InputBuffer& input_buffer)
{
    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cerr << "Error reading input" << std::endl;
        exit(EXIT_FAILURE);
    }

    input_buffer.buffer_length = input.length();
    input_buffer.buffer = new char[input_buffer.buffer_length];
    strcpy(input_buffer.buffer, input.c_str());
}

enum PrepareResult
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
};

enum MetaCommandResult
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};

enum StatementType
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
};

class Statement
{
    public:
        StatementType type;
};

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      printf("This is where we would do an insert.\n");
      break;
    case (STATEMENT_SELECT):
      printf("This is where we would do a select.\n");
      break;
  }
}

MetaCommandResult do_meta_command(InputBuffer& input_buffer)
{
  if (strcmp(input_buffer.buffer, "_exit") == 0)
    {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

int main(int argc, char* argv[])
{
    InputBuffer* input_buffer = new InputBuffer();

    while(true)
    {
        print_prompt();
        read_input(*input_buffer);

        if (input_buffer->buffer[0] == '_')
        {
            switch (do_meta_command(*input_buffer))
            {
                case (META_COMMAND_SUCCESS):
                   continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                   printf("Unrecognized command '%s'\n", input_buffer->buffer);
                   continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
        }

    return 0;
}

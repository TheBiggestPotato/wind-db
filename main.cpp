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
    }

    return 0;
}

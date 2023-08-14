
const int MAX_NUMBER_LOW_VALUE = 1;
const int MAX_NUMBER_HI_VALUE = 32767;
const int DEFAULT_MAX_NUMBER = 100;
const int MAX_NUMBER_LEVEL1 = 10;
const int MAX_NUMBER_LEVEL2 = 50;
const int MAX_NUMBER_LEVEL3 = 100;

bool parse_args(int argc, const char **argv, bool &show_table_arg,
                int &max_number_arg);

void print_help();
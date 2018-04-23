void verify_word(char *word);

void control_memory(size_t size);

struct SymbolTables
{
    char *token;
    char *type;
    char *value;
    char *scope;
};

struct SymbolTables *SymbolTable;

extern const char *reserved_words[];

extern char *file_array;

extern int char_index;

extern int char_count;

extern char *scope;

extern int line_index;
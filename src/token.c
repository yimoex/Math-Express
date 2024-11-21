typedef struct {
    int ptr;
    int max;
    const char* text;
} Token;

Token* token_create(const char* text, int max){
    Token* token = (Token *)malloc(sizeof(Token));
    token -> text = text;
    token -> ptr = 0;
    token -> max = max;
    return token;
}

char token_read(Token* token){
    if(token -> ptr == token -> max) return -1;
    char ch = token -> text[token -> ptr];
    token -> ptr++;
    return ch;
}


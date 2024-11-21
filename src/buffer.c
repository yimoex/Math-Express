#define BUFFER_MAX_SIZE 4096

typedef struct {
    unsigned long size;
    unsigned long realsize;
    char* data;
} Buffer;

Buffer* buffer_create(){
    Buffer* buf = (Buffer *)malloc(sizeof(Buffer));
    buf -> size = BUFFER_MAX_SIZE;
    buf -> realsize = 0;
    buf -> data = (char *)malloc(sizeof(char) * BUFFER_MAX_SIZE);
    memset(buf -> data, '\0', BUFFER_MAX_SIZE);
    return buf;
}

Buffer* buffer_add_char(Buffer* buf, char ch){
    buf -> data[buf -> realsize] = ch;
    buf -> realsize++;
    return buf;
}

int buffer_empty(Buffer* buf){
    return buf -> realsize == 0;
}

Buffer* buffer_clear(Buffer* buf){
    buf -> realsize = 0;
    memset(buf -> data, '\0', BUFFER_MAX_SIZE);
    return buf;
}

Buffer* buffer_export(Buffer* buf, char* tmp){
    strncpy(tmp, buf -> data, buf -> realsize);
    return buf;
}

int buffer2int(Buffer* buf){
    return atoi(buf -> data);
}


#ifndef MYHEADER

typedef struct {
  int flag, readerCount;
} buffer;

int buf_init(buffer *b);
int changeFlag(buffer *b);
int incrementReader(buffer *b);
int decrementReader(buffer *b);
int getFlag(buffer *b);
int getReaderCount(buffer *b);

#endif // !MYHEADER

int buf_init(buffer *b) {
  b->flag = 1;
  b->readerCount = 0;
  return 1;
}

int changeFlag(buffer *b) {
  b->flag = 0;
  return 1;
}

int incrementReader(buffer *b) {
  b->readerCount++;
}

int decrementReader(buffer *b) {
  b->readerCount--;
}

int getFlag(buffer *b) {
  return b->flag;
}

int getReaderCount(buffer *b) {
  return b->readerCount;
}


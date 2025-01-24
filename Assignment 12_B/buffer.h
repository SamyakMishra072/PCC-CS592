#ifndef MYHEADER

#include <stdbool.h>

typedef struct {
  bool flag, finish;
} buffer;

void buf_init(buffer *b);
bool getFlag(buffer *b);
void changeFlag(buffer *b);
void finished(buffer *b);
bool getFinish(buffer *b);

#endif // !MYHEADER

void buf_init(buffer *b) {
  b->flag = true;
  b->finish = false;
  return;
}

bool getFlag(buffer *b) {
  return b->flag;
}

void changeFlag(buffer *b) {
  b->flag = !(b->flag);
  return;
}

void finished(buffer *b) {
  b->finish = true;
  return;
}

bool getFinish(buffer *b) {
  return b->finish;
}

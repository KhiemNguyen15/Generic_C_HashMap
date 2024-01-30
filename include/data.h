#ifndef DATA_H
#define DATA_H

typedef struct Data Data;

struct Data {
  void *val;
};

Data createData(void *val);
void *getData(Data data);

#endif

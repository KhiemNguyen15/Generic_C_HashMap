#include <stdlib.h>

#include "data.h"

Data createData(void *val)
{
    Data *data = (Data *)malloc(sizeof(Data));
    data->val = val;

    return *data;
}

void *getData(Data data)
{
    return data.val;
}
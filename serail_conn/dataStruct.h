#ifndef DATASTRUCT_H
#define DATASTRUCT_H
struct Data {
    int id;
    float temp1;
    float temp2;
};
union U_data {
    Data d;
    char b[12];
};
Data sdata;
U_data udata;
#endif // DATASTRUCT_H

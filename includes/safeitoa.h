#ifndef SAFEITOA_H
#define SAFEITOA_H

 char *safeitoa(const int x, char *buffer, const int bufferSize, const int radix);

 int twosNegation(const int x, const int radix);

 int negateBuffer(char *buffer, const int bufferSize, const int strlen, const int radix);

 void safestrrev(char *buffer, const int bufferSize, const int strlen);

#endif 


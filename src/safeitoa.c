#include <stdio.h>
#include <string.h>
#include "../includes/safeitoa.h"

//copiado desta resposta https://stackoverflow.com/a/16042640

static char _numberSystem[] = "0123456789ABCDEF";
static char _twosComp[] = "FEDCBA9876543210";

 void safestrrev(char *buffer, const int bufferSize, const int strlen)
{
    int len = strlen;
    if (len > bufferSize)
    {
        len = bufferSize;
    }
    for (int index = 0; index < (len / 2); index++)
    {
        char ch = buffer[index];
        buffer[index] = buffer[len - index - 1];
        buffer[len - index - 1] = ch;
    }
}

 int negateBuffer(char *buffer, const int bufferSize, const int strlen, const int radix)
{
    int len = strlen;
    if (len > bufferSize)
    {
        len = bufferSize;
    }
    if (radix == 10)
    {
        if (len < (bufferSize - 1))
        {
            buffer[len++] = '-';
            buffer[len] = '\0';
        }
    }
    else
    {
        int twosCompIndex = 0;
        for (int index = 0; index < len; index++)
        {
            if ((buffer[index] >= '0') && (buffer[index] <= '9'))
            {
                twosCompIndex = buffer[index] - '0';
            }
            else if ((buffer[index] >= 'A') && (buffer[index] <= 'F'))
            {
                twosCompIndex = buffer[index] - 'A' + 10;
            }
            else if ((buffer[index] >= 'a') && (buffer[index] <= 'f'))
            {
                twosCompIndex = buffer[index] - 'a' + 10;
            }
            twosCompIndex += (16 - radix);
            buffer[index] = _twosComp[twosCompIndex];
        }
        if (len < (bufferSize - 1))
        {
            buffer[len++] = _numberSystem[radix - 1];
            buffer[len] = 0;
        }
    }
    return len;
}

 int twosNegation(const int x, const int radix)
{
    int n = x;
    if (x < 0)
    {
        if (radix == 10)
        {
            n = -x;
        }
        else
        {
            n = ~x;
        }
    }
    return n;
}

 char *safeitoa(const int x, char *buffer, const int bufferSize, const int radix)
{
    int strlen = 0;
    int n = twosNegation(x, radix);
    int nuberSystemIndex = 0;

    if (radix <= 16)
    {
        do
        {
            if (strlen < (bufferSize - 1))
            {
                nuberSystemIndex = (n % radix);
                buffer[strlen++] = _numberSystem[nuberSystemIndex];
                buffer[strlen] = '\0';
                n = n / radix;
            }
            else
            {
                break;
            }
        } while (n != 0);
        if (x < 0)
        {
            strlen = negateBuffer(buffer, bufferSize, strlen, radix);
        }
        safestrrev(buffer, bufferSize, strlen);
        return buffer;
    }
    return NULL;
}
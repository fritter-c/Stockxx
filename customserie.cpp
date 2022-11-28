#include "customserie.h"

CustomSerie::CustomSerie()
{

}

bool CustomSerie::Next()
{
    return false;
}

bool CustomSerie::Prior()
{
    return false;
}

bool CustomSerie::PriorAll()
{
    return false;
}

bool CustomSerie::NextAll()
{
    return false;
}

bool CustomSerie::PriorN(size_t N)
{
    return false;
}

bool CustomSerie::NextN(size_t N)
{
    return false;
}

size_t CustomSerie::Size()
{
    return 0;
}

double CustomSerie::Open()
{
    return INVALID_DOUBLE;
}

double CustomSerie::Close()
{
    return INVALID_DOUBLE;
}

QDateTime CustomSerie::Date()
{
    return ZERO_DATE;
}

double CustomSerie::High()
{
    return INVALID_DOUBLE;
}

double CustomSerie::Low()
{
    return INVALID_DOUBLE;
}

double CustomSerie::Volume()
{
    return INVALID_DOUBLE;
}

QuoteIdentifier CustomSerie::Quote()
{
    return INVALID_QUOTE;
}

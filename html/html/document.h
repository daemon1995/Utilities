#pragma once
#include "litehtml/document_container.h"
using namespace litehtml;
class Document :
    public document_container
{
    int refCount;
public:
    Document(int cnt = 0);
};


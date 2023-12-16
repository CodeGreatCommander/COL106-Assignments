/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
SymEntry::SymEntry():key(""),left(nullptr),right(nullptr),val(nullptr){}
SymEntry::SymEntry(string key,UnlimitedRational* q):key(key),val(q),left(nullptr),right(nullptr){}
SymEntry::~SymEntry(){}


#ifndef SAFE_STRING_H
#define SAFE_STRING_H

typedef void String;

String* string_create(const char* cstr);
char*   string_as_c_str(String* string);
void    string_destroy();


#endif


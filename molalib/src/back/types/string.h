#pragma once

#include "../../util.h"
#include "../../front/api.h"

/*

len()                           length (without NULL character)
set(pos, char)
clear()
empty()
reverse()
prepend(str)
append(str)
delpref(count)
delsuf(count)
copy()
substr(index, count)
array()
split(sep)
startswith(str)
endswith(str)
splitlines()
join(arr)
replace(str, str)
comb(str)

*/

typedef struct StringValue {
    size_t length;
    char  *string;    // NULL terminated, length doesnt count the NULL character

    uint32_t ref_count;
    uint32_t gc_mark         : 1;
    uint32_t is_gc_protected : 1;
} StringValue;

#define get_string(obj) ((StringValue *)((obj)->value))

StringValue   *stringValueCreate(size_t length, char *string);
StringValue   *stringValueCopy(StringValue *val);
void           stringValueDestroy(StringValue *val);
void           stringValueGCOnlyUnref(StringValue *val);
void           stringValueGCDestroy(StringValue *val);
char           stringValueIndexAccess(StringValue *val, int64_t index);
struct Object *stringValueLookupField(StringValue *val, ident name);
struct Object *stringValueLookupMethod(StringValue *val, ident name);
int            stringCompare(StringValue *first, StringValue *second);    // like strcmp
StringValue   *stringConcat(StringValue *first, StringValue *second);
void           stringValueRef(StringValue *unit);
void           stringValueUnref(StringValue *unit);

void init_string();

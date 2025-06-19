#include "string.h"
#include "../api.h"

StringValue *stringValueCreate(size_t length, char *string) {
    stat_created_strings++;
    StringValue *res = allocOrError(sizeof(StringValue));
    res->length      = length;
    res->string      = allocOrError(sizeof(char) * length + 1);
    strcpy(res->string, string);

    res->gc_mark         = gc_mark;
    res->ref_count       = 0;
    res->is_gc_protected = 0;

    gcTrackStringValue(res);

    return res;
}

StringValue *stringValueCopy(StringValue *val) {
    return stringValueCreate(val->length, val->string);
}

void stringValueDestroy(StringValue *val) {
    stat_created_strings--;
    freeBytes(val->string);
    freeBytes(val);
    gcUntrackStringValue(val);
}

void stringValueGCOnlyUnref(StringValue *val) {}

void stringValueGCDestroy(StringValue *val) {
    stat_created_strings--;
    freeBytes(val->string);
    freeBytes(val);
    gcUntrackStringValue(val);
}

char stringValueIndexAccess(StringValue *val, int64_t index) {
    if (!(0 <= index && index < val->length)) {
        signalError(OUT_OF_BOUNDS_ERROR_CODE, "Index out of bounds");
    }
    return val->string[index];
}

struct Object *stringValueLookupField(StringValue *val, ident name) {}

struct Object *stringValueLookupMethod(StringValue *val, ident name) {}

int stringCompare(StringValue *first, StringValue *second) {
    size_t m = (first->length < second->length) ? first->length : second->length;
    for (size_t i = 0; i < m; i++) {
        if (first->string[i] < second->string[i]) {
            return -1;
        }
        else if (first->string[i] > second->string[i]) {
            return 1;
        }
    }
    if (first->length < second->length) {
        return -1;
    }
    else if (first->length > second->length) {
        return 1;
    }
    return 0;
}

StringValue *stringConcat(StringValue *first, StringValue *second) {
    char *str = allocOrError(first->length + second->length + 1);
    memcpy(str, first->string, first->length);
    memcpy(str + first->length, second->string, second->length);
    str[first->length + second->length] = '\0';

    StringValue *res = stringValueCreate(first->length + second->length, str);
    freeBytes(str);
    return res;
}

void stringValueRef(StringValue *unit) {
    unit->ref_count++;
}

void stringValueUnref(StringValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageStringValue(unit);
    }
}

void init_string() {}

/* created by Boris Timofeenko, 2017 */
#include <mem.h>
#include "linear_sequence.h"
#define TOITER(x) ((LSQ_Iterator*)(x))
#define TOSEQUENCE(x) ((LSQ*)(x))

typedef struct {
    LSQ_BaseTypeT *head;
    LSQ_IntegerIndexT size;
} LSQ;

typedef struct {
    LSQ_IntegerIndexT i;
    LSQ *handle;
} LSQ_Iterator;

LSQ_HandleT LSQ_CreateSequence(void){
    LSQ *seq = malloc(sizeof(LSQ));
    seq->head = NULL;
    seq->size = 0;
    return ((LSQ_HandleT)seq);
}

void LSQ_DestroySequence(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid) return;
    free((TOSEQUENCE(handle))->head);
    free(TOSEQUENCE(handle));
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle){
    return (handle != LSQ_HandleInvalid ? (TOSEQUENCE(handle))->size : 0);
}

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator){
    return ((iterator != NULL) && (TOITER(iterator)->i >= 0) && (TOITER(iterator)->i < TOITER(iterator)->handle->size));
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator){
    return ((iterator != NULL) && (TOITER(iterator)->i >= TOITER(iterator)->handle->size));
}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator){
    return ((iterator != NULL) && (TOITER(iterator)->i < 0));
}

LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator){
    if (iterator == NULL) return NULL;
    return (TOITER(iterator)->handle->head + TOITER(iterator)->i);
}

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index){
    if (handle == LSQ_HandleInvalid) return (NULL);
    LSQ_Iterator *iter = malloc(sizeof(LSQ_Iterator));
    iter->i = index;
    iter->handle = TOSEQUENCE(handle);
    return ((LSQ_IteratorT)iter);
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid) return (LSQ_HandleInvalid);
    LSQ_Iterator *iter = malloc(sizeof(LSQ_Iterator));
    iter->i = 0;
    iter->handle = TOSEQUENCE(handle);
    return ((LSQ_IteratorT)iter);
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle){
    if (handle == LSQ_HandleInvalid) return (LSQ_HandleInvalid);
    LSQ_Iterator *iter = malloc(sizeof(LSQ_Iterator));
    iter->i = TOSEQUENCE(handle)->size;
    iter->handle = TOSEQUENCE(handle);
    return ((LSQ_IteratorT)iter);
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator){
    free(TOITER(iterator));
}

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator){
    if (TOITER(iterator) == NULL) return;
    TOITER(iterator)->i++;
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator){
    if (TOITER(iterator) == NULL) return;
    TOITER(iterator)->i--;
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift){
    if (TOITER(iterator) == NULL) return;
    TOITER(iterator)->i += shift;
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos){
    if (TOITER(iterator) == NULL) return;
    TOITER(iterator)->i = pos;
}

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if (TOSEQUENCE(handle) == LSQ_HandleInvalid) return;
    TOSEQUENCE(handle)->size++;
    TOSEQUENCE(handle)->head = realloc(TOSEQUENCE(handle)->head,sizeof(LSQ_BaseTypeT)*TOSEQUENCE(handle)->size);
    memmove(TOSEQUENCE(handle)->head+1,TOSEQUENCE(handle)->head,sizeof(LSQ_BaseTypeT)*(TOSEQUENCE(handle)->size - 1));
    *(TOSEQUENCE(handle)->head) = element;
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if (TOSEQUENCE(handle) == LSQ_HandleInvalid) return;
    TOSEQUENCE(handle)->size++;
    TOSEQUENCE(handle)->head = realloc(TOSEQUENCE(handle)->head,sizeof(LSQ_BaseTypeT)*TOSEQUENCE(handle)->size);
    *(TOSEQUENCE(handle)->head + TOSEQUENCE(handle)->size - 1) = element;
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement){
    if (TOITER(iterator) == NULL) return;
    TOITER(iterator)->handle->size++;
    TOITER(iterator)->handle->head = realloc(TOITER(iterator)->handle->head, sizeof(LSQ_BaseTypeT)*TOITER(iterator)->handle->size);
    memmove(TOITER(iterator)->handle->head + TOITER(iterator)->i + 1, TOITER(iterator)->handle->head + TOITER(iterator)->i, sizeof(LSQ_BaseTypeT)*(TOITER(iterator)->handle->size - TOITER(iterator)->i - 1));
    (*(TOITER(iterator)->handle->head + TOITER(iterator)->i)) = newElement;
}

void LSQ_DeleteFrontElement(LSQ_HandleT handle){
    if (TOSEQUENCE(handle) == LSQ_HandleInvalid) return;
    if (TOSEQUENCE(handle)->size == 0) return;
    TOSEQUENCE(handle)->size--;
    TOSEQUENCE(handle)->head++;
}

void LSQ_DeleteRearElement(LSQ_HandleT handle){
    if (TOSEQUENCE(handle) == LSQ_HandleInvalid) return;
    if (TOSEQUENCE(handle)->size == 0) return;
    TOSEQUENCE(handle)->size--;
}

void LSQ_DeleteGivenElement(LSQ_IteratorT iterator){
    if ((TOITER(iterator) == NULL) || (!LSQ_IsIteratorDereferencable(iterator))) return;
    TOITER(iterator)->handle->size--;
    memmove(TOITER(iterator)->handle->head + TOITER(iterator)->i,TOITER(iterator)->handle->head + TOITER(iterator)->i+1,sizeof(LSQ_BaseTypeT)*(TOITER(iterator)->handle->size - TOITER(iterator)->i));
    TOITER(iterator)->handle->head = realloc(TOITER(iterator)->handle->head, sizeof(LSQ_BaseTypeT)*(TOITER(iterator)->handle->size));
}
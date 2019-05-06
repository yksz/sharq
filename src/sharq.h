#ifndef SHARQ_H
#define SHARQ_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

typedef struct {

} Sharq;

int Sharq_init(Sharq* self);
int Sharq_receive(Sharq* self, char* buf, size_t len);
int Sharq_transmit(Sharq* self, const char* buf, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SHARQ_H */

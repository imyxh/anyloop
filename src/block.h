#ifndef _OPENAO_BLOCK_H
#define _OPENAO_BLOCK_H

#include <gsl/gsl_matrix.h>

// due to tda and stride considerations, we cannot simply memcpy() a matrix or
// vector to a gsl_block; this file makes that simpler

// write matrix to continuous block
gsl_block *mat2blk(gsl_matrix *m);

// write vector to continuous block
gsl_block *vec2blk(gsl_vector *v);

#endif

#ifndef CONCAT2
#define CONCAT2_NX(A, B) A ## B
#define CONCAT2(A, B) CONCAT2_NX(A, B)
#endif

#ifndef CONCAT3
#define CONCAT3_NX(A, B, C)	A ## B ## c
#define CONCAT3(A, B, C) 	CONCAT3_NX(A, B, C)
#endif

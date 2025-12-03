#include <stdio.h>
#include "mtest.h"


TEST_CASE(TestConnection,
/* Arrange */
int i = 1;
int j = 1;

/* Act */
int k = i + j;

/* Assert */
CHECK_EQ_INT(k,2);

)






MAIN_RUN_TESTS(TestConnection)
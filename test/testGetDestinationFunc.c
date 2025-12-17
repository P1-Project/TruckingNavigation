#include <stdio.h>
#include "mtest.h"
#include "../src/GetDestinationFunc.h"
#include "DefineStruct.h"
#include "DefineConst.h"
#include "HelperFunc.h"

TEST_CASE(format6,
    /* Arrange */

    /* Act */

    /* Assert */

)

TEST_CASE(IsDestinationInBound,
    /* Arrange */
    Destination destination;


    /* Act */
    GetDestinationRandom(&destination, MAPSIZE);

    /* Assert */
    CHECK_LE_INT(destination.startX, MAPSIZE);
    CHECK_GE_INT(destination.startX, 0);
    CHECK_LE_INT(destination.startY, MAPSIZE);
    CHECK_GE_INT(destination.startY, 0);
    CHECK_LE_INT(destination.endX, MAPSIZE);
    CHECK_GE_INT(destination.endX, 0);
    CHECK_LE_INT(destination.endY, MAPSIZE);
    CHECK_GE_INT(destination.endY, 0);


)
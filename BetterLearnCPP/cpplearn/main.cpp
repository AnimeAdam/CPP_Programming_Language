#include "Headers/IncludesAll.h"
#include "Headers/Defines.h"
#include "Headers/Chapter2/SimpleVector.h"
#include "Headers/Chapter3/OperatorOverloading.h"
#include "Headers/Chapter3/AbstractContainer.h"
#include "Headers/Chapter3/BetterVector.h"
#include "Headers/Chapter3/CopyingAndMoving.h"
#include "Headers/Chapter3/Templates.h"
#include "Headers/Chapter4/Strings.h"
#include "Headers/Chapter4/IOstream.h"
#include "Headers/Chapter4/Containers.h"
#include "Headers/Chapter5/ResourceManagement.h"
#include "Headers/Chapter5/Task_Threads.h"
#include "Headers/Chapter5/SmallUtilityComponents.h"
#include "Headers/Chapter6/Types.h"
#include "Headers/Chapter7/Pointers.h"
#include "Headers/Chapter8/Structures.h"
#include "Headers/Chapter8/Unions.h"
#include "Headers/Chapter8/Enums.h"
#include "Headers/Chapter13/ErrorHandling.h"

//region Main

//TODO pg. 467


int g(int j ...)
{
    j = j + j;
    return j;
}

int main() {
    std::cout << "Hello, World! " << std::endl;
    

    return 0;
}

//endregion
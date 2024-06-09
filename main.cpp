#include "solution.h"

int main(){
    Problem p = getInstance(PNe150, 0);
    Solution s = Solution(p);

    s.setSolutionQuality(p);

    return 0;
}

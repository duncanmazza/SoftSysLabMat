/* Run all tests
 *
 * Duncan and Anna SoftSys Project 1
 */

#include "test_all.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

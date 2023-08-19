#ifdef _MSC_VER
#define _SCL_SECURE_NO_WARNINGS
#endif

#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <srtdbg.h>
#endif

#include "vector_test.h"
#include "deque_test.h"
#include "stack_test.h"
#include "queue_test.h"
#include "list_test.h"
#include "set_test.h"
#include "map_test.h"
#include "unordered_set_test.h"
#include "unordered_map_test.h"
#include "string_test.h"

int main()
{
    using namespace mystl::test;

    std::cout.sync_with_stdio(false);

    vector_test::vector_test();
    deque_test::deque_test();
    stack_test::stack_test();
    queue_test::queue_test();
    queue_test::priority_test();
    list_test::list_test();
    set_test::set_test();
    set_test::multiset_test();
    map_test::map_test();
    map_test::multimap_test();
    unordered_set_test::unordered_set_test();
    unordered_set_test::unordered_multiset_test();
    unordered_map_test::unordered_map_test();
    unordered_map_test::unordered_multimap_test();
    string_test::string_test();
}
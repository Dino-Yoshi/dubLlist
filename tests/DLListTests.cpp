#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#define private public
#include "../DLList.cpp"
#undef private

#include <vector>

template <typename T>
std::vector<T> ForwardValues(DLList<T>& list) {
    std::vector<T> values;
    typename DLList<T>::Node* current = list.head;
    int guard = 0;
    while (current != nullptr && guard < 100) {
        values.push_back(current->data);
        current = current->next;
        ++guard;
    }
    return values;
}

template <typename T>
std::vector<T> BackwardValues(DLList<T>& list) {
    std::vector<T> values;
    typename DLList<T>::Node* current = list.tail;
    int guard = 0;
    while (current != nullptr && guard < 100) {
        values.push_back(current->data);
        current = current->prev;
        ++guard;
    }
    return values;
}

template <typename T>
void RequireOrder(DLList<T>& list, const std::vector<T>& forward, const std::vector<T>& backward) {
    REQUIRE(ForwardValues(list) == forward);
    REQUIRE(BackwardValues(list) == backward);
    REQUIRE(list.numNodes == static_cast<int>(forward.size()));
}

TEST_CASE("Empty returns true for a new list", "[Empty]") {
    DLList<int> list;
    INFO("input: newly constructed list; expected output: Empty() == true");
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Empty returns false after PushFront", "[Empty]") {
    DLList<int> list;
    list.PushFront(10);
    INFO("input: [10]; expected output: Empty() == false");
    REQUIRE(list.Empty() == false);
}

TEST_CASE("Empty returns false after PushBack", "[Empty]") {
    DLList<int> list;
    list.PushBack(20);
    INFO("input: [20]; expected output: Empty() == false");
    REQUIRE(list.Empty() == false);
}

TEST_CASE("Empty returns true after removing the only element", "[Empty]") {
    DLList<int> list;
    list.PushBack(30);
    list.PopBack();
    INFO("input: [30] then PopBack(); expected output: Empty() == true");
    REQUIRE(list.Empty() == true);
}

TEST_CASE("PushFront inserts into an empty list", "[PushFront]") {
    DLList<int> list;
    INFO("input: PushFront(4); expected order: [4]");
    REQUIRE(list.PushFront(4) == true);
    RequireOrder(list, {4}, {4});
    REQUIRE(list.head == list.tail);
}

TEST_CASE("PushFront prepends before an existing element", "[PushFront]") {
    DLList<int> list;
    list.PushFront(4);
    INFO("input: [4], PushFront(2); expected order: [2, 4]");
    REQUIRE(list.PushFront(2) == true);
    RequireOrder(list, {2, 4}, {4, 2});
}

TEST_CASE("PushFront preserves insertion order across several prepends", "[PushFront]") {
    DLList<int> list;
    list.PushFront(3);
    list.PushFront(2);
    list.PushFront(1);
    INFO("input: PushFront(3), PushFront(2), PushFront(1); expected order: [1, 2, 3]");
    RequireOrder(list, {1, 2, 3}, {3, 2, 1});
}

TEST_CASE("PushFront keeps the old tail unchanged", "[PushFront]") {
    DLList<int> list;
    list.PushBack(8);
    list.PushFront(6);
    INFO("input: [8], PushFront(6); expected TopBack() == 8");
    REQUIRE(list.TopBack() == 8);
}

TEST_CASE("PushFront sets the new head prev pointer to null", "[PushFront]") {
    DLList<int> list;
    list.PushBack(2);
    list.PushFront(1);
    INFO("input: [2], PushFront(1); expected head->prev == nullptr");
    REQUIRE(list.head->prev == nullptr);
}

TEST_CASE("PushBack inserts into an empty list", "[PushBack]") {
    DLList<int> list;
    INFO("input: PushBack(4); expected order: [4]");
    REQUIRE(list.PushBack(4) == true);
    RequireOrder(list, {4}, {4});
    REQUIRE(list.head == list.tail);
}

TEST_CASE("PushBack appends after an existing element", "[PushBack]") {
    DLList<int> list;
    list.PushBack(2);
    INFO("input: [2], PushBack(4); expected order: [2, 4]");
    REQUIRE(list.PushBack(4) == true);
    RequireOrder(list, {2, 4}, {4, 2});
}

TEST_CASE("PushBack preserves insertion order across several appends", "[PushBack]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: PushBack(1), PushBack(2), PushBack(3); expected order: [1, 2, 3]");
    RequireOrder(list, {1, 2, 3}, {3, 2, 1});
}

TEST_CASE("PushBack keeps the old head unchanged", "[PushBack]") {
    DLList<int> list;
    list.PushFront(6);
    list.PushBack(8);
    INFO("input: [6], PushBack(8); expected TopFront() == 6");
    REQUIRE(list.TopFront() == 6);
}

TEST_CASE("PushBack sets the new tail next pointer to null", "[PushBack]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    INFO("input: [1], PushBack(2); expected tail->next == nullptr");
    REQUIRE(list.tail->next == nullptr);
}

TEST_CASE("TopFront returns null-equivalent value for an empty int list", "[TopFront]") {
    DLList<int> list;
    INFO("input: empty list; expected output: TopFront() == 0");
    REQUIRE(list.TopFront() == 0);
}

TEST_CASE("TopFront returns the only element", "[TopFront]") {
    DLList<int> list;
    list.PushBack(7);
    INFO("input: [7]; expected output: TopFront() == 7");
    REQUIRE(list.TopFront() == 7);
}

TEST_CASE("TopFront returns the first element after multiple appends", "[TopFront]") {
    DLList<int> list;
    list.PushBack(7);
    list.PushBack(9);
    list.PushBack(11);
    INFO("input: [7, 9, 11]; expected output: TopFront() == 7");
    REQUIRE(list.TopFront() == 7);
}

TEST_CASE("TopFront reflects the newest front insertion", "[TopFront]") {
    DLList<int> list;
    list.PushBack(7);
    list.PushFront(5);
    INFO("input: [7], PushFront(5); expected output: TopFront() == 5");
    REQUIRE(list.TopFront() == 5);
}

TEST_CASE("TopBack returns null-equivalent value for an empty int list", "[TopBack]") {
    DLList<int> list;
    INFO("input: empty list; expected output: TopBack() == 0");
    REQUIRE(list.TopBack() == 0);
}

TEST_CASE("TopBack returns the only element", "[TopBack]") {
    DLList<int> list;
    list.PushFront(7);
    INFO("input: [7]; expected output: TopBack() == 7");
    REQUIRE(list.TopBack() == 7);
}

TEST_CASE("TopBack returns the last element after multiple prepends", "[TopBack]") {
    DLList<int> list;
    list.PushFront(11);
    list.PushFront(9);
    list.PushFront(7);
    INFO("input: PushFront(11), PushFront(9), PushFront(7); expected output: TopBack() == 11");
    REQUIRE(list.TopBack() == 11);
}

TEST_CASE("TopBack reflects the newest back insertion", "[TopBack]") {
    DLList<int> list;
    list.PushFront(5);
    list.PushBack(7);
    INFO("input: [5], PushBack(7); expected output: TopBack() == 7");
    REQUIRE(list.TopBack() == 7);
}

TEST_CASE("PopFront returns null-equivalent value for an empty int list", "[PopFront]") {
    DLList<int> list;
    INFO("input: empty list; expected output: PopFront() == 0");
    REQUIRE(list.PopFront() == 0);
}

TEST_CASE("PopFront removes and returns the only element", "[PopFront]") {
    DLList<int> list;
    list.PushBack(4);
    INFO("input: [4]; expected output: PopFront() == 4 and list is empty");
    REQUIRE(list.PopFront() == 4);
    REQUIRE(list.Empty() == true);
    REQUIRE(list.head == nullptr);
    REQUIRE(list.tail == nullptr);
}

TEST_CASE("PopFront removes the first element from a two-element list", "[PopFront]") {
    DLList<int> list;
    list.PushBack(4);
    list.PushBack(5);
    INFO("input: [4, 5]; expected output: PopFront() == 4 and remaining order [5]");
    REQUIRE(list.PopFront() == 4);
    RequireOrder(list, {5}, {5});
}

TEST_CASE("PopFront removes elements in front-to-back order", "[PopFront]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: [1, 2, 3]; expected pop sequence: 1, 2, 3");
    REQUIRE(list.PopFront() == 1);
    REQUIRE(list.PopFront() == 2);
    REQUIRE(list.PopFront() == 3);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("PopFront resets the new head prev pointer", "[PopFront]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PopFront();
    INFO("input: [1, 2] then PopFront(); expected head->prev == nullptr");
    REQUIRE(list.head->prev == nullptr);
}

TEST_CASE("PopBack returns null-equivalent value for an empty int list", "[PopBack]") {
    DLList<int> list;
    INFO("input: empty list; expected output: PopBack() == 0");
    REQUIRE(list.PopBack() == 0);
}

TEST_CASE("PopBack removes and returns the only element", "[PopBack]") {
    DLList<int> list;
    list.PushBack(4);
    INFO("input: [4]; expected output: PopBack() == 4 and list is empty");
    REQUIRE(list.PopBack() == 4);
    REQUIRE(list.Empty() == true);
    REQUIRE(list.head == nullptr);
    REQUIRE(list.tail == nullptr);
}

TEST_CASE("PopBack removes the last element from a two-element list", "[PopBack]") {
    DLList<int> list;
    list.PushBack(4);
    list.PushBack(5);
    INFO("input: [4, 5]; expected output: PopBack() == 5 and remaining order [4]");
    REQUIRE(list.PopBack() == 5);
    RequireOrder(list, {4}, {4});
}

TEST_CASE("PopBack removes elements in back-to-front order", "[PopBack]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: [1, 2, 3]; expected pop sequence: 3, 2, 1");
    REQUIRE(list.PopBack() == 3);
    REQUIRE(list.PopBack() == 2);
    REQUIRE(list.PopBack() == 1);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("PopBack resets the new tail next pointer", "[PopBack]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PopBack();
    INFO("input: [1, 2] then PopBack(); expected tail->next == nullptr");
    REQUIRE(list.tail->next == nullptr);
}

TEST_CASE("Find returns false for an empty list", "[Find]") {
    DLList<int> list;
    INFO("input: empty list, Find(3); expected output: false");
    REQUIRE(list.Find(3) == false);
}

TEST_CASE("Find returns true for the head value", "[Find]") {
    DLList<int> list;
    list.PushBack(3);
    list.PushBack(4);
    INFO("input: [3, 4], Find(3); expected output: true");
    REQUIRE(list.Find(3) == true);
}

TEST_CASE("Find returns true for the tail value", "[Find]") {
    DLList<int> list;
    list.PushBack(3);
    list.PushBack(4);
    INFO("input: [3, 4], Find(4); expected output: true");
    REQUIRE(list.Find(4) == true);
}

TEST_CASE("Find returns false for a missing value", "[Find]") {
    DLList<int> list;
    list.PushBack(3);
    list.PushBack(4);
    INFO("input: [3, 4], Find(9); expected output: false");
    REQUIRE(list.Find(9) == false);
}

TEST_CASE("Erase returns false for an empty list", "[Erase]") {
    DLList<int> list;
    INFO("input: empty list, Erase(3); expected output: false");
    REQUIRE(list.Erase(3) == false);
}

TEST_CASE("Erase removes the head value", "[Erase]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: [1, 2, 3], Erase(1); expected order: [2, 3]");
    REQUIRE(list.Erase(1) == true);
    RequireOrder(list, {2, 3}, {3, 2});
}

TEST_CASE("Erase removes the tail value", "[Erase]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: [1, 2, 3], Erase(3); expected order: [1, 2]");
    REQUIRE(list.Erase(3) == true);
    RequireOrder(list, {1, 2}, {2, 1});
}

TEST_CASE("Erase removes a middle value", "[Erase]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: [1, 2, 3], Erase(2); expected order: [1, 3]");
    REQUIRE(list.Erase(2) == true);
    RequireOrder(list, {1, 3}, {3, 1});
}

TEST_CASE("Erase removes only the first matching value", "[Erase]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(2);
    list.PushBack(3);
    INFO("input: [1, 2, 2, 3], Erase(2); expected order: [1, 2, 3]");
    REQUIRE(list.Erase(2) == true);
    RequireOrder(list, {1, 2, 3}, {3, 2, 1});
}

TEST_CASE("AddBefore returns false for an empty list", "[AddBefore]") {
    DLList<int> list;
    INFO("input: empty list, AddBefore(nullptr, 3); expected output: false");
    REQUIRE(list.AddBefore(nullptr, 3) == false);
}

TEST_CASE("AddBefore inserts before the head", "[AddBefore]") {
    DLList<int> list;
    list.PushBack(2);
    INFO("input: [2], AddBefore(head, 1); expected order: [1, 2]");
    REQUIRE(list.AddBefore(list.head, 1) == true);
    RequireOrder(list, {1, 2}, {2, 1});
    REQUIRE(list.head->prev == nullptr);
}

TEST_CASE("AddBefore inserts before a middle node", "[AddBefore]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(3);
    list.PushBack(4);
    INFO("input: [1, 3, 4], AddBefore(node with 3, 2); expected order: [1, 2, 3, 4]");
    REQUIRE(list.AddBefore(list.head->next, 2) == true);
    RequireOrder(list, {1, 2, 3, 4}, {4, 3, 2, 1});
}

TEST_CASE("AddBefore inserts before the tail", "[AddBefore]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(3);
    INFO("input: [1, 3], AddBefore(tail, 2); expected order: [1, 2, 3]");
    REQUIRE(list.AddBefore(list.tail, 2) == true);
    RequireOrder(list, {1, 2, 3}, {3, 2, 1});
}

TEST_CASE("AddAfter returns false for an empty list", "[AddAfter]") {
    DLList<int> list;
    INFO("input: empty list, AddAfter(nullptr, 3); expected output: false");
    REQUIRE(list.AddAfter(nullptr, 3) == false);
}

TEST_CASE("AddAfter inserts after the only node", "[AddAfter]") {
    DLList<int> list;
    list.PushBack(1);
    INFO("input: [1], AddAfter(head, 2); expected order: [1, 2]");
    REQUIRE(list.AddAfter(list.head, 2) == true);
    RequireOrder(list, {1, 2}, {2, 1});
    REQUIRE(list.tail->next == nullptr);
}

TEST_CASE("AddAfter inserts after the head in a multi-node list", "[AddAfter]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(3);
    INFO("input: [1, 3], AddAfter(head, 2); expected order: [1, 2, 3]");
    REQUIRE(list.AddAfter(list.head, 2) == true);
    RequireOrder(list, {1, 2, 3}, {3, 2, 1});
}

TEST_CASE("AddAfter inserts after a middle node", "[AddAfter]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(4);
    INFO("input: [1, 2, 4], AddAfter(node with 2, 3); expected order: [1, 2, 3, 4]");
    REQUIRE(list.AddAfter(list.head->next, 3) == true);
    RequireOrder(list, {1, 2, 3, 4}, {4, 3, 2, 1});
}

TEST_CASE("AddAfter inserts after the tail and updates tail", "[AddAfter]") {
    DLList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    INFO("input: [1, 2], AddAfter(tail, 3); expected order: [1, 2, 3] and TopBack() == 3");
    REQUIRE(list.AddAfter(list.tail, 3) == true);
    RequireOrder(list, {1, 2, 3}, {3, 2, 1});
    REQUIRE(list.TopBack() == 3);
}

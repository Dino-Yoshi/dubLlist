# DLList Unit Test Failure Report

Command run:

```text
ctest --test-dir cmake-build-debug --output-on-failure
```

Result:

```text
Failed 3 test cases, failed 3 assertions.
```

All three failures are in `AddAfter`. The suite builds and runs successfully, and the failures are deterministic functional failures in the implementation, not test harness, build, dependency, or environment errors.

## Failure 1: AddAfter after the only node

- Test: `AddAfter inserts after the only node`
- Test location: `tests/DLListTests.cpp:422`
- Failing assertion location: `tests/DLListTests.cpp:38`
- Input data: list `[1]`, then `AddAfter(head, 2)`
- Expected output: forward traversal `[1, 2]`
- Actual output: forward traversal `[1]`

Catch2 output:

```text
ForwardValues(list) == forward for: { 1 } == { 1, 2 }
```

Verification:

The test first verifies that `AddAfter(list.head, 2)` returns `true`, then traverses from `head` using `next` pointers. The implementation enters the `currNode == head` branch at `DLList.cpp:302`, initializes `newNode->prev` and `newNode->next`, but never assigns `currNode->next = newNode`. Therefore the inserted node is not reachable from `head`.

## Failure 2: AddAfter after the head in a multi-node list

- Test: `AddAfter inserts after the head in a multi-node list`
- Test location: `tests/DLListTests.cpp:431`
- Failing assertion location: `tests/DLListTests.cpp:38`
- Input data: list `[1, 3]`, then `AddAfter(head, 2)`
- Expected output: forward traversal `[1, 2, 3]`
- Actual output: forward traversal `[1, 3]`

Catch2 output:

```text
ForwardValues(list) == forward for: { 1, 3 } == { 1, 2, 3 }
```

Verification:

The implementation again uses the `currNode == head` branch at `DLList.cpp:302`. It updates the old second node's `prev` pointer to the new node at `DLList.cpp:308`, but still never updates the head's `next` pointer to the new node. This creates an inconsistent chain where backward traversal can see the new node, but forward traversal cannot.

## Failure 3: AddAfter after the tail

- Test: `AddAfter inserts after the tail and updates tail`
- Test location: `tests/DLListTests.cpp:450`
- Failing assertion location: `tests/DLListTests.cpp:39`
- Input data: list `[1, 2]`, then `AddAfter(tail, 3)`
- Expected output: backward traversal `[3, 2, 1]` and `TopBack() == 3`
- Actual output: backward traversal `[2, 1]`

Catch2 output:

```text
BackwardValues(list) == backward for: { 2, 1 } == { 3, 2, 1 }
```

Verification:

The implementation enters the `currNode == tail` branch at `DLList.cpp:320` and assigns `tail->next = newNode`, so forward traversal can reach the new node. However, it never assigns `tail = newNode`. As a result, `tail` still points to the old final node, backward traversal starts from the wrong node, and `TopBack()` would return the old tail value.

## Summary

The suite itself is valid for these failures because:

- Catch2 compiled and executed normally.
- The failing tests use simple integer data and direct pointer traversal of the linked list.
- The same traversal helpers pass for `PushFront`, `PushBack`, `PopFront`, `PopBack`, `Erase`, and `AddBefore`.
- The failed expectations match standard doubly linked list behavior: inserting after a node must connect the previous node's `next` pointer and, when inserting after the tail, must update `tail`.

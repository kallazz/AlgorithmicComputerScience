import pytest

from hybrid_sort import hybrid_sort
from insertion_sort import insertion_sort
from quick_sort import quick_sort
from list_generator import generate_random_list

ARRAY_SIZES_TO_CHECK = 100

def assert_random_arrays(sorting_algorithm):
    for i in range(ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        assert sorted(random_list) == sorting_algorithm(random_list)

def test_insertion_sort():
    for i in range(ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        expected_result = sorted(random_list)
        insertion_sort(random_list)
        assert random_list == expected_result

def test_quick_sort():
    for i in range(ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        expected_result = sorted(random_list)
        quick_sort(random_list, 0, i - 1)
        assert random_list == expected_result

def test_hybrid_sort():
    for i in range(ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        expected_result = sorted(random_list)
        hybrid_sort(random_list, 0, i - 1)
        assert random_list == expected_result
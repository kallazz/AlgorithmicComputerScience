import pytest

from sorting_algorithms.custom_sort import custom_sort
from sorting_algorithms.hybrid_sort import hybrid_sort
from sorting_algorithms.insertion_sort import insertion_sort
from sorting_algorithms.merge_sort import merge_sort
from sorting_algorithms.quick_sort import quick_sort
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


def test_merge_sort():
    for i in range(ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        expected_result = sorted(random_list)
        merge_sort(random_list, 0, i - 1)
        assert random_list == expected_result


def test_custom_sort():
    for i in range(1, ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        expected_result = sorted(random_list)
        custom_sort(random_list)
        assert random_list == expected_result

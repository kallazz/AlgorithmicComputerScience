import pytest

from sorting_algorithms.custom_sort import custom_sort
from sorting_algorithms.hybrid_sort import hybrid_sort
from sorting_algorithms.insertion_sort import insertion_sort
from sorting_algorithms.merge_sort import merge_sort
from sorting_algorithms.quick_sort import quick_sort
from sorting_algorithms.dual_pivot_quicksort import dual_pivot_quicksort
from list_generator import generate_random_list

ARRAY_SIZES_TO_CHECK = 100


def assert_random_arrays(sorting_algorithm, takes_args = False):
    for i in range(1, ARRAY_SIZES_TO_CHECK):
        random_list = generate_random_list(i)
        expected_result = sorted(random_list)
        if takes_args:
            sorting_algorithm(random_list, 0, len(random_list) - 1)
        else:
            sorting_algorithm(random_list)
        assert random_list == expected_result


def test_insertion_sort():
    assert_random_arrays(insertion_sort)


def test_quick_sort():
    assert_random_arrays(quick_sort, takes_args=True)


def test_hybrid_sort():
    assert_random_arrays(hybrid_sort, takes_args=True)


def test_merge_sort():
    assert_random_arrays(merge_sort, takes_args=True)


def test_custom_sort():
    assert_random_arrays(custom_sort)


def test_dual_pivot_quicksort():
    assert_random_arrays(dual_pivot_quicksort, takes_args=True)

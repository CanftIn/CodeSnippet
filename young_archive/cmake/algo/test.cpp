#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <cmath>
#include <limits>

using namespace std;

template <typename T, std::size_t SIZE, typename F>
void insertion_sort(std::array<T, SIZE> &arr, F &&pred)
{
	for (int i = 1; i < SIZE; i++)
	{
		T key = arr.at(i);
		int j = i - 1;
		while (j >= 0 && pred((T)arr.at(j), key))
		{
			arr.at(j + 1) = arr.at(j);
			j--;
		}
		arr.at(j + 1) = key;
	}
}

template <typename T, std::size_t SIZE, typename F>
void merge(std::array<T, SIZE> &arr, int p, int q, int r, F &&pred)
{
	int n_1 = q - p + 1;
	int n_2 = r - q;
	std::vector<T> L;
	std::vector<T> R;
	for (int i = 0; i < n_1; i++)
	{
		L.push_back(arr.at(p + i));
	}
	for (int i = 0; i < n_2; i++)
	{
		R.push_back(arr.at(q + i + 1));
	}
	L.push_back(std::numeric_limits<T>::max());
	R.push_back(std::numeric_limits<T>::max());
	int i = 0, j = 0;
	for (int k = p; k < r + 1; k++)
	{
		if (pred(L.at(i), R.at(j)))
		{
			arr.at(k) = L.at(i);
			i++;
		}
		else
		{
			arr.at(k) = R.at(j);
			j++;
		}
	}
}

template <typename T, std::size_t SIZE, typename F>
void merge_sort(std::array<T, SIZE> &arr, int p, int r, F &&pred)
{
	if (p < r)
	{
		T q = (int)std::floor((p + r) / 2);
		merge_sort(arr, p, q, pred);
		merge_sort(arr, q + 1, r, pred);
		merge(arr, p, q, r, pred);
	}
}

int main(int argc, char **argv)
{
	std::array<int, 10> test_arr = {4, 1, 5, 2, 3, 9, 6, 8, 0, 7};
	merge_sort(test_arr, 0, 9, [](int a, int b) { return a <= b; });
	for (const auto &n : test_arr)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;
	return 0;
}
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define VEC_MAX_SIZE 24
#define VEC_MAX_ELEMENT 12

int trap(std::vector<int>& height)
{
	/*

		_ _ # _ _ _ _ _ _ 
		_ _ # _ _ _ _ _ # 		trapped water is
		_ _ # _ _ _ _ # # 		current max (moving r->l)
		_ _ # _ _ _ _ # # 		minus current if lte (else new max)
		_ _ # _ _ _ _ # # 		do this til hit gte number (else discard)
		_ _ # _ _ _ _ # # 		repeat
		_ _ # _ _ # _ # # 
		_ _ # _ _ # _ # # 
		# _ # _ _ # _ # # 
		# # # _ _ # _ # # 
		# # # _ _ # _ # # 
		# # # _ # # _ # # 
		[ 4 3 12 0 1 6 0 10 11 ]

							*/

	int cur_max = 0;
	int cur = 0;
	int left_wall = 0;
	int right_wall = 0;
	int width = 0;
	int water = 0;
	int stuck = 0;

	for (std::vector<int>::iterator it = height.begin(); it != height.end(); it++)
	{
		cur = *it;
	
		//initial case	
		if (left_wall == 0)
		{
			left_wall = cur;
		}		
		else
		{
			//right wall
			if ((left_wall - cur) <= 0)
			{
				right_wall = cur;
				
			}
			else
			{
				width++;
			}
		}
		//update max
		if ((cur_max - cur) <= 0)
		{
			cur_max = cur;
			//new max or eq means water is bounded, so put in stuck and reset
			stuck += water;
			water = 0;
		}
		else //cur lte local max
		{
			water += cur_max - cur;
		}
	}

	return stuck;
}

int find_max(std::vector<int>& v)
{
	int max = 0;
	int current = 0;
	std::vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++)
	{
		current = *it;
		if (current > max)
			max = current;
	}
	return max;
}

void graph_vec(std::vector<int>& v)
{
	int height = find_max(v);
	int water = 0;
	std::vector<int>::iterator it;
	//iterate through lines
	for (int i = 0; i < height; i++)
	{
		//does the int in this vector go high enough to be in this line?
		for (it = v.begin(); it != v.end(); it++)
		{
			//height-i = distance from top, meme is printed from the top down
			if (*it >= height-i)
				std::cout << "# ";
			else
				std::cout << "_ ";
		}
		std::cout << "\n";
	}
}

void print_vec(std::vector<int>& v)
{
	std::cout << "[ ";
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;
}

void bubble_sort(std::vector<int>& v)
{
	int swaps = 0;
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		//look ahead
		if (*it > *(it+1))
		{
			std::swap(*it, *(it+1));
			swaps++;
		}
	}
	if (swaps != 0)
		bubble_sort(v);
}

int main(void)
{
	std::vector<int> vector;
	std::srand(std::time(0));
	time_t beg, end = 0;

	int r_vec_size = std::rand() % (VEC_MAX_SIZE + 1);

	for (int i = 0; i < r_vec_size; i++)
	{
		vector.push_back(std::rand() % (VEC_MAX_ELEMENT + 1));
	}

	graph_vec(vector);
	print_vec(vector);

	std::time(&beg);
	bubble_sort(vector);
	std::time(&end);

	graph_vec(vector);
	print_vec(vector);

	std::cout << "time to sort: " << end << beg << std::endl;

	return 0;
}

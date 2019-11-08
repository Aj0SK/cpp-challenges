#include <bits/stdc++.h>

using namespace std;

template <class RandomIt, class Compare>
constexpr void quicksort(RandomIt first, RandomIt last, Compare cmp)
{    
    if(first >= last)
    // just to be sure :-)
    {
        return;
    }
    
    size_t n = last - first;
    
    if(n <= 32)
    {
        std::sort(first, last, cmp);
        // TODO something O(n^2) that works pretty fast for small inputs
        return;
    }

    const size_t relPivotIndex = (rand() % (n));
    
    if(relPivotIndex != 0)
    {
        swap(*(first+relPivotIndex), *first);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Pivot is now on the position [first]. We are passing elements from left to
    // right. We put elements bigger than pivot on the right side and elements
    // equal to pivot on the left side.
    
    RandomIt i = first+1, j = last;
    int equalNum = 1;

    for(;i<j;)
    {
        if(*i < *first)
        {
            ++i;
        }
        else if(*first < *i)
        {
            while( j-1 != i && *first < *(j-1))
            {
                --j;
            }
            if(i == j-1)
            {
                --j;
                break;
            }

            swap(*i, *(j-1));
            
            if(!(*i < *first))
            {
                if(i != first + equalNum)
                {
                    swap(*i, *(first+equalNum));
                }
                 ++equalNum;
            }
            
            ++i;
            --j;
        }
        else
        {
            if(i != first + equalNum)
            {
                swap(*i, *(first+equalNum));
            }
            ++equalNum;
            ++i;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // In the first "part" of array -- [first;i) we have elements <= pivot
    // Also we have elements equal to pivot on positions [first, equalNum) and we
    // want these on the end of this "part" of array
    
    int savedEqualNum = equalNum;
    int size = i-first;
    
    if(equalNum > size/2)
    {
        equalNum = size - equalNum;
    }
    
    for(int k=0; k<equalNum; ++k)
    {
        swap(*(first+k), *(i-k-1));
    }
    
    // now we recursively call our algorithm on whole second part and elements
    // from first part, that are strictly less than our pivot
    
    quicksort(first, i-savedEqualNum);
    quicksort(i, last);
}


int main()
{
    ios_base::sync_with_stdio(false);
    
    vector<int> pole = {7, -6, 2, -4};
    
    sort(pole.begin(), pole.end(), std::less<int>());
    
    for(int i=1; i<pole.size(); ++i)
    {
        if(pole[i-1] > pole[i])
        {
            std::cout << "Error" << std::endl;
        }
    }
    
    return 0;
}

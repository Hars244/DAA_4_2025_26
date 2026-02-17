class Solution
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            long long hoursneeded = 0;

            for (int i = 0; i < piles.size(); i++)
            {
                int pile = piles[i];
                hoursneeded += (pile + mid - 1) / mid;
            }
            if (hoursneeded <= h)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

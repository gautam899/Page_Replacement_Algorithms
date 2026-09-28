#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <unordered_set>

class FIFO
{
public:
    int countPageFaults(const std::vector<int> &pages, const int maxFrames)
    {
        // Stores the Page References. To make it easier to remove the first in page, we use a queue.
        std::queue<int> queue;
        int faultCount = 0;

        // unordered_set to check what page exist is frames already
        std::unordered_set<int> storage;

        for (std::size_t i = 0; i < pages.size(); i++)
        {
            int p = pages[i];
            if (storage.find(p) != storage.end())
                continue;

            faultCount++;
            if (queue.size() >= maxFrames)
            {
                storage.erase(queue.front());
                queue.pop(); // Remove the front
            }
            queue.push(p);
            storage.insert(p);
        }
        return faultCount;
    }
};
int main()
{
    std::string referenceString = "7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1";
    // std::string referenceString = "1,2,3,4,1,2,5,1,2,3,4,5";
    std::vector<int> pages;

    char *page = std::strtok(referenceString.data(), ",");

    while (page != nullptr)
    {
        pages.push_back(std::stoi(page));
        page = std::strtok(nullptr, ",");
    }

    int maxFrames = 3; // Can be taken as input from the user.
    FIFO fifo;
    int ans = fifo.countPageFaults(pages, maxFrames);
    std::cout << ans << std::endl;
    return 0;
}
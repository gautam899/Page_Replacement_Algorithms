#include <vector>
#include <iostream>
#include <cstring>
#include <queue>
#include <unordered_set>
#include <unordered_map>

class OPT
{
public:
    int findFarthestPage(const std::unordered_map<int, std::queue<int>> &futureOccurences, const std::unordered_set<int> &currentPages)
    {
        int farthestIndex = -1;
        int ans = -1;
        for (const auto &it : currentPages)
        {
            if (futureOccurences.at(it).size() == 0)
                return it; // Will not be used again. Can be replace
            int nextOccurence = futureOccurences.at(it).front();
            if (nextOccurence > farthestIndex)
            {
                farthestIndex = nextOccurence;
                ans = it;
            }
        }
        return ans;
    }
    int countPageFault(const std::vector<int> &pages, int maxFrames)
    {
        if (maxFrames <= 0)
        {
            std::cout << "Number of frames must be greater than zero. Exiting!!" << std::endl;
            std::exit(1);
        }

        // A variable to count the number of page faults
        int count = 0;
        // A data structure to store all the pages currently residing in the frames. In this case I am using a unordered_set which makes it easier to easily find pages already in the frames.
        std::unordered_set<int> currentPages;
        // To store a mapping of pages with all there future occurences, I am using a unordered_map where I have mapped with page number with a queue. The queue will store the page occurences for a page number in order.
        std::unordered_map<int, std::queue<int>> map;

        for (std::size_t i = 0; i < pages.size(); i++)
        {
            map[pages[i]].push(i);
        }

        for (std::size_t i = 0; i < pages.size(); i++)
        {
            int p = pages[i];
            if (currentPages.find(p) != currentPages.end())
            {
                map[p].pop(); // Pop the current index.
                continue;
            }

            count++; // Page fault
            if (currentPages.size() == maxFrames)
            {
                int farthestPage = findFarthestPage(map, currentPages);
                currentPages.erase(farthestPage);
                currentPages.insert(p);
                map[p].pop();
            }
            else
            {
                currentPages.insert(p);
                map[p].pop(); // The front would be the current index.
            }
        }
        return count;
    }
};
int main()
{
    std::string referenceString = "7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1";
    std::vector<int> pages;
    char *page = std::strtok(referenceString.data(), ",");
    while (page != nullptr)
    {
        pages.push_back(std::stoi(page));
        page = std::strtok(nullptr, ",");
    }

    OPT opt;
    int maxFrames = 3;
    int ans = opt.countPageFault(pages, maxFrames);
    std::cout << ans << std::endl;
    return 0;
}
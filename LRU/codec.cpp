#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>

class Node
{
public:
    int pageNumber;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(int _pageNumber)
    {
        pageNumber = _pageNumber;
    }
};

class LRU
{
public:
    Node *head = new Node(-1);
    Node *tail = new Node(-1);

    // pageNumber -> node
    std::unordered_map<int, Node *> storage;

    // Add a page in front of the Head
    void addNode(Node *node)
    {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    // Delete the LRU node/page
    void deleteNode(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    int countPageFaults(std::vector<int> &pages, int maxFrames)
    {
        if (maxFrames <= 0)
        {
            std::cout << "Number of frames must be greater than zero." << std::endl;
            exit(0);
        }
        /* Initialize */
        head->next = tail;
        tail->prev = head;

        int count = 0;
        for (std::size_t i = 0; i < pages.size(); i++)
        {
            int p = pages[i];

            // If the page is already in the frames.
            if (storage.find(p) != storage.end())
            {
                // Get the node associated with page number p
                Node *node = storage[p];
                // Delete the node from it's original position
                deleteNode(node);
                // And add it to the front as the most recently used node.
                addNode(node);
                continue;
            }
            else
            {
                count++; // Page fault
                Node *node = new Node(p);
                if (storage.size() == maxFrames)
                {
                    // Remove the LRU page
                    storage.erase(tail->prev->pageNumber);
                    deleteNode(tail->prev);
                    addNode(node);
                }
                else
                {
                    addNode(node);
                }
                storage[p] = node;
            }
        }
        return count;
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
    LRU lru;
    int ans = lru.countPageFaults(pages, maxFrames);
    std::cout << ans << std::endl;
    return 0;
}
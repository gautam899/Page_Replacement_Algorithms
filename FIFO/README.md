# FIFO Page replacement Algorithm

- This is the simplest among all page replacement algorithms

- This algorithm associates with each page the time at which the page was brought into the memory.

- When the page has to be removed, the oldest page is removed. It is not strictly necessary to record the time at which the page was brought into the memory. We can maintain a FIFO queue and remove the page at the front of the queue.

- We consider a total of three memory frames available.

- A reference string is a sequence of memory access requests, represented as page numbers, generated while executing a program or process. It serves as the input for evaluating page replacement algorithms by simulating how the operating system handles memory requests to minimize page faults.

- A similar reference string is used as input in this implementation "7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1". 

- Ideally, increasing the number of frames for a reference string should reduce the number of page faults. But, for reference string "1,2,3,4,1,2,5,1,2,3,4,5" we notice that the number of page faults with 3 frames is 9 and with 4 frames is 10. This is called Belady's anamoly.
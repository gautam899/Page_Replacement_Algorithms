# LRU (Least Recently Used) Page Replacement Algorithm

- Unlike the FIFO page replacement algorithm, in the Least Recenctly Used Page Replacement Algorithm, we replace the page that has not been used for the longest Period of time.

- LRU page replacement algorithm can never exhibit Belady's anomaly. It is a stack algorithm. That means it can be proven that the set of pages in the memory for n frames is a subset of set of pages in a memory for n+1 frames.
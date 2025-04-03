Nicholas Llaurado
My partner was Kay Leen however she dropped the class after ms1. All work since then has been produced by me.

To test the cache simulator, I decided to first experiment by going through each trace file and running different configurations on the same trace to see how they compare.
First, I wanted to test the differences in output between LRU and FIFO. After running the same parameters for each of the trace files for lru and fifo, I saw that fifo consistently has a higher miss rate of about 20% on average, going up to 2x that of lru.
fifo produces slightly more cycles than lru, about 1% on average. Lru consistently has slightly higher hit rates for loading and storing, about 1% more every time. From changing fifo and lru alone, we can conclude that fifo leads to a higher miss rate, making it a less efficient parameter than lru. 

Next I decided to test the results of no-write-allocate and write-allocate. I ran differerent combinations of no-write-allocate and write-allocate all of the test files and compared the results.
I found that no-write-allocate consistently produces fewer store hits, sometimes none at all. it has many more store misses on average, up to 3x that of its opposite, write-allocate. In addition, it also produces about 20% more load misses on average, sometimes going up to 2x that of write-allocate. 
The load hits remain the same for the most part. I also decided to see if changing the exiction policy had an effect on these results. I saw that the miss and hit rates were slightly affected when changed from lru to fifo and vice versa. as seen in my first set of testing, fifo increases the overall miss rate, especially when paired with no-write-allocate. 
Total cycles were mostly unaffected by these configuration changes. Occasionally being around 5% less when ran on no-write-allocate
From this testing I can conclude that no-write-allocate results in less efficient cache performance as it consistently produces a higher miss rate.

The next step was testing wether or not write-through or write-back would create better results when paired with write-allocate. 
After running all of the test files on a cache configuration with write-allocate and alternating write-back and write-through, I quickly found that write-back consistently produces fewer total cylces than write-through. The miss and hit rates are mostly unaffected by these changes. 
Write-through produces up to 3x more total cycles than write-back on average. This results in less efficient cache performance. Write back can be identified as the more efficeint solution. 

The last steps were to determine the optimal number of sets, blocks, and number of bytes. First, I ran the different test files while altering the number of sets. I started at the lowest number, 1 and progresssively increased the number of sets up to 8192. 
I found that as the number of sets goes, up the hit rate increases and the miss rate decreases. Total cylces also decreases as set number increases. This shows that higher set number is optimal. The optimal number of sets should be maximized. 
As the number of blocks increases, the total number of cycle decreases significantly as well as the miss rate. Hit rate is unaffected for the most part. I tested values all the way from 1 to 8192. This value should be maximized.
However, as the number of bytes in each block increases, total cylces and miss rate increases. This value should be minimized. 

Overall, from this testing the best configuration is as follows:
number of sets: 256 - 8192
number of blocks: 256 - 8192
number of bytes in block: 4 - 16
write-allocate
write-back
lru

This configuration produces the lowest miss rate and total cylces and maximizes hit rate.

